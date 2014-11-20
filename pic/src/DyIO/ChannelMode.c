/*
 * ChannelMode.c
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */
#include "UserApp.h"

boolean setMode(uint8_t pin,uint8_t mode);

void SyncModes(void);



void InitPinStates(void){
	SyncModes();
	//println_I("Modes synced, initializing channels");
	initAdvancedAsync();
	int i;
	for (i=0;i<GetNumberOfIOChannels();i++){
		//DelayMs(10);
		SetChannelMode(i,GetChannelMode(i));
	}
}




boolean setMode(uint8_t pin,uint8_t mode){
	//println_I("Setting Mode: ");printMode(mode,INFO_PRINT);print_I(" on: ");p_int_I(pin);
	//uint8_t currentMode = GetChannelMode(pin);
	if(GetChannelMode(pin)== mode)
		return true;
	forceModeDownstream( pin);
	ClearCounter(pin);
	StopDyIOSPI(pin);
	clearPPM(pin);
	//print_I(" \tHardware Cleared");
	switch (mode){
	case IS_SERVO:
		if(!(((pin < 12) && (isRegulated_0() == 0)) || ((pin >= 12) && (isRegulated_1()== 0)))   ){
                    if(getBrownOutDetect()){
                            print_I(" Servo Mode could not be set, voltage invalid");
                            return false;
                    }
                }
                println_E("Setting servo dfault position to: "); p_int_E(GetConfigurationDataTable(pin));
                /** no break, fall through to set datatable*/

        case IS_PWM:
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



