/*
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
#ifndef BOWLERCONFIG_H_
#define BOWLERCONFIG_H_


#include "reg_structs.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "Bowler/Debug.h"
#  include <avr/iom644p.h>
#if !defined(__AVR_ATmega324P__)
	#define USE_DYN_RPC
#endif

#define FlagBusy_DDR	DDRCbits._P7
#define FlagAsync_DDR 	DDRCbits._P6
#define FlagBusy_IO		PORTCbits._P7
#define FlagAsync		PINCbits._P6

#define InitFlagPins() 	FlagBusy_DDR=OUTPUT;FlagAsync_DDR=INPUT;FlagBusy_IO=0;PORTCbits._P6=1;

#define OUTPUT 					1
#define INPUT  					0
#define OFF						0
#define ON						1
#define ALLOUTPUT 				0xFF
#define ALLINPUT  				0x00
#define SDK_LED_ALLON 			0x00
#define SDK_LED_ALLOFF 			0xff
#define SDK_LED_ON 				0
#define SDK_LED_OFF 			1
#define UARTDELAY				20

#define Nop()					__asm__("nop\n\t")
#define nop()					Nop()

void WriteAVRUART0(uint8_t val);
void WriteAVRUART1(uint8_t val);
void updateTimer(uint64_t value);

void fixTimers(int currentTimer);

//#define WriteUART_COM 			WriteAVRUART0
//#define WriteUART_DEBUG 		WriteAVRUART1

#define StartCritical() cli()
#define EndCritical()   sei()

#define USE_UART
void AVR_Bowler_HAL_Init(void);
#define Bowler_HAL_Init() AVR_Bowler_HAL_Init()
#define SetColor(a,b,c)

void showString (PGM_P s,Print_Level l,char newLine);

#undef print
#undef println

/**
 * print the null terminated string with no new lines
 */
#define print(A,B) showString(PSTR(A),B,0)

/**
 * print the null terminated string with a newline inserted at the begining of the string
 */
#define println(A,B) showString(PSTR(A),B,1)



#endif /* BOWLERCONFIG_H_ */
