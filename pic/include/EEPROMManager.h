/*
 * EEPROMManager.h
 *
 *  Created on: Mar 19, 2010
 *      Author: hephaestus
 */

#ifndef EEPROMMANAGER_H_
#define EEPROMMANAGER_H_


#define NAMESIZE 17
#define LOCKSIZE 5

#define NAMESTART 0
#define LOCKSTART (NAMESIZE+NAMESTART)
#define DATASTART (LOCKSTART +LOCKSIZE)
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
		uint8_t stream[sizeof(struct _local_pid)];
	};
} pid_vales;

typedef struct _EESTORAGE
{

		uint8_t lockByte;
		pid_vales pid[NUM_PID_GROUPS];
		uint8_t end;

} EESTORAGE;

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
