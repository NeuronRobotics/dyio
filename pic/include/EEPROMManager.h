/*
 * EEPROMManager.h
 *
 *  Created on: Mar 19, 2010
 *      Author: hephaestus
 */

#ifndef EEPROMMANAGER_H_
#define EEPROMMANAGER_H_

#define NAMESTART 0
#define LOCKSTART 17
#define DATASTART 22
#define DATAVALID 37
#include "Bowler/AbstractPID.h"
struct _local_pid{
        unsigned 					:5;
        unsigned		Async		:1;
        unsigned		Polarity	:1;
        unsigned		Enabled 	:1;
        unsigned 		char inputMode;
        unsigned 		char inputChannel;
        unsigned 		char outputMode;
        unsigned 		char outputChannel;
        struct{
            double P;
            double I;
            double D;
        }K;
};
typedef struct  _pid_vales
{
	union{
		struct _local_pid data;
		BYTE stream[sizeof(struct _local_pid)];
	};
} pid_vales;

typedef struct _EESTORAGE
{

		BYTE lockByte;
		pid_vales pid[NUM_PID_GROUPS];
		BYTE end;

} EESTORAGE;

void readPPMLink(BYTE * vals);
void writePPMLink(BYTE * vals);

void setEEBrownOutDetect(BOOL b);
BOOL getEEBrownOutDetect();

void LoadEEstore(void);
void WritePIDvalues(AbsPID * pid, DYIO_PID * dy,int group);
void LoadPIDvals(AbsPID * pid, DYIO_PID * dy,int group);

BOOL GetName(char * name);
void SetName(char * name);
BOOL GetLockCode(char * name);
void SetLockCode(char * code);
void SetEEPRomData(BYTE start,BYTE stop,BYTE * data);
void GetEEPRomData(BYTE start,BYTE stop,BYTE * data);


#endif /* EEPROMMANAGER_H_ */
