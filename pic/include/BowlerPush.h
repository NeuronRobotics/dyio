/*
 * Push.h
 *
 *  Created on: Feb 11, 2010
 *      Author: hephaestus
 */

#ifndef PUSH_H_
#define PUSH_H_

void forceValueDownstream(int8_t pin);
void forceModeDownstream(int8_t pin);
void LoadDefaultValues();
void LoadCorePacket(BowlerPacket * pack);
void pushError(uint8_t zone,uint8_t trace);

uint8_t GetChannelValueCoProc(uint8_t PIN);

void PushAllAsync();
void PushADCChange(uint8_t pin,uint16_t state);
void PushDIOChange(uint8_t pin,uint8_t state);
void PushCounterChange(uint8_t pin,int64_t state);
boolean GetSerialStream(BowlerPacket * packet);

void POWER(BowlerPacket * packet);
void SetCoProcLED(boolean a, boolean b, int batt);
void DownstreamPowerChange(void);
void UpstreamPushPowerChange(uint8_t r0,uint8_t r1, uint16_t voltage, uint8_t override);
void UpstreamPushSerialStream(void);
void UpstreamPushSPIlStream(void);
void GetAllModes(BowlerPacket * pack);\

void PushCoProcAsync(void);

void PushADCval(uint8_t pin,uint16_t val);
void PushDIval(uint8_t pin,uint8_t val);
void DownstreamSerialStreamSet(BYTE_FIFO_STORAGE * txBuffer);

void DownstreamSerialStreamGet(BYTE_FIFO_STORAGE * rxBuffer);


#endif /* PUSH_H_ */
