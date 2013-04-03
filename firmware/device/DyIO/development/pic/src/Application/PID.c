/**
 * PID.c
 *
 *  Created on: Aug 8, 2009
 *      Author: hephaestus
 */

#include "UserApp.h"

static AbsPID 			pidGroups[NUM_PID_GROUPS];
static DYIO_PID 		dyPid[NUM_PID_GROUPS];
static PD_VEL 			vel[NUM_PID_GROUPS];
static PidLimitEvent	limits[NUM_PID_GROUPS];

extern DATA_STRUCT * DATA __attribute__ ((section (".scs_global_var")));

#define DYPID_NON_USED 0xff

float getPositionMine(int group);
void setOutputMine(int group, float val);
int resetPositionMine(int group, int target);
//void pidAsyncCallbackMine();
void onPidConfigureMine(int);
PidLimitEvent * checkPIDLimitEventsMine(BYTE group);



static RunEveryData force[NUM_PID_GROUPS];

void fail(){
	while(TRUE){
		SetColor(1,1,0);
		buttonCheck(1);
	}
}

void initPIDChans(BYTE group){

	if(dyPid[group].inputChannel==DYPID_NON_USED || dyPid[group].outputChannel==DYPID_NON_USED)
		return;

	switch(dyPid[group].inputMode & 0x7F){
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
		dyPid[group].inputChannel = getCounterIntChannnel( channelToCounterGroup(dyPid[group].inputChannel));
		StartCounterInput(dyPid[group].inputChannel);
		break;
	}

	println_I("Setting Modes for PID");
	SetCoProcMode(dyPid[group].inputChannel,dyPid[group].inputMode|0x80);
	SetCoProcMode(dyPid[group].outputChannel,dyPid[group].outputMode);
	SyncModes();

	if(dyPid[group].inputMode== IS_ANALOG_IN){
		pidGroups[group].SetPoint=GetAnalogValFromAsync(dyPid[group].inputChannel);
	}else{
		pidGroups[group].SetPoint=0;
	}
}
BOOL asyncCallback(BowlerPacket *Packet){
    PutBowlerPacket(Packet);// This only works with USB and UART
    return TRUE;
}
void InitPID(void){

	BYTE i;
	//WORD loop;
	for (i=0;i<NUM_PID_GROUPS;i++){
		//DyPID values
		dyPid[i].inputChannel=DYPID_NON_USED;
		dyPid[i].outputChannel=DYPID_NON_USED;
		dyPid[i].inputMode=0;
		dyPid[i].outputMode=0;

		pidGroups[i].Enabled=FALSE;
		pidGroups[i].channel = i;
		vel[i].enabled=FALSE;
		vel[i].K.P=.1;
		limits[i].type=NO_LIMIT;

		LoadPIDvals(&pidGroups[i],&dyPid[i]);
		if(		dyPid[i].inputChannel==DYPID_NON_USED ||
				dyPid[i].outputChannel==DYPID_NON_USED  ||
				dyPid[i].outputChannel==dyPid[i].inputChannel)
		{
			dyPid[i].inputChannel=DYPID_NON_USED;
			dyPid[i].outputChannel=DYPID_NON_USED;
			WritePIDvalues(&pidGroups[i],&dyPid[i]);
		}
		force[i].MsTime=0;
		force[i].setPoint=200;
	}

	InitilizePidController( pidGroups,
							vel,
							NUM_PID_GROUPS,
							&getPositionMine,
							&setOutputMine,
							&resetPositionMine,
							&asyncCallback,
							&onPidConfigureMine,
							&checkPIDLimitEventsMine);

	for (i=0;i<NUM_PID_GROUPS;i++){
		printPIDvals(i);
		if(pidGroups[i].Enabled){
			initPIDChans(i);
			println_I("Resetting PID channel from init");
			int value = 0;
			if(dyPid[i].inputMode == IS_ANALOG_IN)
				value = 512;
			pidReset(i,value);
		}
	}

}

void GetConfigDyPID(BowlerPacket * Packet){
	BYTE chan = Packet->use.data[0];
	Packet->use.data[1]=dyPid[chan].inputChannel;// =Packet->use.data[1];
	Packet->use.data[2]=dyPid[chan].inputMode ;//Packet->use.data[2];
	Packet->use.data[3]=dyPid[chan].outputChannel;//Packet->use.data[3];
	Packet->use.data[4]=dyPid[chan].outputMode;//Packet->use.data[4];
	Packet->use.head.DataLegnth=4+5;
	Packet->use.head.Method=BOWLER_POST;

}
BYTE ConfigDyPID(BowlerPacket * Packet){
	BYTE chan = Packet->use.data[0];
	dyPid[chan].inputChannel =Packet->use.data[1];
	dyPid[chan].inputMode =Packet->use.data[2];
	dyPid[chan].outputChannel =Packet->use.data[3];
	dyPid[chan].outputMode =Packet->use.data[4];

	initPIDChans(chan);

	WritePIDvalues(&pidGroups[chan],&dyPid[chan]);
	return TRUE;
}



BYTE GetPIDGroup(BYTE channel){
	BYTE mode = GetChannelMode(channel);
	BYTE i;
	switch(mode){
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
	case IS_ANALOG_IN:
	case IS_DI:
		for(i=0;i<NUM_PID_GROUPS;i++){
			if(dyPid[i].inputChannel == channel){
				if(pidGroups[i].Enabled || vel[i].enabled )
					return i;
			}
		}
		break;
	case IS_SERVO:
	case IS_DC_MOTOR_DIR:
	case IS_DC_MOTOR_VEL:
	case IS_PWM:
	case IS_DO:
		for(i=0;i<NUM_PID_GROUPS;i++){
			if(dyPid[i].outputChannel == channel){
				if(pidGroups[i].Enabled || vel[i].enabled)
					return i;
			}
		}
		break;
	default:
		break;
	}
	return NOT_USED_IN_PID;
}

void onPidConfigureMine(int group){
	WritePIDvalues(&pidGroups[group],&dyPid[group]);
}

void trigerPIDLimit(BYTE chan,PidLimitType type,INT32  tick){
	limits[chan].group=chan;
	limits[chan].type=type;
	limits[chan].value=tick;
	limits[chan].time=getMs();
}

PidLimitEvent * checkPIDLimitEventsMine(BYTE group){
	return & limits[group];
}


int resetPositionMine(int group, int current){
	if(dyPid[group].inputChannel==DYPID_NON_USED)
			return current;
	if(dyPid[group].inputMode == IS_COUNTER_INPUT_INT){
		SetCounterInput(dyPid[group].inputChannel,current);
	}else if(dyPid[group].inputMode == IS_ANALOG_IN){
		current=GetAnalogValFromAsync(dyPid[group].inputChannel);
	}else if(dyPid[group].inputMode == IS_DI){
		current=GetDigitalValFromAsync(dyPid[group].inputChannel);
	}
	return current;
}

float getPositionMine(int group){
	if(dyPid[group].inputChannel==DYPID_NON_USED||
			((pidGroups[group].Enabled == FALSE) && (vel[group].enabled==FALSE)))
		return 0;

	LONG pos = 0;
	//print_I("\nGetting PID value from group: ");p_sl_I(chan->channel);print_I(" of mode: ");printMode(chan->inputMode);print_I(" From channel: ");p_ul_I(chan->inputChannel);print_I("\n");
	switch(dyPid[group].inputMode){
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
		pos=GetCounterByChannel( dyPid[group].inputChannel );
		break;
	case IS_ANALOG_IN:
		pos=GetAnalogValFromAsync(dyPid[group].inputChannel);
		break;
	case IS_DI:
		pos = GetDigitalValFromAsync(dyPid[group].inputChannel);
		break;
	}
	return ((float)pos);
}

void setOutputMine(int group, float v){

	if( dyPid[group].outputChannel==DYPID_NON_USED||
			((pidGroups[group].Enabled == FALSE) && (vel[group].enabled==FALSE)))
		return;
	Print_Level l = getPrintLevel();
	setPrintLevelNoPrint();
	int val = (int)(v);
	BYTE center = DATA[dyPid[group].outputChannel].PIN.currentConfiguration;

	if(dyPid[group].outputMode == IS_SERVO){
		val += center;
		if (val>190)
			val=190;
		if(val<25)
			val=25;
	}else if(dyPid[group].outputMode == IS_DO){
		if(val>0)
			val=1;
		else
			val=0;
	}else{
		val += 128;
		if (val>255)
			val=255;
		if(val<0)
			val=0;
	}
	int set = (int)val;
	if (dyPid[group].outVal==set){
		//if(!(RunEvery(&force[chan->channel])>0))
			return;
	}else{
		print_I(" Setting PID output, was ");p_sl_I(dyPid[group].outVal);print_I(" is now: ");p_sl_I(set);print_I(" on DyIO chan: ");p_sl_I(dyPid[group].outputChannel);print_I(", ");
	}
	dyPid[group].outVal=set;

	println_I("PID setting output for group: ");p_ul_I(group);
	SetChannelValueCoProc(dyPid[group].outputChannel,dyPid[group].outVal);
	setPrintLevel(l);
}


