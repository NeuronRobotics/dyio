/*
 * PID.h
 *
 *  Created on: Feb 6, 2010
 *      Author: hephaestus
 */

#ifndef PID_H_
#define PID_H_

#define NUM_PID_GROUPS 8
#define NOT_USED_IN_PID 0xff
void GetConfigDyPID(BowlerPacket * Packet);
uint8_t ConfigDyPID(BowlerPacket * Packet);
void InitPID(void);

void trigerPIDLimit(uint8_t chan,PidLimitType type,int32_t  tick);

uint8_t GetPIDGroup(uint8_t channel);
void pushPPMPacket(void);

#endif /* PID_H_ */
