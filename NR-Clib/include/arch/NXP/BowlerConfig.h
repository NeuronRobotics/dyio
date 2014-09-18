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

#include <NXP/crp.h>

#if !defined(__AVR_ATmega324P__)
	#define USE_DYN_RPC
#endif

// GPIO pin masking defines
#define OUTPUT 					1
#define INPUT  					0
#define OFF						0
#define ON						1


#define Nop()					Nop()//__asm__("nop\n\t")
#define nop()					Nop()

//void WriteAVRUART0(BYTE val);
//void WriteAVRUART1(BYTE val);

#define WriteUART_COM 		Nop()	//WriteAVRUART0
#define WriteUART_DEBUG 		Nop() //WriteAVRUART1

#define StartCritical() Nop() //cli()
#define EndCritical()   Nop() //sei()

#define USE_UART
void AVR_Bowler_HAL_Init(void);
#define Bowler_HAL_Init() AVR_Bowler_HAL_Init()
#define SetColor(a,b,c)

#endif /* BOWLERCONFIG_H_ */
