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
void writeWordFlash(DWORD address,DWORD data);
void eraseFlash(void);
void BlinkUSBStatus(void);

void InitSPI(void);
void StopSPI(void);
BYTE GetByteSPI(BYTE b);
void avrSPIProg(BowlerPacket * Packet);
void eraseAVR(void);
void GetAVRid(BYTE * buffer);
void HoldAVRReset(void);
void ReleaseAVRReset(void);
BOOL AVRDone(void);
void AVRFlush(void);
void runAVRByteWrites(void);
BOOL writeAVRLowByte(BYTE data, UINT16 address);
BOOL writeAVRHighByte(BYTE data, UINT16 address);
BOOL writeAVRTempFlashPageHighByte(BYTE data, BYTE address);
BOOL writeAVRTempFlashPageLowByte(BYTE data, BYTE address);

void writeLowFuse();
void writeHighFuse();
void writeExtendedFuse();
void programMode(void);

#endif /* PROTOTYPES_H_ */
