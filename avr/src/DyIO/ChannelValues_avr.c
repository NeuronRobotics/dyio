/*
 * ChannelValues.c
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */
#include "UserApp_avr.h"

/**
 * Set Channel Values
 * This function takes a
 * @param pin pin index
 * @param numValues a number of values to be delt with
 * @param data an array of data values
 * @param ms the time for the transition to take
 *
 */
boolean SetChanelValueHW(uint8_t pin,uint8_t numValues,int32_t * data, float ms){
	uint8_t mode = GetChannelMode(pin);

		switch(mode){
//		case IS_COUNTER_INPUT_INT:
//		case IS_COUNTER_INPUT_DIR:
//		case IS_COUNTER_OUTPUT_INT:
//		case IS_COUNTER_OUTPUT_DIR:
//			SetChanVal(pin,data[0],ms);
//			return true; 
		}
		if(isSingleByteMode(mode)){
			int32_t time = (data[0]&0xffff0000)>>16;
			//mask the time into the data byte
			int32_t tmp = (data[0]&0x000000ff);
			//boolean back = data[0] !=getBcsIoDataTable(pin)->PIN.currentValue;
			boolean back =isNewDataTableValue(pin, data[0]);
			setDataTableCurrentValue(pin,data[0]);
			if(back){
				if(isOutputMode(mode)){
					SetChanVal(pin,tmp, time);
				}else{

				}
			}
		}else{
			//println_E("Unknown mode for setting ");printMode(mode,ERROR_PRINT);
		}

		return true; 

}

/**
 * Set Channel Values
 * This function takes a pin index, a number of values to be delt with, and an array of data values
 * Data is stored into numValues and data
 */
boolean GetChanelValueHW(uint8_t pin,uint8_t * numValues,int32_t * data){
	uint8_t mode = GetChannelMode(pin);
	numValues[0]=1;
	data[0] = getBcsIoDataTable(pin)->PIN.currentValue;
	if(mode== IS_UART_RX){
		 numValues[0] =1;
		 data[0]= Get_UART_Byte_CountPassThrough();
	}
	return true; 
}
/**
 * Set Channel Values
 * This function takes a
 * @param data an array of data values
 * @param ms the time for the transition to take
 *
 */
boolean SetAllChanelValueHW(int32_t * data, float ms){
//    Print_Level l = getPrintLevel();
//    setPrintLevelInfoPrint();
//    clearPrint();
	int i;
	for(i=0;i<GetNumberOfIOChannels();i++){
			SetChanelValueHW(i,1,& data[i], ms);
	}


//    printValues();
//    //printModes();
//    setPrintLevel(l);

	return true; 
}

/**
 * Set Channel Values
 * This function takes a pin index, a number of values to be delt with, and an array of data values
 * Data is stored into numValues and data
 */
boolean GetAllChanelValueHW(int32_t * data){
	int i;
	uint8_t numValues;
	for(i=0;i<GetNumberOfIOChannels();i++){
			GetChanelValueHW(i,&numValues,& data[i]);
	}
	return true; 
}

/**
 * Configure Channel
 * @param pin the index of the channel to configure
 * @param numValues The number of values passed in to deal with
 * @param data the array of values to use in the configuration step
 */

boolean ConfigureChannelHW(uint8_t pin,uint8_t numValues,int32_t * data){
	if(GetChannelMode(pin) != 0xff){
			SetNewConfigurationDataTable(pin, data[0]);
	}else{
		int i;
		for (i=0;i<numValues;i++){

			data[i]=GetConfigurationDataTable(i);
		}
	}
	return true; 
}

/**
 * Set Stream
 * This function takes a
 * @param pin pin index
 * @param numValues a number of values to be dealt with
 * @param data an array of data values
 *
 */
boolean SetStreamHW(uint8_t pin,uint8_t numValues,uint8_t * data){
	if(GetChannelMode(pin)==IS_UART_TX){
		UARTPassThroughWrite(numValues,data);
	}
	return true;
}

/**
 * Get Stream
 * This function takes a pin index, a number of values to be dealt with, and an array of data values
 * Data is stored into numValues and data
 */
boolean GetStreamHW(uint8_t pin,uint8_t*  numValues,uint8_t * data){

	if(GetChannelMode(pin)==IS_UART_RX){
		int uartSize =Get_UART_Byte_CountPassThrough();
		if(uartSize>0){
			numValues[0]=UARTGetArrayPassThrough(data,uartSize);
		}
	}
	return true;
}


/**
 * Legacy
 *
 *
 */
boolean SaveValue(uint8_t pin,uint8_t val){
	switch(GetChannelMode(pin)){
	case IS_SERVO:
	case IS_PWM:
		EEWriteValue(pin,val);
		return true; 
	default:
		return false; 
	}
}

//boolean GetChannelValue(BowlerPacket * Packet){
//	boolean ret=false;
//	uint8_t pin = Packet->use.data[0];
//	uint8_t mode = GetChannelMode(pin);
//	//int i;
//	uint16_t val=GetChanVal(pin);
//	if(IsAsync(pin)){
//		//AsynAck();
//	}
//	Packet->use.head.Method=BOWLER_POST;
//	if ((mode == IS_DC_MOTOR_VEL)||(mode == IS_DC_MOTOR_DIR)||(mode == IS_DO)|| (mode == IS_PWM)|| (mode == IS_SERVO) || (mode == IS_DI) ||(mode == IS_COUNTER_OUTPUT_HOME)||(mode == IS_COUNTER_INPUT_HOME)){
//		set8bit(Packet, val,1);
//		Packet->use.head.DataLegnth=6;
//		ret = true;
//	}else if ((mode == IS_ANALOG_IN)){
//		val=GetADC(pin);
//		set16bit(Packet,val,1);
//		Packet->use.head.DataLegnth=7;
//		ret = true;
//	}else if ( (mode == IS_UART_TX) || (mode == IS_UART_RX)){
//		//Number of bytes in the stream to be sent
//		Packet->use.head.DataLegnth=5;
//		uint16_t numBytes=Get_UART_Byte_CountPassThrough();
//		if(numBytes>0){
//			UARTGetArrayPassThrough(Packet->use.data+1,numBytes);
//			//Offset using pointer, rather then shuffeling
////			for (i=0;i<numBytes;i++){
////				Packet->use.data[(numBytes)-i]=Packet->use.data[(numBytes-1)-i];
////			}
//			Packet->use.data[0]=17;
//			Packet->use.head.DataLegnth+=numBytes;
//		}
//		return true;
//	}else{
//		return false;
//	}
//	return ret;
//}

uint16_t GetChanVal(uint8_t pin){
	uint16_t val;
	uint8_t mode = GetChannelMode(pin);
	switch (mode){
	case HIGH_IMPEDANCE:
		val=1;
		break;
	case IS_DI:
	case IS_DO:
	case IS_COUNTER_INPUT_HOME:
	case IS_COUNTER_OUTPUT_HOME:
		val = GetDIO(pin);
		break;
	case IS_SERVO:
		val = GetServoPos(pin);
		break;
	case IS_PWM:
		val = GetPWM(pin);
		break;
	case IS_DC_MOTOR_VEL:
	case IS_DC_MOTOR_DIR:
		val = GetDCMotor(pin);
		break;
	case IS_ANALOG_IN:
		val=GetADC(pin);
		break;
	default:
		val=1;
		break;
	}
	return val;
}



boolean isASetableMode(uint8_t mode){
	if ((mode == IS_DO)|| (mode == IS_SERVO) || (mode == IS_PWM)|| (mode == IS_DI)||(mode == IS_DC_MOTOR_VEL)||(mode == IS_DC_MOTOR_DIR)){
		return true; 
	}
	return false; 
}


boolean SetChanVal(uint8_t pin,int32_t bval, float time){
//	println_W("SetChanVal\tchan: ");p_int_W(pin);
//	print_W(" \tto val: ");p_int_W(bval);print_W(" \ttime: ");p_fl_W(time);
	uint8_t mode = GetChannelMode(pin);

		switch (mode){
		case IS_DI:
		case IS_DO:
			SetDIO(pin,(bval<=0)?0:1);
			break;
		case IS_SERVO:
			SetServoPos(pin,bval,time);
			break;
		case IS_PWM:
			SetPWM(pin,bval);
			break;
		case IS_DC_MOTOR_VEL:
		case IS_DC_MOTOR_DIR:
			SetDCMotor(pin,bval);
			break;
		default:
			return false;
		}
		return true;

}
