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
        #include "bootloader/Namespace_bcs_bootloader.h"


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

	uint16_t Get_HAL_Byte_Count();
void disableSerialComs(boolean state);
#define Bowler_HAL_Init Pic32_Bowler_HAL_Init
void SetPICUARTFifo(BYTE_FIFO_STORAGE * s);
void SendPacketUSB(uint8_t * packet,uint16_t size);
void Pic32_Bowler_HAL_Init(void);

void FlashSync(void);
void SetFlashData(uint32_t * s,uint32_t size);
void FlashLoad(void);

void setPicIOTristateInput(char port,int pin);
void setPicIOTristateOutput(char port,int pin);
void setPicIOTristate(boolean state,char port,int pin);

void setPicIOPin(boolean state,char port,int pin);
boolean getPicIOPin(char port,int pin);


#define     ioPortB(s,p)  if(s){PORTBSET=(1<<p);}else{ PORTBCLR=(1<<p);}
#define     ioPortC(s,p)  if(s){PORTCSET=(1<<p);}else{ PORTCCLR=(1<<p);}
#define     ioPortD(s,p)  if(s){PORTDSET=(1<<p);}else{ PORTDCLR=(1<<p);}
#define     ioPortE(s,p)  if(s){PORTESET=(1<<p);}else{ PORTECLR=(1<<p);}
#define     ioPortF(s,p)  if(s){PORTFSET=(1<<p);}else{ PORTFCLR=(1<<p);}
#define     ioPortG(s,p)  if(s){PORTGSET=(1<<p);}else{ PORTGCLR=(1<<p);}


#endif /* BOWLERCONFIG_H_ */
