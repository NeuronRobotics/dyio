/*
 * ChannelMode.c
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */
#include "UserApp_avr.h"

boolean startup = true; 
void InitPinModes(void){
	uint8_t i;
	uint8_t mode=0;
	for (i=0;i<NUM_PINS;i++){

		//ClearPinState(i);
		SetPinTris(i,INPUT);
		SetDIO(i,0);

		//getBcsIoDataTable(i)->PIN.previousChannelMode=NO_CHANGE;
		mode=EEReadMode(i);
		if((mode < 2)||(mode >=IO_MODE_MAX)){
			configPinMode(i,IS_DI,INPUT,ON);
			mode = EEReadMode(i);
		}
		getBcsIoDataTable(i)->PIN.currentChannelMode = 0xff;// this forces the set Mode function to set the mode and hardware
		println_W("Initializing :");p_int_W(i);printMode(mode,WARN_PRINT);
		setMode(i,mode);
		_EEWriteMode(i, mode);
	}
	startup = false; 
	//printModes();
}


boolean setMode(uint8_t pin,uint8_t mode){
	if(mode == GetChannelMode(pin)){
		return true;
	}
	ClearPinState(pin);
	//uint8_t pwm,dir;

	switch (mode){

	case IS_UART_TX:
	case IS_UART_RX:
		if(pin == 17 || pin == 16){
			configPinMode(16,IS_UART_TX,OUTPUT,ON);
			configPinMode(17,IS_UART_RX,INPUT,ON);
			InitUART();
			return true; 
		}
		break;
	case IS_SPI_MOSI:
	case IS_SPI_MISO:
	case IS_SPI_SCK:
		if(pin == 0 || pin == 1||pin == 2   ){
			configPinMode(0,IS_SPI_SCK,INPUT,ON);
			configPinMode(1,IS_SPI_MISO,INPUT,ON);
			configPinMode(2,IS_SPI_MOSI,INPUT,ON);
			return true; 
		}
		break;
	case IS_ANALOG_IN:
		configPinMode(pin,mode,INPUT,OFF);
		if(InitADC(pin)){
			return true; 
		}
		break;
	case IS_PWM:
		if(InitPWM(pin)){
			return true; 
		}
		return false; 
	case IS_DC_MOTOR_VEL:
	case IS_DC_MOTOR_DIR:
		if(InitDCMotor(pin)){
			return true; 
		}
		return false; 
	case IS_SERVO:
		InitServo(pin);
		configPinMode(pin,mode,OUTPUT,OFF);
		return true; 
	case IS_DO:
		configPinMode(pin,mode,OUTPUT,OFF);
		setDataTableCurrentValue(pin,OFF);
		return true; 
	case IS_DI:
	case IS_PPM_IN:
	case IS_COUNTER_OUTPUT_INT:
	case IS_COUNTER_OUTPUT_DIR:
	case IS_COUNTER_OUTPUT_HOME:
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
		configPinMode(pin,mode,INPUT,ON);
		return true; 
	default:
		configPinMode(pin,mode,INPUT,ON);
		return true; 
	}
	return false; 
}

void configPinMode(uint8_t pin,uint8_t mode,uint8_t tris,uint8_t io){
	SetPinTris(pin,tris);
	SetDIO(pin,io);
	_EEWriteMode(pin,mode);
}
