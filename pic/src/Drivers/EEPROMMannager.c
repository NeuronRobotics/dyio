/*
 * EEPROMMannager.c
 *
 *  Created on: Mar 19, 2010
 *      Author: hephaestus
 */

#include "UserApp.h"

pid_vales pidEEPRomVal[NUM_PID_GROUPS];
#define pidValSize sizeof(pid_vales)
#define PID_VAL_END ((pidValSize*(NUM_PID_GROUPS)))
#define PPM_END	     (PID_VAL_END+NUM_PPM_CHAN)
#define BROWNOUT_START  (PPM_END+1)
#define BROWNOUT_END 	(BROWNOUT_START+1)

uint8_t loadEEDone=false; 
void LoadEEstore(void){
	if(loadEEDone)
		return;
	//println_I("Loading eeprom data");
	loadEEDone=true; 
	int i;
	for (i=0;i<NUM_PID_GROUPS;i++){
		GetEEPRomData((pidValSize*i),(pidValSize*i)+pidValSize,pidEEPRomVal[i].stream);
	}
	//println_I("Done loading eeprom data");
}
void LoadPIDvals(AbsPID * pid, DYIO_PID * dy,int group){
	LoadEEstore();
	uint8_t i = group;
	if(pidEEPRomVal[i].data.outputChannel==pidEEPRomVal[i].data.inputChannel)
		return;
	if(pidEEPRomVal[i].data.outputChannel>=GetNumberOfIOChannels() ||pidEEPRomVal[i].data.inputChannel>=GetNumberOfIOChannels() )
		return;
	if(pidEEPRomVal[i].data.outputMode==pidEEPRomVal[i].data.inputMode)
		return;
	//println_I("Using values for chan: ");p_int_I(i);
	pid->config.Enabled=pidEEPRomVal[i].data.Enabled;
	pid->config.Polarity=pidEEPRomVal[i].data.Polarity;
	//pidChans->Async=pidEEPRomVal[i].data.Async;
	dy->inputMode=pidEEPRomVal[i].data.inputMode;
	dy->outputMode=pidEEPRomVal[i].data.outputMode;
	dy->outputChannel=pidEEPRomVal[i].data.outputChannel;
	dy->inputChannel=pidEEPRomVal[i].data.inputChannel;

	pid->config.K.P=pidEEPRomVal[i].data.K.P;
	pid->config.K.I=pidEEPRomVal[i].data.K.I;
	pid->config.K.D=pidEEPRomVal[i].data.K.D;
}

void WritePIDvalues(AbsPID * pid, DYIO_PID * dy,int group){
	uint8_t i = group;
	pidEEPRomVal[i].data.Enabled= pid->config.Enabled;
	pidEEPRomVal[i].data.Polarity=pid->config.Polarity;
	pidEEPRomVal[i].data.Async=pid->config.Async;
	pidEEPRomVal[i].data.inputMode=dy->inputMode;
	pidEEPRomVal[i].data.outputMode=dy->outputMode;
	pidEEPRomVal[i].data.inputChannel=dy->inputChannel;
	pidEEPRomVal[i].data.outputChannel=dy->outputChannel;
	pidEEPRomVal[i].data.K.P=pid->config.K.P;
	pidEEPRomVal[i].data.K.I=pid->config.K.I;
	pidEEPRomVal[i].data.K.D=pid->config.K.D;
	SetEEPRomData((pidValSize*i),(pidValSize*i)+pidValSize,pidEEPRomVal[i].stream);
}
void writePPMLink(uint8_t * vals){
	SetEEPRomData(PID_VAL_END,PID_VAL_END+NUM_PPM_CHAN,vals);
}
void readPPMLink(uint8_t * vals){
	GetEEPRomData(PID_VAL_END,PID_VAL_END+NUM_PPM_CHAN,vals);
}

void setEEBrownOutDetect(boolean b){
	uint8_t tmp = b?1:0;
	SetEEPRomData(BROWNOUT_START,BROWNOUT_END,&tmp);
}
boolean getEEBrownOutDetect(){
	uint8_t tmp =0;
	GetEEPRomData(BROWNOUT_START,BROWNOUT_END,&tmp);
	return tmp;
}





