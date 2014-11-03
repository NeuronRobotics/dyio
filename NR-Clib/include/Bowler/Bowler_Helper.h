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
uint16_t READY(BowlerPacket * Packet,uint8_t code,uint8_t trace);
uint16_t ERR(BowlerPacket * Packet,uint8_t code,uint8_t trace);

uint16_t GetDataLegnth(uint8_t *buffer);

uint16_t SetPacketLegnth(BowlerPacket * Packet,uint8_t len);
uint16_t GetPacketLegnth(BowlerPacket * Packet);


uint32_t Bytes2Int32(uint8_t a,uint8_t b,uint8_t c,uint8_t d);

unsigned long GetRPCValue(char * data);

unsigned char CheckAddress(uint8_t * one,uint8_t * two);

void LoadCorePacket(BowlerPacket * Packet);

uint8_t CalcCRC(BowlerPacket *Packet);
void SetCRC(BowlerPacket * Packet);
unsigned char CheckCRC(BowlerPacket * Packet);
void copyPacket(BowlerPacket * from,BowlerPacket * to);


float interpolate(INTERPOLATE_DATA * data, float currentTime);

boolean bound(float target, float actual, float plus, float minus);


void set8bit(BowlerPacket * Packet,uint8_t val, uint8_t offset);

void set16bit(BowlerPacket * Packet,int16_t val, uint8_t offset);

void set32bit(BowlerPacket * Packet,int32_t val, uint8_t offset);

void setString(BowlerPacket * Packet, char * val, uint8_t offset);

int32_t get32bit(BowlerPacket * Packet, uint8_t offset);

int32_t get16bit(BowlerPacket * Packet, uint8_t offset);


#endif /* BOWLER_HELPER_H_ */
