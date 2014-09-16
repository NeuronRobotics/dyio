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

#define DYPID_NON_USED 0xff

float getPositionMine(int group);
void setOutputMine(int group, float val);
int resetPositionMine(int group, int target);
//void pidAsyncCallbackMine();
void onPidConfigureMine(int);
PidLimitEvent * checkPIDLimitEventsMine(uint8_t group);



static RunEveryData force[NUM_PID_GROUPS];

void fail(){
	while(true) {
		SetColor(1,1,0);
		buttonCheck(1);
	}
}

void initPIDChans(uint8_t group){

	if(dyPid[group].inputChannel==DYPID_NON_USED || dyPid[group].outputChannel==DYPID_NON_USED)
		return;

	switch(dyPid[group].inputMode){
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
		dyPid[group].inputChannel = getCounterIntChannnel( channelToCounterGroup(dyPid[group].inputChannel));
		StartCounterInput(dyPid[group].inputChannel);
		break;
	}

	println_I("Setting Modes for PID");
	SetCoProcMode(dyPid[group].inputChannel,dyPid[group].inputMode);
	SetCoProcMode(dyPid[group].outputChannel,dyPid[group].outputMode);
	SyncModes();

	if(dyPid[group].inputMode== IS_ANALOG_IN){
		pidGroups[group].SetPoint=GetValFromAsync(dyPid[group].inputChannel);
	}else{
		pidGroups[group].SetPoint=0;
	}
}
boolean asyncCallback(BowlerPacket *Packet){
    PutBowlerPacket(Packet);// This only works with USB and UART
    return true; 
}
void InitPID(void){

	uint8_t i;
	//uint16_t loop;
	for (i=0;i<NUM_PID_GROUPS;i++){
		//DyPID values
		dyPid[i].inputChannel=DYPID_NON_USED;
		dyPid[i].outputChannel=DYPID_NON_USED;
		dyPid[i].inputMode=0;
		dyPid[i].outputMode=0;

		pidGroups[i].config.Enabled=false; 
		vel[i].enabled=false; 
		pidGroups[i].config.V.P=.1;
		limits[i].type=NO_LIMIT;

		LoadPIDvals(&pidGroups[i],&dyPid[i],i);
		if(		dyPid[i].inputChannel==DYPID_NON_USED ||
				dyPid[i].outputChannel==DYPID_NON_USED  ||
				dyPid[i].outputChannel==dyPid[i].inputChannel)
		{
			dyPid[i].inputChannel=DYPID_NON_USED;
			dyPid[i].outputChannel=DYPID_NON_USED;
			WritePIDvalues(&pidGroups[i],&dyPid[i],i);
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
							//&asyncCallback,
							&onPidConfigureMine,
							&checkPIDLimitEventsMine);

	for (i=0;i<NUM_PID_GROUPS;i++){
		printPIDvals(i);
		if(pidGroups[i].config.Enabled){
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
	uint8_t chan = Packet->use.data[0];
	Packet->use.data[1]=dyPid[chan].inputChannel;// =Packet->use.data[1];
	Packet->use.data[2]=dyPid[chan].inputMode ;//Packet->use.data[2];
	Packet->use.data[3]=dyPid[chan].outputChannel;//Packet->use.data[3];
	Packet->use.data[4]=dyPid[chan].outputMode;//Packet->use.data[4];
	Packet->use.head.DataLegnth=4+5;
	Packet->use.head.Method=BOWLER_POST;

}
uint8_t ConfigDyPID(BowlerPacket * Packet){
	uint8_t chan = Packet->use.data[0];
	dyPid[chan].inputChannel =Packet->use.data[1];
	dyPid[chan].inputMode =Packet->use.data[2];
	dyPid[chan].outputChannel =Packet->use.data[3];
	dyPid[chan].outputMode =Packet->use.data[4];

	initPIDChans(chan);

	WritePIDvalues(&pidGroups[chan],&dyPid[chan],chan);
	return true; 
}



uint8_t GetPIDGroup(uint8_t channel){
	uint8_t mode = GetChannelMode(channel);
	uint8_t i;
	switch(mode){
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
	case IS_ANALOG_IN:
	case IS_DI:
		for(i=0;i<NUM_PID_GROUPS;i++){
			if(dyPid[i].inputChannel == channel){
				if(pidGroups[i].config.Enabled || vel[i].enabled )
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
				if(pidGroups[i].config.Enabled || vel[i].enabled)
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
	WritePIDvalues(&pidGroups[group],&dyPid[group],group);
}

void trigerPIDLimit(uint8_t chan,PidLimitType type,int32_t  tick){
	limits[chan].group=chan;
	limits[chan].type=type;
	limits[chan].value=tick;
	limits[chan].time=getMs();
}

PidLimitEvent * checkPIDLimitEventsMine(uint8_t group){
	return & limits[group];
}


int resetPositionMine(int group, int current){
	if(dyPid[group].inputChannel==DYPID_NON_USED)
			return current;
	if(dyPid[group].inputMode == IS_COUNTER_INPUT_INT){
		SetCounterInput(dyPid[group].inputChannel,current);
	}else if(dyPid[group].inputMode == IS_ANALOG_IN){
		current=GetValFromAsync(dyPid[group].inputChannel);
	}else if(dyPid[group].inputMode == IS_DI){
		current=GetDigitalValFromAsync(dyPid[group].inputChannel);
	}
	return current;
}

float getPositionMine(int group){
	if(dyPid[group].inputChannel==DYPID_NON_USED||
			((pidGroups[group].config.Enabled == false)  && (vel[group].enabled==false) ))
		return 0;

	LONG pos = 0;
	//print_I("\nGetting PID value from group: ");p_int_I(chan->channel);print_I(" of mode: ");printMode(chan->inputMode);print_I(" From channel: ");p_int_I(chan->inputChannel);print_I("\n");
	switch(dyPid[group].inputMode){
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
		pos=GetCounterByChannel( dyPid[group].inputChannel );
		break;
	case IS_ANALOG_IN:
		pos=GetValFromAsync(dyPid[group].inputChannel);
		break;
	case IS_DI:
		pos = GetDigitalValFromAsync(dyPid[group].inputChannel);
		break;
	}
	return ((float)pos);
}

void setOutputMine(int group, float v){

	if( dyPid[group].outputChannel==DYPID_NON_USED||
			((pidGroups[group].config.Enabled == false)  && (vel[group].enabled==false) ))
		return;
	Print_Level l = getPrintLevel();
	setPrintLevelNoPrint();
	int val = (int)(v);
	//uint8_t center = getBcsIoDataTable()[dyPid[group].outputChannel].PIN.currentConfiguration;

	if(dyPid[group].outputMode == IS_SERVO){
		val += 128;
		if (val>254)
			val=254;
		if(val<0)
			val=0;
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
		print_I(" Setting PID output, was ");p_int_I(dyPid[group].outVal);print_I(" is now: ");p_int_I(set);print_I(" on DyIO chan: ");p_int_I(dyPid[group].outputChannel);print_I(", ");
	}
	dyPid[group].outVal=set;

	println_I("PID setting output for group: ");p_int_I(group);
	SetChannelValueCoProc(dyPid[group].outputChannel,dyPid[group].outVal);
	setPrintLevel(l);
}


