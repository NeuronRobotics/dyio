/*
 * EEPROMManager.h
 *
 *  Created on: Mar 19, 2010
 *      Author: hephaestus
 */

#ifndef EEPROMMANAGER_H_
#define EEPROMMANAGER_H_



#include "Bowler/AbstractPID.h"


void readPPMLink(uint8_t * vals);
void writePPMLink(uint8_t * vals);

void setEEBrownOutDetect(boolean b);
boolean getEEBrownOutDetect();

void LoadEEstore(void);
void WritePIDvalues(AbsPID * pid, DYIO_PID * dy,int group);
void LoadPIDvals(AbsPID * pid, DYIO_PID * dy,int group);

boolean GetName(char * name);
void SetName(char * name);
boolean GetLockCode(char * name);
void SetLockCode(char * code);
void SetEEPRomData(uint8_t start,uint8_t stop,uint8_t * data);
void GetEEPRomData(uint8_t start,uint8_t stop,uint8_t * data);


#endif /* EEPROMMANAGER_H_ */
