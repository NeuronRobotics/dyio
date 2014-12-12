/**
 * PID.c
 *
 *  Created on: Aug 8, 2009
 *      Author: hephaestus
 */

#include "UserApp.h"

AbsPID 			pidGroups[NUM_PID_GROUPS];
DYIO_PID 		dyPid[NUM_PID_GROUPS];
PidLimitEvent	limits[NUM_PID_GROUPS];

#define DYPID_NON_USED 0xff

float getPositionMine(int group);
void setOutputMine(int group, float val);
int resetPositionMine(int group, int target);
//void pidAsyncCallbackMine();
void onPidConfigureMine(int);
PidLimitEvent * checkPIDLimitEventsMine(uint8_t group);



RunEveryData force[NUM_PID_GROUPS];

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

//	println_W("PID In chan: ");
//	p_int_W(dyPid[group].inputChannel);
//	println_W(" mode: ");
//	printMode(dyPid[group].inputMode, WARN_PRINT);
//	println_W("PID Out chan: ");
//	p_int_W(dyPid[group].outputChannel);
//	println_W(" mode: ");
	printMode(dyPid[group].outputMode, WARN_PRINT);
	SetCoProcMode(dyPid[group].inputChannel,dyPid[group].inputMode);
	SetCoProcMode(dyPid[group].outputChannel,dyPid[group].outputMode);
	forceModeDownstream(dyPid[group].inputChannel);
	forceModeDownstream(dyPid[group].outputChannel);
	//SyncModes();

	if(dyPid[group].inputMode== IS_ANALOG_IN){
		pidGroups[group].SetPoint=GetValFromAsync(dyPid[group].inputChannel);
	}else{
		pidGroups[group].SetPoint=0;
	}
	SetPIDCalibrateionState(group, CALIBRARTION_DONE);
	getPidGroupDataTable( group)->config.Async=true;
	getPidGroupDataTable( group)->config.Enabled=true;

}
boolean asyncCallback(BowlerPacket *Packet){
    PutBowlerPacket(Packet);// This only works with USB and UART
    return true; 
}
void InitPID(void){
	//println_I("Starting PID initialization ");
	uint8_t i;
	//uint16_t loop;
	for (i=0;i<NUM_PID_GROUPS;i++){
		//DyPID values
		dyPid[i].inputChannel=DYPID_NON_USED;
		dyPid[i].outputChannel=DYPID_NON_USED;
		dyPid[i].inputMode=0;
		dyPid[i].outputMode=0;
		dyPid[i].flagValueSync=false;

                pidGroups[i].config.tipsScale=1.0;
                pidGroups[i].config.Enabled = false;
                pidGroups[i].config.Async = 1;
                pidGroups[i].config.IndexLatchValue = 0;
                pidGroups[i].config.stopOnIndex = 0;
                pidGroups[i].config.useIndexLatch = 0;
                pidGroups[i].config.K.P = .1;
                pidGroups[i].config.K.I = 0;
                pidGroups[i].config.K.D = 0;
                pidGroups[i].config.V.P = .1;
                pidGroups[i].config.V.D = 0;
                pidGroups[i].config.Polarity = 0;
                pidGroups[i].config.stop = 0;
                pidGroups[i].config.upperHistoresis = 0;
                pidGroups[i].config.lowerHistoresis = 0;
                pidGroups[i].config.offset = 0.0;
                pidGroups[i].config.calibrationState = CALIBRARTION_DONE;
                pidGroups[i].interpolate.set=0;
                pidGroups[i].interpolate.setTime=0;
                pidGroups[i].interpolate.start=0;
                pidGroups[i].interpolate.startTime=0;

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
                                NUM_PID_GROUPS,
                                &getPositionMine,
                                &setOutputMine,
                                &resetPositionMine,
                                &onPidConfigureMine,
                                &checkPIDLimitEventsMine);

	for (i=0;i<NUM_PID_GROUPS;i++){
		printPIDvals(i);
		if(pidGroups[i].config.Enabled){
			println_I("PID ");p_int_I(i);
			initPIDChans(i);

			int value = getPositionMine(i);
                        pidGroups[i].CurrentState=value;
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

void runPIDConfigurationValueSync(){
	int i;
	for (i=0;i<NUM_PID_GROUPS;i++){
		if(dyPid[i].flagValueSync == true){
			dyPid[i].flagValueSync = false;
			WritePIDvalues(&pidGroups[i],&dyPid[i],i);
		}
	}
}

uint8_t ConfigDyPID(BowlerPacket * Packet){
	uint8_t chan = Packet->use.data[0];
	dyPid[chan].inputChannel =Packet->use.data[1];
	dyPid[chan].inputMode =Packet->use.data[2];
	dyPid[chan].outputChannel =Packet->use.data[3];
	dyPid[chan].outputMode =Packet->use.data[4];

	initPIDChans(chan);
	dyPid[chan].flagValueSync = true;
	//WritePIDvalues(&pidGroups[chan],&dyPid[chan],chan);
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
				if(pidGroups[i].config.Enabled || pidGroups[i].vel.enabled )
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
				if(pidGroups[i].config.Enabled ||  pidGroups[i].vel.enabled)
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

	dyPid[group].flagValueSync = true;
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
	if(dyPid[group].inputChannel==DYPID_NON_USED)
		return 0;

	int32_t pos = 0;

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
            default:
                return 0;
	}
	//println_W("Get PID ");p_int_W(group);print_W(" is ");p_int_W(pos);
	return ((float)pos);
}

void setOutputMine(int group, float v){

	if( dyPid[group].outputChannel==DYPID_NON_USED)
		return;
	Print_Level l = getPrintLevel();
	//setPrintLevelNoPrint();
	int val = (int)(v);

	if(dyPid[group].outputMode == IS_SERVO){
		val += 128;
		if (val>255)
			val=255;
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
	//print_W("  set ");p_int_W(group);print_W(" to ");p_int_W(set);

	dyPid[group].outVal=set;

	SetChannelValueCoProc(dyPid[group].outputChannel,dyPid[group].outVal);
	setPrintLevel(l);
}


