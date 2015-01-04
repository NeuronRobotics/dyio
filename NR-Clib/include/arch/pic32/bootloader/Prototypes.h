/*
 * Prototypes.h
 *
 *  Created on: May 30, 2010
 *      Author: hephaestus
 */

#ifndef PROTOTYPES_H_
#define PROTOTYPES_H_

void InitializeSystem(void);
void RunApplications(void);
void writeLine(BowlerPacket * Packet);
void writeWordFlash(uint32_t address,uint32_t data);
void eraseFlash(void);
void BlinkUSBStatus(void);

void InitSPI(void);
void StopSPI(void);
uint8_t GetByteSPI(uint8_t b);
void avrSPIProg(BowlerPacket * Packet);
void eraseAVR(void);
void GetAVRid(uint8_t * buffer);
void HoldAVRReset(void);

void PowerCycleAVR();

void ReleaseAVRReset(void);
boolean AVRDone(void);
void AVRFlush(void);
void runAVRByteWrites(void);
boolean writeAVRLowByte(uint8_t data, uint16_t address);
boolean writeAVRHighByte(uint8_t data, uint16_t address);
boolean writeAVRTempFlashPageHighByte(uint8_t data, uint8_t address);
boolean writeAVRTempFlashPageLowByte(uint8_t data, uint8_t address);

void writeLowFuse();
void writeHighFuse();
void writeExtendedFuse();
void programMode(void);

#endif /* PROTOTYPES_H_ */
