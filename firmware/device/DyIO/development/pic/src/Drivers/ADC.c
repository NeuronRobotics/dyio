/*
 * ADC.c
 *
 *  Created on: Feb 12, 2010
 *      Author: hephaestus
 */

#include "UserApp.h"
UINT32 getDyIOVoltage(BYTE chan);

BOOL init = FALSE;
#define AVG_SIZE 20

typedef struct __attribute__((__packed__)) _ROLLINGAVG
{
	UINT32 rawAvg[AVG_SIZE];
	float avgSum;
	BYTE avgIndex;
	BYTE adcChan;
} ROLLINGAVG;

ROLLINGAVG adc[4];
float lastHighTime=0;
float lastLowTime=0;

static BOOL lockOutRail = FALSE;
static BOOL externalLock=FALSE;
INT32 calc(ROLLINGAVG * avg){
	UINT32 v=getDyIOVoltage(avg->adcChan);
//	avg->avgSum+=v;
//	avg->rawAvg[avg->avgIndex ++]=v;
//	if (avg->avgIndex == AVG_SIZE)
//		avg->avgIndex=0;
//	avg->avgSum-=(float)avg->rawAvg[avg->avgIndex];
//	return (avg->avgSum/AVG_SIZE);
	return v;
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
#define timeOfVoltageflux .2
RunEveryData lockOutTimeout;
BYTE GetRawVoltageCode(BYTE bank){

	float rv =GetRawVoltage();
	if(lockOutRail == FALSE){
		float current = getMs();
		float diffLow = (current-lastLowTime);
		float diffHigh = (current-lastHighTime);
		if((current>lastLowTime) && (current>lastHighTime)){
			if((lastHighTime != 0) &&  (lastLowTime != 0)){
				if((diffLow<timeOfVoltageflux) && (diffHigh<timeOfVoltageflux)){
					lockOutRail=TRUE;
					lockOutTimeout.MsTime=current;
					lockOutTimeout.setPoint=1000;
					UpstreamPushPowerChange();
					println_I("Power fluctuation detected\n");
					println_I("Current Time: ");p_fl_I(current);
					println_I("Last low time: ");p_fl_I(lastLowTime);print_I(", ");p_fl_I(diffLow);
					println_I("Last high time : ");p_fl_I(lastHighTime);print_I(", ");p_fl_I(diffHigh);
				}
			}
		}
	}else{
		if(RunEvery(&lockOutTimeout)>0){
			lockOutRail = FALSE;
			UpstreamPushPowerChange();
			println_I("Power fluctuation Reset");
		}
		return 0;
	}
	if(bank==0){
		rv = GetRail0Voltage();
	}else{
		rv = GetRail1Voltage();
	}
	if(rv>RawVoltageMin){
		lastHighTime = getMs();
		if(externalLock==TRUE)
			return 3;
		return 1;
	}else {
		lastLowTime = getMs();
		if(rv<3000 && externalLock==FALSE){
			return 2;
		}else{
			return 0;
		}
	}
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

UINT32 getDyIOVoltage(BYTE chan){
	InitADC();
	float scale = 16.283951;
	UINT32 raw = getAdcRaw(chan, 5);
	UINT32 volt = (UINT32)(((float)raw)*scale);
	return volt;
}
