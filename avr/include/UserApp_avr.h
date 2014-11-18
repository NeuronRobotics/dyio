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
#include "arch/AVR/BowlerConfig.h"
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

boolean checkAnalog();
uint16_t getAnv(uint8_t pin);
boolean getDig(uint8_t pin);
boolean checkDigital();
void initPinState(uint8_t i);
void initBluetooth();

boolean avrAsyncCallbackPtr(BowlerPacket *Packet);
void SetNewConfigurationDataTable(uint8_t pin, int32_t value);
NAMESPACE_LIST * get_internalNamespace();



#if defined(ROBOSUB_DEMO)
	#define DIGO			0x6f676964 // 'digo'  Comment
#endif


#endif /* USERAPP_H_ */
