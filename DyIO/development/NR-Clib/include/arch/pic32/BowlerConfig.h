/*
 * BowlerConfig.h
 *
 *  Created on: Jan 11, 2010
 *      Author: hephaestus
 */

#ifndef BOWLERCONFIG_H_
#define BOWLERCONFIG_H_

#if defined(__PIC32MX__)
	#include "arch/pic32/Compiler.h"
    #include "arch/pic32/GenericTypeDefs.h"
#endif

	#define USE_DYN_RPC

	#define ASSERTED				0
	#define NOT_ASSERTED			1
	#define OUTPUT 					0
	#define INPUT 					1

	#include "HardwareProfile.h"
	#include "Delay.h"
	#include "Tick.h"
	#include "LED.h"
	#include "UART.h"
	#include "FlashStorage.h"

	#include "USB/usb_fifo.h"
	#include <plib.h>


	#define StartCritical()  INTDisableInterrupts();
	#define EndCritical()    INTEnableSystemMultiVectoredInt();INTEnableInterrupts();

	#define WriteUART_COM 			Write32UART1
#if defined(AIM_ETH)
	#define WriteUART_DEBUG 		Write32UART1
#else
        #define WriteUART_DEBUG 		Write32UART1
#endif
	#define USE_UART
	#define USE_USB

	WORD Get_HAL_Byte_Count();
void disableSerialComs(BOOL state);
#define Bowler_HAL_Init Pic32_Bowler_HAL_Init
void SetPICUARTFifo(BYTE_FIFO_STORAGE * s);
void SendPacketUSB(BYTE * packet,WORD size);
void Pic32_Bowler_HAL_Init(void);




#endif /* BOWLERCONFIG_H_ */
