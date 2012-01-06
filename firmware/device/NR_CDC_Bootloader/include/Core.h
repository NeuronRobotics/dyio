/*
 * Core.h
 *
 *  Created on: Jun 13, 2011
 *      Author: hephaestus
 */

#ifndef CORE_H_
#define CORE_H_

#if defined(MAINAPP)
#ifdef USB_A0_SILICON_WORK_AROUND
	#pragma config UPLLEN   = OFF       // USB PLL Enabled (A0 bit inverted)
#else
	#pragma config UPLLEN   = ON        // USB PLL Enabled
#endif

#pragma config FPLLMUL  = MUL_20        // PLL Multiplier
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider
#pragma config FPLLODIV = DIV_1         // PLL Output Divider
#pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
#pragma config FWDTEN   = OFF           // Watchdog Timer
#pragma config WDTPS    = PS1           // Watchdog Timer Postscale
#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC = OFF           // CLKO Enable
#pragma config POSCMOD  = HS            // Primary Oscillator
#pragma config IESO     = ON            // Internal/External Switch-over
#pragma config FSOSCEN  = ON            // Secondary Oscillator Enable (KLO was off)
#pragma config FNOSC    = PRIPLL        // Oscillator Selection
#pragma config CP       = OFF           // Code Protect
#pragma config BWP      = OFF           // Boot Flash Write Protect
#pragma config PWP      = OFF           // Program Flash Write Protect
#pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
#pragma config DEBUG    = OFF            // Background Debugger Enable

#endif


#if defined(DYIO)

	#define initLed()		InitLEDS()
	#define initButton() 	((_TRISB0)=1)
	#define isPressed()		(_RB0== 1)
	#define setLed(a,b,c) 	SetColor(a,b,c)

#elif defined(UBW_OLD)

	#define initLed()		LATE = 0xFFF0; TRISE = 0xFFF0;
	#define initButton() 	((_TRISE7)=1)
	#define isPressed()		(_RE7 == 0)
	#define setLed(a,b,c) 	LATEbits.LATE0=a;LATEbits.LATE1=b;LATEbits.LATE2=c

#elif defined(UBW_NEW)

	#define initLed()		LATE = 0xFFF0; TRISE = 0xFFF0;
	#define initButton() 	((_TRISE7)=1)
	#define isPressed()		(_RE7 == 0)
	#define setLed(a,b,c) 	LATEbits.LATE0=a;LATEbits.LATE1=b;LATEbits.LATE2=c

#elif defined(AIM_ETH)

	#define initLed()		_TRISD0 = OUTPUT;_TRISD1 = OUTPUT;_TRISD2 = OUTPUT;
	#define initButton() 	_TRISD6  = INPUT;_TRISD7  = INPUT;_TRISD13 = INPUT;CNPUESET=0x00098000;
	#define isPressed()		( _RD6==0 || _RD7==0 || _RD13==0)
	#define setLed(a,b,c) 	_RD0=a;_RD1=b;_RD2=c;

#endif



#endif /* CORE_H_ */
