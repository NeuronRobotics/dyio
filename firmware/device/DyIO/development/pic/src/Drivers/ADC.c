/*
 * ADC.c
 *
 *  Created on: Feb 12, 2010
 *      Author: hephaestus
 */

#include "UserApp.h"
float getVolt(BYTE chan);

BOOL init = FALSE;
#define AVG_SIZE 20

typedef struct __attribute__((__packed__)) _ROLLINGAVG
{
	float rawAvg[AVG_SIZE];
	float avgSum;
	BYTE avgIndex;
	BYTE adcChan;
} ROLLINGAVG;

ROLLINGAVG adc[4];
float lastHighTime=0;
float lastLowTime=0;

static BOOL lockOutRail = FALSE;
static BOOL externalLock=FALSE;
float calc(ROLLINGAVG * avg){
	float v=getVolt(avg->adcChan);
	avg->avgSum+=v;
	avg->rawAvg[avg->avgIndex ++]=v;
	if (avg->avgIndex == AVG_SIZE)
		avg->avgIndex=0;
	avg->avgSum-=(float)avg->rawAvg[avg->avgIndex];
	return (avg->avgSum/AVG_SIZE);
}
void InitADC(void){
	if(init==TRUE)
		return;
	init = TRUE;
	println_I("Start Initialized the ADC");
	BYTE i,j;

	adc[0].adcChan=15;
	adc[1].adcChan=12;
	adc[2].adcChan=14;
	adc[3].adcChan=13;

	for(i=0;i<4;i++){
		InitADCHardware(adc[i].adcChan);
		adc[i].avgSum=0;
		adc[i].avgIndex=0;
		for(j=0;j<AVG_SIZE;j++){
			calc(&adc[i]);
		}
	}
	println_I("Finish Initializing the ADC");


}

BOOL isLocked(void){
	return lockOutRail;
}
BOOL isActive(void){
	return externalLock;
}
void unlockServos(){
	externalLock=FALSE;
}
void lockServos(){
	externalLock=TRUE;
}
#define flux 200
RunEveryData lockOutTimeout;
BYTE GetRawVoltageCode(BYTE bank){
	BYTE back;

	float rv =GetRawVoltage();
	if(lockOutRail == FALSE){
		float current = getMs();
		float diffLow = (current-lastLowTime);
		float diffHigh = (current-lastHighTime);
		if((current>lastLowTime) && (current>lastHighTime)){
			if((lastHighTime != 0) &&  (lastLowTime != 0)){
				if((diffLow<flux) && (diffHigh<flux)){
					lockOutRail=TRUE;
					lockOutTimeout.MsTime=current;
					lockOutTimeout.setPoint=1000;
					UpstreamPushPowerChange();
				}
			}
		}
	}else{
		if(RunEvery(&lockOutTimeout)>0){
			lockOutRail = FALSE;
			UpstreamPushPowerChange();
		}
		return 0;
	}
	if(bank==0){
		rv = GetRail0Voltage();
	}else{
		rv = GetRail1Voltage();
	}
	if(rv>RawVoltageMin-1.5){
		lastHighTime = getMs();
		if(externalLock==TRUE)
			return 3;
		back=1;
	}else {
		lastLowTime = getMs();
		if(rv<3.0 && externalLock==FALSE){
			back=2;
		}else{
			back=0;
		}
	}
	return back;
}

float GetRawVoltage(void){
	return calc(&adc[2]);
}

float GetRawVoltagePostFuse(void){
	return calc(&adc[3]);
}

float GetRail0Voltage(void){
	return calc(&adc[0]);
}

float GetRail1Voltage(void){
	return calc(&adc[1]);
}

float getVolt(BYTE chan){
	InitADC();
//	AD1CHSbits.CH0SA = chan;
//	AD1CON1bits.SAMP = 1;
//	Delay10us(5);
//	AD1CON1bits.SAMP = 0;
//	RUN_EVERY timeout = {getMs(),2};
//	while (AD1CON1bits.DONE == 0 && RunEvery(&timeout)==0){
//		// Wait for ADC to finish
//		buttonCheck(2);
//	}
//	if(AD1CON1bits.DONE == 1){
//		//init = FALSE;
//		return 0;
//	}
//	AD1CHS =0;
//	WORD tmp = ADC1BUF0;
//	float back = ((float)tmp)*0.017283951;
//	println_I("Voltage on chan:");
//	p_int_I(chan);
//	print_I(" is ");
//	p_int_I(tmp);
//	print_I(" is scaled to ");
//	p_fl_I(back);
	return getAdcVoltage(chan, 10);
}
