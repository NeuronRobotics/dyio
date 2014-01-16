/*
* Copyright(C) NXP Semiconductors, 2011
* All rights reserved.
*
* Software that is described herein is for illustrative purposes only
* which provides customers with programming information regarding the
* LPC products.  This software is supplied "AS IS" without any warranties of
* any kind, and NXP Semiconductors and its licensor disclaim any and 
* all warranties, express or implied, including all implied warranties of 
* merchantability, fitness for a particular purpose and non-infringement of 
* intellectual property rights.  NXP Semiconductors assumes no responsibility
* or liability for the use of the software, conveys no license or rights under any
* patent, copyright, mask work right, or any other intellectual property rights in 
* or to any products. NXP Semiconductors reserves the right to make changes
* in the software without notification. NXP Semiconductors also makes no 
* representation or warranty that such application will be suitable for the
* specified use without further testing or modification.
* 
* Permission to use, copy, modify, and distribute this software and its 
* documentation is hereby granted, under NXP Semiconductors' and its 
* licensor's relevant copyrights in the software, without fee, provided that it 
* is used in conjunction with NXP Semiconductors microcontrollers.  This 
* copyright, permission, and disclaimer notice must appear in all copies of 
* this code.
*/


#include "../bsp_internal.h"

#if (BOARD == BOARD_MCB1000)

void bsp_init(void)
{
}

void Serial_Init(const uint32_t BaudRate, const bool DoubleSpeed)
{
}

void USB_Connect(void)
{
	GPIO_SetDir(USB_CONNECT_GPIO_PORT_NUM,(1<<USB_CONNECT_GPIO_BIT_NUM),1);				//output
	GPIO_ClearValue(USB_CONNECT_GPIO_PORT_NUM,(1<<USB_CONNECT_GPIO_BIT_NUM));			//pull up D+
}


void Buttons_Init(void)
{
	GPIO_SetDir(BUTTONS_BUTTON1_GPIO_PORT_NUM,(1<<BUTTONS_BUTTON1_GPIO_BIT_NUM),0); // input
}

void Joystick_Init(void)
{
	GPIO_SetDir(JOYSTICK_PRESS_GPIO_PORT_NUM,(1<<JOYSTICK_PRESS_GPIO_BIT_NUM),0); 	// input
}

uint8_t Joystick_GetStatus(void)
{
	uint8_t ret = NO_BUTTON_PRESSED;

	if((GPIO_ReadValue(JOYSTICK_PRESS_GPIO_PORT_NUM) & (1<<JOYSTICK_PRESS_GPIO_BIT_NUM)) == 0x00)
	{
		ret |= JOY_PRESS;
	}

	return ret;
}
void Audio_Init(uint32_t samplefreq)
{

}
void Audio_Reset_Data_Buffer(void)
{

}
uint32_t Audio_Get_ISO_Buffer_Address(uint32_t last_packet_size)
{
  return 0;
}
void LEDs_Init(void){}
void LEDs_SetAllLEDs(uint32_t LEDMask){}

#endif
