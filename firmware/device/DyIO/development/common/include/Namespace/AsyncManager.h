/*
 * AsyncManager.h
 *
 *  Created on: Mar 19, 2010
 *      Author: hephaestus
 */

#ifndef ASYNCMANAGER_H_
#define ASYNCMANAGER_H_

//#define ASYN_RDY(i) ((pushAsyncReady(i)==TRUE)&&(IsAsync(i) == TRUE)&& (GetPIDGroup(i) == NOT_USED_IN_PID))

#define ASYN_RDY(i) ((pushAsyncReady(i)==TRUE)&&(IsAsync(i) == TRUE))

BOOL IsAsync(BYTE channel);

void populateGACV(BowlerPacket * Packet);
void initAdvancedAsync();

void ProcessAsyncData(BowlerPacket * Packet);
//int GetAnalogValFromAsync(BYTE pin);
void SetValFromAsync(int pin, int value);
int GetValFromAsync(int pin);
//int  GetDigitalValFromAsync(BYTE pin);
void RunAsync(void);
void StopAsync(void);
void StartAsync(void);
void SyncSessionTime(float time);

void setAsync(BYTE channel,BOOL async);
void setAsyncLocal(BYTE channel,BOOL async);


#define		NOTEQUAL 		0
#define		DEADBAND 		1
#define		THRESHHOLD 		2
#define		AUTOSAMP 		3


#define		ASYN_BOTH 		0
#define		ASYN_RISING 	1
#define		ASYN_FALLING 	2


typedef struct _AdvancedAsyncData{
	INT32			previousVal;
	INT32			currentVal;
	RunEveryData 	time;
	BYTE		type;
	BYTE 		enabled;
	struct{
		INT32 	val;
	}deadBand;
	struct{
		INT32 	val;
		BYTE edge;
	}threshhold;
}AdvancedAsyncData;

BOOL pushAsyncReady( BYTE pin);
void startAdvancedAsyncDefault(BYTE pin);
void setAsyncLocal(BYTE channel,BOOL async);

#endif /* ASYNCMANAGER_H_ */
