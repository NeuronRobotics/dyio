/*
 * Pin_State.c
 *
 *  Created on: Nov 23, 2009
 *      Author: hephaestus
 */
#include "UserApp_avr.h"
#include "Namespace/AsyncManager.h"

void InitPins(void){
	InitPinFunction();
	InitPinModes();
	int i=0;
	for(i=0;i<GetNumberOfIOChannels();i++){
		initPinState(i);
		configAdvancedAsyncNotEqual(i,10);
	}
}


void ClearPinState(BYTE pin){

	BYTE current = GetChannelMode(pin);

	ClearPWM(pin);
	ClearADC(pin);
	ClearDCMotor(pin);

	if ( (current >= IS_SPI_MOSI)&&(current <= IS_SPI_SCK)){
		EEWriteMode(0,IS_DI);
		EEWriteMode(1,IS_DI);
		EEWriteMode(2,IS_DI);
		EEWriteMode(3,IS_DI);
	}
	if ((current == IS_UART_TX)||(current == IS_UART_RX)){
		StopUartPassThrough(pin);
		EEWriteMode(16,IS_DI);
		EEWriteMode(17,IS_DI);
	}
	SetPinTris(pin,INPUT);
}
