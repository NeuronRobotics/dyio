/*
 * ChannelMode.c
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */
#include "UserApp.h"



boolean setMode(uint8_t pin,uint8_t mode){

	uint8_t current = GetChannelMode(pin);

	StopDyIOSPI(pin,current );
	clearPPM(pin,current);
	ClearCounter(pin,current);

	if ((current == IS_UART_TX)||(current == IS_UART_RX)){
		SetCoProcMode(17,IS_DI);
		SetCoProcMode(16,IS_DI);
	}

	uint8_t pwm,dir;
	if(pin>7){
		dir=pin;
		pwm=dir-4;
	}else{
		pwm=pin;
		dir=pwm+4;
	}
	// check current mode first, clear both pins if set to DC motor mode
	if((GetChannelMode(pwm)==IS_DC_MOTOR_VEL)&&(GetChannelMode(dir)==IS_DC_MOTOR_DIR)){
		SetCoProcMode(pwm,IS_DI);
		SetCoProcMode(dir,IS_DI);
	}

	//print_I(" \tHardware Cleared");
	switch (mode){
	case IS_SERVO:
		if(!(((pin < 12) && (isRegulated_0() == 0)) || ((pin >= 12) && (isRegulated_1()== 0)))   ){
                    if(getBrownOutDetect()){
                            //print_W(" Servo Mode could not be set, voltage invalid");
                            return false;
                    }
                }
                //println_E("Setting servo default position to: "); p_int_E(GetConfigurationDataTable(pin));
                /** no break, fall through to set datatable*/
	case IS_DC_MOTOR_VEL:
	case IS_DC_MOTOR_DIR:
	case IS_PWM:
        	//println_E(__FILE__);println_E("setMode");
		setDataTableCurrentValue(pin,GetConfigurationDataTable(pin));
		// Set up new DC-motor mode is this is the mode to set
		if(mode ==IS_DC_MOTOR_VEL ||mode ==IS_DC_MOTOR_DIR ){
			SetCoProcMode(pwm,IS_DC_MOTOR_VEL);
			SetCoProcMode(dir,IS_DC_MOTOR_DIR);
		}
		break;
	case IS_SPI_MOSI:
	case IS_SPI_MISO:
	case IS_SPI_SCK:
		if( pinHasFunction(pin, mode) != false) {
			ClearCounter(0,current );
			ClearCounter(1,current );
			ClearCounter(2,current );
			ClearCounter(23,current );
			ClearCounter(22,current );
			ClearCounter(21,current );
			ClearCounter(20,current );
			ClearCounter(19,current );
			ClearCounter(18,current );
			//print_I("|Mode is now SPI");
			InitSPIDyIO();
			SetCoProcMode(0,IS_SPI_SCK);
			SetCoProcMode(1,IS_SPI_MISO);
			SetCoProcMode(2,IS_SPI_MOSI);
			break;
		}else{
			return false; 
		}
		break;
	case IS_UART_RX:
	case IS_UART_TX:
		ClearCounter(16,current );
		ClearCounter(17,current );
		ClearCounter(3,current );
		SetCoProcMode(16,IS_UART_TX);
		SetCoProcMode(17,IS_UART_RX);
		break;
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
		if(pinHasFunction(pin, mode) != false) {
//			print_I("|Mode is now Counter Input");
			StartCounterInput(pin);
			break;
		}else{
			//print_E(", Counter Input not availible");
			return false; 
		}
		break;
	case IS_COUNTER_OUTPUT_INT:
	case IS_COUNTER_OUTPUT_DIR:
	case IS_COUNTER_OUTPUT_HOME:
		if(pinHasFunction(pin, mode) != false) {
//			print_I("|Mode is now Counter Output");
			StartCounterOutput(pin);
			break;
		}else{
			//print_E(", Counter Output not availible");
			return false; 
		}
		break;
	case IS_PPM_IN:
		//println_W("Setting up PPM...");
		ClearCounter(23,current );
		ClearCounter(22,current );
		startPPM(pin);
		break;
	case IS_DO:
		setDataTableCurrentValue(pin,OFF);
		break;
	default:
		break;
	}
	SetCoProcMode(pin,mode);
	print_E(" OK ");
	return true;
//	print_I(" \tMode set");
	
}



