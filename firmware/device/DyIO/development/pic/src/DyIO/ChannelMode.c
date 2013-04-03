/*
 * ChannelMode.c
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */
#include "UserApp.h"

BOOL setMode(BYTE pin,BYTE mode);

void SyncModes(void);

BOOL brownOutDetect = TRUE;

void InitPinStates(void){
	SyncModes();
	int i;
	for (i=0;i<GetNumberOfIOChannels();i++){
		setMode(i,GetChannelMode(i));
		GetChannelValueCoProc(i);
	}
}

void setBrownOutDetect(BOOL b){
	brownOutDetect = b;
	setEEBrownOutDetect(b);
}
BOOL getBrownOutDetect(){
	return brownOutDetect;
}

BOOL setMode(BYTE pin,BYTE mode){
	println_I("Setting Mode: ");printMode(mode,INFO_PRINT);print_I(" on: ");p_ul_I(pin);
	BYTE currentMode = GetChannelMode(pin);
	ClearCounter(pin);
	StopSPI(currentMode);
	clearPPM(pin);
	switch (mode & 0x7f){

	case IS_SERVO:
		if(((pin < 12) && (isRegulated_0() == 0)) || ((pin >= 12) && (isRegulated_1()== 0))   ){
			print_I("|Mode is now servo");
			break;
		}else{
			if(getBrownOutDetect()){
				print_I(" Servo Mode could not be set, voltage invalid");
				return FALSE;
			}else{
				break;
			}
		}
	case IS_SPI_MOSI:
	case IS_SPI_MISO:
	case IS_SPI_SCK:
		if( pinHasFunction(pin, mode) != FALSE){
			print_I("|Mode is now SPI");
			InitSPI();
			break;
		}else{
			return FALSE;
		}

	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
		if(pinHasFunction(pin, mode) != FALSE){
			print_I("|Mode is now Counter Input");
			StartCounterInput(pin);
			break;
		}else{
			print_I(", Counter Input not availible");
			return FALSE;
		}
		break;
	case IS_COUNTER_OUTPUT_INT:
	case IS_COUNTER_OUTPUT_DIR:
	case IS_COUNTER_OUTPUT_HOME:
		if(pinHasFunction(pin, mode) != FALSE){
			print_I("|Mode is now Counter Output");
			StartCounterOutput(pin);
			break;
		}else{
			print_I(", Counter Output not availible");
			return FALSE;
		}
		break;
	case IS_PPM_IN:
		println_I("Setting up PPM...");
		startPPM(pin);
		break;
	}


	//ASYNC managed in EEPROM on co proc
	SetCoProcMode(pin,mode);

	SyncModes();

	return TRUE;
}




/*
BOOL SetChannelMode(BowlerPacket * Packet){

	BYTE pin =Packet->use.getBcsIoDataTable()[0];

	BYTE mode=Packet->use.getBcsIoDataTable()[1]& 0x7f;

	if(Packet->use.head.getBcsIoDataTable()Legnth == 7){
		isAsync[pin] = Packet->use.getBcsIoDataTable()[2]?TRUE:FALSE;
	}

	if(setMode(pin,mode)){
		//println_I("Valid Mode, setting...");
		//println_I("Sending Mode Set To Co Proc");

		//ASYNC managed in EEPROM on co proc
		SendPacketToCoProc(Packet);

		SyncModes();
		READY(Packet,4,33);
		if(isAsync[pin])
			startAdvancedAsyncDefault(pin);
		return TRUE;
	}else{
		println_E("Mode Invalid!");
		return FALSE;
	}

}

BOOL SetAllChannelMode(BowlerPacket * Packet){
	SendPacketToCoProc(Packet);
	SyncModes();
	int i=0;
	for(i=0;i<NUM_PINS;i++){
		if(IsAsync(i))
			startAdvancedAsyncDefault(i);
	}
	return TRUE;
}
*/



