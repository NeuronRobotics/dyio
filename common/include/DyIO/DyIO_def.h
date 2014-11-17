/**
 *
 * Copyright 2009 Neuron Robotics, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include "Bowler/Bowler.h"
#include "Debug_DyIO.h"
#include "ChannelMode.h"
#include "ChannelValues.h"
#include "Bowler/AbstractPID.h"
#ifndef DYIO_DEF_H_
#define DYIO_DEF_H_

//#define ROBOSUB_DEMO

#define NUM_PINS   			24

#define SERVO_BOUND 		0

//#define MAJOR_REV			3
//#define MINOR_REV			7
//#define FIRMWARE_VERSION	19


//neuronrobotics.dyio
#define _REV				0x7665725f // '_rev'  Get the revision number
#define INFO				0x6f666e69 // 'info'  Get and set the name string
#define _PWR				0x7277705f // '_pwr'  Request the power state

//private internal RPC's for communication between the host and co processor
#define EEPD				0x64706565// Interface with the EEPROM
#define DASN			    0x6e736164 // 'dasn'  Get 8 bit Async data
#define AASN				0x6e736161 // 'aasn'  Get 16 bit Async data
#define SAVE				0x65766173 // 'save'  Get the save values for servos
#define _MAC				0x63616D5F// Provision MAC address
#define POVR				0x72766f70 // 'povr'  Power override packet

//bcs.pid.dypid
#define DPID				0x64697064 // 'dpid'  Dynamic PID

#define FLAG_BLOCK 0
#define FLAG_OK    1


#define PID_VAL_END ((pidValSize*(NUM_PID_GROUPS)))
#define PPM_END	     (PID_VAL_END+NUM_PPM_CHAN)
#define BROWNOUT_START  (PPM_END+1)
#define BROWNOUT_END 	(BROWNOUT_START+1)


boolean ConfigChannel(BowlerPacket * Packet);
void ClearPinState(uint8_t pin);
void InitPins(void);
void InitPinFunction(void);

boolean pinHasFunction(uint8_t pin, uint8_t function);
void runDyIOMain(void);

NAMESPACE_LIST * get_neuronRoboticsDyIONamespace();
NAMESPACE_LIST * get_bcsPidDypidNamespace() ;

NAMESPACE_LIST * get_bcsSafeNamespace();
void setCoProcBrownOutMode(boolean b);
uint8_t SetAllCoProcValues();
boolean LoadSerialTxData(uint8_t numValues,uint8_t * data);
uint8_t GetSerialRxData(uint8_t * data);
void SetNewConfigurationDataTable(uint8_t pin, int32_t value);
void SyncDataTable();


#endif /* DYIO_DEF_H_ */
