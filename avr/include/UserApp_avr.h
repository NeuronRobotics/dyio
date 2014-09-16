/*
 * UserApp.h
 *
 *  Created on: Jan 2, 2010
 *      Author: hephaestus
 */

#ifndef USERAPP_H_
#define USERAPP_H_

//#define WPIRBE
#include <math.h>
#include "Bowler/Bowler.h"

#include "Namespace/Namespace_bcs_io.h"
#include "Namespace/Namespace_bcs_io_setmode.h"

#include "DyIOApp/HardwareProfile.h"

#include "DyIO/DyIO_def.h"
#include "DyIOApp/Power.h"
#include "DyIOApp/Servo.h"
#include "DyIOApp/AVR_IO.h"
#include "DyIOApp/ADC.h"
#include "DyIOApp/PWM.h"
#include "DyIOApp/EEPROM.h"
#include "DyIOApp/UARTPassThrough.h"
#include "DyIOApp/DCMotorDriver.h"
#include "DyIOApp/Push.h"


#include "DyIOApp/SPISlave.h"
#if defined(USE_AS_LIBRARY)
#include "DyIOApp/DyIOLib.h"
#endif


void UserInit(void);
void UserRun(void);
void AsynAck(void);

BOOL checkAnalog();
UINT16 getAnv(BYTE pin);
BOOL getDig(BYTE pin);
BOOL checkDigital();
void initPinState(BYTE i);
void initBluetooth();

BOOL avrAsyncCallbackPtr(BowlerPacket *Packet);
void SetNewConfigurationDataTable(BYTE pin, INT32 value);
NAMESPACE_LIST * get_internalNamespace();



#if defined(ROBOSUB_DEMO)
	#define DIGO			0x6f676964 // 'digo'  Comment
#endif


#endif /* USERAPP_H_ */
