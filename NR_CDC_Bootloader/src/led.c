/*
 * led.c
 *
 *  Created on: May 30, 2010
 *      Author: hephaestus
 */

#include "main.h"


/********************************************************************
 * Function:        void BlinkUSBStatus(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        BlinkUSBStatus turns on and off LEDs
 *                  corresponding to the USB device state.
 *
 * Note:            mLED macros can be found in HardwareProfile.h
 *                  USBDeviceState is declared and updated in
 *                  usb_device.c.
 *******************************************************************/
#include "main.h"
static unsigned char greenLed=0;
void BlinkUSBStatus(void)
{
    static WORD led_count=0;

    if(led_count == 0)led_count = 10000U;
    led_count--;

	if(led_count==0)
	{
		greenLed= !greenLed;
		setLed(greenLed,greenLed,!greenLed);
	}//end if



}//end BlinkUSBStatus
