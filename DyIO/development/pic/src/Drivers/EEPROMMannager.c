/*
 * EEPROMMannager.c
 *
 *  Created on: Mar 19, 2010
 *      Author: hephaestus
 */

#include "UserApp.h"

static pid_vales pidEEPRomVal[NUM_PID_GROUPS];
#define pidValSize sizeof(pid_vales)
#define PID_VAL_END ((pidValSize*(NUM_PID_GROUPS)))
#define PPM_END	     (PID_VAL_END+NUM_PPM_CHAN)
#define BROWNOUT_START  (PPM_END+1)
#define BROWNOUT_END 	(BROWNOUT_START+1)

BYTE loadEEDone=FALSE;
void LoadEEstore(void){
	if(loadEEDone)
		return;
	println_I("Loading eeprom data");
	loadEEDone=TRUE;
	int i;
	for (i=0;i<NUM_PID_GROUPS;i++){
		GetEEPRomData((pidValSize*i),(pidValSize*i)+pidValSize,pidEEPRomVal[i].stream);
	}
	println_I("Done loading eeprom data");
}
void LoadPIDvals(AbsPID * pid, DYIO_PID * dy){
	LoadEEstore();
	BYTE i = pid->channel;
	if(pidEEPRomVal[i].outputChannel==pidEEPRomVal[i].inputChannel)
		return;
	if(pidEEPRomVal[i].outputChannel>=GetNumberOfIOChannels() ||pidEEPRomVal[i].inputChannel>=GetNumberOfIOChannels() )
		return;
	if(pidEEPRomVal[i].outputMode==pidEEPRomVal[i].inputMode)
		return;
	println_I("Using values for chan: ");p_int_I(i);
	pid->Enabled=pidEEPRomVal[i].Enabled;
	pid->Polarity=pidEEPRomVal[i].Polarity;
	//pidChans->Async=pidEEPRomVal[i].Async;
	dy->inputMode=pidEEPRomVal[i].inputMode;
	dy->outputMode=pidEEPRomVal[i].outputMode;
	dy->outputChannel=pidEEPRomVal[i].outputChannel;
	dy->inputChannel=pidEEPRomVal[i].inputChannel;

	pid->K.P=pidEEPRomVal[i].K.P;
	pid->K.I=pidEEPRomVal[i].K.I;
	pid->K.D=pidEEPRomVal[i].K.D;
}

void WritePIDvalues(AbsPID * pid, DYIO_PID * dy){
	BYTE i = pid->channel;
	pidEEPRomVal[i].Enabled= pid->Enabled;
	pidEEPRomVal[i].Polarity=pid->Polarity;
	pidEEPRomVal[i].Async=pid->Async;
	pidEEPRomVal[i].inputMode=dy->inputMode;
	pidEEPRomVal[i].outputMode=dy->outputMode;
	pidEEPRomVal[i].inputChannel=dy->inputChannel;
	pidEEPRomVal[i].outputChannel=dy->outputChannel;
	pidEEPRomVal[i].K.P=pid->K.P;
	pidEEPRomVal[i].K.I=pid->K.I;
	pidEEPRomVal[i].K.D=pid->K.D;
	SetEEPRomData((pidValSize*i),(pidValSize*i)+pidValSize,pidEEPRomVal[i].stream);
}
void writePPMLink(BYTE * vals){
	SetEEPRomData(PID_VAL_END,PID_VAL_END+NUM_PPM_CHAN,vals);
}
void readPPMLink(BYTE * vals){
	GetEEPRomData(PID_VAL_END,PID_VAL_END+NUM_PPM_CHAN,vals);
}

void setEEBrownOutDetect(BOOL b){
	BYTE tmp = b?1:0;
	SetEEPRomData(BROWNOUT_START,BROWNOUT_END,&tmp);
}
BOOL getEEBrownOutDetect(){
	BYTE tmp =0;
	GetEEPRomData(BROWNOUT_START,BROWNOUT_END,&tmp);
	return tmp;
}





