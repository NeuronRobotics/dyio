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
#define __32MX440F128H__
#define __PIC32_FEATURE_SET__ 440
#define __LANGUAGE_C__
#include "arch/pic32/BowlerConfig.h"

#endif
//#include <peripheral/legacy/int_3xx_4xx_legacy.h>

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
#include "arch/pic32/FlashStorage.h"
#include "SerialPassThrough.h"
#include "PPMReader.h"
#include "CartesianController.h"
#include "UartDMA.h"
#include "Bluetooth.h"

#include "arch/pic32/BowlerConfig.h"

#include <proc/p32mx440f128h.h>
#include <proc/ppic32mx.h>


void UserInit(void);
void UserRun(void);

void UpdateAVRLED(void);
void setHeartBeatState( boolean hb, int time);
int getHeartBeatTime();
boolean getHeartBeatLock();

void buttonCheck(uint8_t code);
void MyServer();
void UserInit(void);
void InitializeDyIODataTableManager();

#define MAX_RETRY 5
#define DELAY_TIMEOUT 200

#endif /* USERAPP_H_ */
