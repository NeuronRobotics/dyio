/*
 * AsyncManager.h
 *
 *  Created on: Mar 19, 2010
 *      Author: hephaestus
 */

#ifndef ASYNCMANAGER_H_
#define ASYNCMANAGER_H_

//#define ASYN_RDY(i) ((pushAsyncReady(i)==true) &&(IsAsync(i) == true) && (GetPIDGroup(i) == NOT_USED_IN_PID))

//#define ASYN_RDY(i) ((pushAsyncReady(i)==true) &&(IsAsync(i) == true) )

boolean IsAsync(uint8_t channel);

void populateGACV(BowlerPacket * Packet);
void initAdvancedAsync();

void ProcessAsyncData(BowlerPacket * Packet);
//int GetAnalogValFromAsync(uint8_t pin);
void SetValFromAsync(int pin, int value);
int GetValFromAsync(int pin);
int GetDigitalValFromAsync(uint8_t pin);

//int  GetDigitalValFromAsync(uint8_t pin);
void RunAsync(void);
void StopAsync(void);
void StartAsync(void);
void SyncSessionTime(float time);

void setAsync(uint8_t channel,boolean async);
void setAsyncLocal(uint8_t channel,boolean async);


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
	uint8_t 		enabled;
	struct{
		int32_t 	val;
	}deadBand;
	struct{
		int32_t 	val;
		uint8_t edge;
	}threshhold;
}AdvancedAsyncData;

boolean pushAsyncReady( uint8_t pin);
void startAdvancedAsyncDefault(uint8_t pin);
void setAsyncLocal(uint8_t channel,boolean async);
void configAdvancedAsyncNotEqual(uint8_t pin,float time);

#endif /* ASYNCMANAGER_H_ */
