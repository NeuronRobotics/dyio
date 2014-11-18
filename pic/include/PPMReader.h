/**
 * @filePPMReader.h
 *
 *  Created on: Feb 18, 2011
 * @author Kevin Harrington
 */

#ifndef PPMREADER_H_
#define PPMREADER_H_


void pushPPMPacket(void);
void runPPMEvent(void);
void RunPPMCheck(void);
void clearPPM(uint8_t chan);
void startPPM(uint8_t chan);

void ConfigPPMFromArray(uint8_t * data);

void GetPPMDataToPacket(BowlerPacket * Packet);
void ConfigPPM(BowlerPacket * Packet);
int GetPPMDataToArray(uint8_t * data);

#endif /* PPMREADER_H_ */
