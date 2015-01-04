/*
 * Pin_State.c
 *
 *  Created on: Nov 23, 2009
 *      Author: hephaestus
 */
#include "UserApp_avr.h"
#include "Namespace/AsyncManager.h"


void ClearPinState(uint8_t pin){

	uint8_t current = GetChannelMode(pin);

	ClearPWM(pin);
	ClearADC(pin);
	ClearDCMotor(pin);

	if ((current == IS_UART_TX)||(current == IS_UART_RX)){
		StopUartPassThrough(pin);
	}
	SetPinTris(pin,INPUT);
}
