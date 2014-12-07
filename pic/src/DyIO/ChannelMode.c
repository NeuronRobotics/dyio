/*
 * ChannelMode.c
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */
#include "UserApp.h"



boolean setMode(uint8_t pin,uint8_t mode){
	//println_I("Setting Mode: ");printMode(mode,INFO_PRINT);print_I(" on: ");p_int_I(pin);
	uint8_t current = GetChannelMode(pin);
	if(GetChannelMode(pin)== mode){
		//println_W("Re-Setting Mode: ");printMode(mode,WARN_PRINT);print_W(" on: ");p_int_W(pin);
		//return true;
	}
	forceModeDownstream( pin);
	StopDyIOSPI(pin);
	clearPPM(pin);

	if(current == IS_PPM_IN){
		ClearCounter(23);
		ClearCounter(22);
	}
	if ( (current >= IS_SPI_MOSI)&&(current <= IS_SPI_SCK)){
		ClearCounter(0);
		ClearCounter(1);
		ClearCounter(2);
	}
	if ((current == IS_UART_TX)||(current == IS_UART_RX)){
		ClearCounter(16);
		ClearCounter(17);
	}
	if(current ==IS_DC_MOTOR_VEL ||current ==IS_DC_MOTOR_DIR ){
		uint8_t pwm,dir;
		if(pin>7){
			dir=pin;
			pwm=dir-4;
		}else{
			pwm=pin;
			dir=pwm+4;
		}
		if((GetChannelMode(pwm)==IS_DC_MOTOR_VEL)&&(GetChannelMode(dir)==IS_DC_MOTOR_DIR)){
			SetCoProcMode(pwm,IS_DI);
			SetCoProcMode(dir,IS_DI);
		}
	}
	ClearCounter(pin);

	//print_I(" \tHardware Cleared");
	switch (mode){
	case IS_SERVO:
		if(!(((pin < 12) && (isRegulated_0() == 0)) || ((pin >= 12) && (isRegulated_1()== 0)))   ){
                    if(getBrownOutDetect()){
                            print_W(" Servo Mode could not be set, voltage invalid");
                            return false;
                    }
                }
                //println_E("Setting servo dfault position to: "); p_int_E(GetConfigurationDataTable(pin));
                /** no break, fall through to set datatable*/

        case IS_PWM:
        	//println_E(__FILE__);println_E("setMode");
                setDataTableCurrentValue(pin,GetConfigurationDataTable(pin));
		return true;
	case IS_SPI_MOSI:
	case IS_SPI_MISO:
	case IS_SPI_SCK:
		if( pinHasFunction(pin, mode) != false) {
//			print_I("|Mode is now SPI");
			InitSPIDyIO();
			return true;
		}else{
			return false; 
		}
		return true;
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
		if(pinHasFunction(pin, mode) != false) {
//			print_I("|Mode is now Counter Input");
			StartCounterInput(pin);
			return true;
		}else{
			print_E(", Counter Input not availible");
			return false; 
		}
		break;
	case IS_COUNTER_OUTPUT_INT:
	case IS_COUNTER_OUTPUT_DIR:
	case IS_COUNTER_OUTPUT_HOME:
		if(pinHasFunction(pin, mode) != false) {
//			print_I("|Mode is now Counter Output");
			StartCounterOutput(pin);
			return true;
		}else{
			print_E(", Counter Output not availible");
			return false; 
		}
		return true;
	case IS_PPM_IN:
		println_I("Setting up PPM...");
		startPPM(pin);
		return true;
	case IS_DO:
		setDataTableCurrentValue(pin,OFF);
		return true;
            default:
                return true;
	}
//	print_I(" \tMode set");
	
}



