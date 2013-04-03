/*
 * UserApp.h
 *
 *  Created on: Jan 2, 2010
 *      Author: hephaestus
 */

#ifndef USERAPP_H_
#define USERAPP_H_

#define RELEASE_BOARD
#if !defined(RELEASE_BOARD)
#define LAST_DEV_BOARD
#endif
#if !defined(__PIC32MX__)
#define __PIC32MX__
#define __C32__
#include "arch/pic32/BowlerConfig.h"
#endif

#include "Bowler/Bowler.h"
#include "Namespace/Namespace_bcs_io.h"
#include "Namespace/Namespace_bcs_io_setmode.h"

#include "DyIO/DyIO_def.h"
#include "CoProcCom.h"
#include "PIC_IO.h"
#include "PID.h"
#include "Power.h"
#include "Counter.h"
#include "Switches.h"
#include "BowlerPush.h"
#include "ADC.h"
#include "EEPROMManager.h"
#include "SPI.h"
#include "AVRInterface.h"
#include "FlashStorage.h"
#include "SerialPassThrough.h"
#include "PPMReader.h"
#include "CartesianController.h"
#include "UartDMA.h"
#include "Bluetooth.h"

#include "arch/pic32/BowlerConfig.h"



void UserInit(void);
void UserRun(void);

void UpdateAVRLED(void);
void setHeartBeatState( BOOL hb, int time);
int getHeartBeatTime();
BOOL getHeartBeatLock();

void buttonCheck(BYTE code);
void MyServer();

#endif /* USERAPP_H_ */
