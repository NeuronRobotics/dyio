/**
 *
 * Copyright 2009 Neuron Robotics, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef BOWLER_HELPER_H_
#define BOWLER_HELPER_H_
#include "Defines.h"
#include "Bowler_Struct_Def.h"
unsigned short int READY(BowlerPacket * Packet,BYTE code,BYTE trace);
unsigned short int ERR(BowlerPacket * Packet,BYTE code,BYTE trace);

unsigned short int GetDataLegnth(BYTE *buffer);

unsigned short int SetPacketLegnth(BowlerPacket * Packet,BYTE len);
unsigned short int GetPacketLegnth(BowlerPacket * Packet);


unsigned long Bytes2Int32(BYTE a,BYTE b,BYTE c,BYTE d);

unsigned long GetRPCValue(char * data);

unsigned char CheckAddress(BYTE * one,BYTE * two);

void LoadCorePacket(BowlerPacket * Packet);

BYTE CalcCRC(BowlerPacket *Packet);
void SetCRC(BowlerPacket * Packet);
unsigned char CheckCRC(BowlerPacket * Packet);
void copyPacket(BowlerPacket * from,BowlerPacket * to);


typedef struct _INTERPOLATE_DATA
{
	float set;
	float start;
	float setTime;
	float startTime;
} INTERPOLATE_DATA;

float interpolate(INTERPOLATE_DATA * data, float currentTime);

BOOL bound(float target, float actual, float plus, float minus);


void set8bit(BowlerPacket * Packet,BYTE val, BYTE offset);

void set16bit(BowlerPacket * Packet,INT16 val, BYTE offset);

void set32bit(BowlerPacket * Packet,INT32 val, BYTE offset);

INT32 get32bit(BowlerPacket * Packet, BYTE offset);

INT32 get16bit(BowlerPacket * Packet, BYTE offset);


#endif /* BOWLER_HELPER_H_ */
