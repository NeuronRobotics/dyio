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
BOOL SetChanelValueHW(BYTE pin,BYTE numValues,INT32 * data, float ms){
	BYTE mode = GetChannelMode(pin);
	if(isStremChannelMode(mode)){
		BYTE * bData = (BYTE *)data;
		switch(mode){
//		case IS_SPI_MOSI:
//		case IS_SPI_MISO:
//		case IS_SPI_SCK:
//			SendPacketToSPIFromArray(numValues,bData);
//			return TRUE;
//		case IS_UART_TX:
//		case IS_UART_RX:
//			LoadSerialTxData( numValues,bData);
//			return TRUE;
//		case IS_PPM_IN:
//			ConfigPPMFromArray(bData);
//			return TRUE;
		}
	}else{
		switch(mode){
//		case IS_COUNTER_INPUT_INT:
//		case IS_COUNTER_INPUT_DIR:
//		case IS_COUNTER_OUTPUT_INT:
//		case IS_COUNTER_OUTPUT_DIR:
//			SetChanVal(pin,data[0],ms);
//			return TRUE;
		}
		if(isSingleByteMode(mode)){
			INT32 time = (INT32)ms;
			//mask the time into the data byte
			getBcsIoDataTable()[pin].PIN.currentValue = (time<<16)|(data[0]&0x000000ff);
		}
		return TRUE;
	}


}

/**
 * Set Channel Values
 * This function takes a pin index, a number of values to be delt with, and an array of data values
 * Data is stored into numValues and data
 */
BOOL GetChanelValueHW(BYTE pin,BYTE * numValues,INT32 * data){
	BYTE mode = GetChannelMode(pin);
	if(isStremChannelMode(mode)){
		BYTE * bData = (BYTE *)data;
		switch(mode){
//		case IS_SPI_MOSI:
//		case IS_SPI_MISO:
//		case IS_SPI_SCK:
//			SendPacketToSPIFromArray(numValues[0],bData);
//			return TRUE;
//		case IS_UART_TX:
//		case IS_UART_RX:
//			 numValues[0] = GetSerialRxData( bData);
//			return TRUE;
//		case IS_PPM_IN:
//			numValues[0] = GetPPMDataToArray(bData);
//			return TRUE;
		}
	}else{
		numValues[0]=1;
		switch(mode){
//		case IS_COUNTER_INPUT_INT:
//		case IS_COUNTER_INPUT_DIR:
//			data[0] = GetCounterByChannel(pin);
//			return TRUE;
//		case IS_COUNTER_OUTPUT_INT:
//		case IS_COUNTER_OUTPUT_DIR:
//			data[0] = GetCounterOutput(pin);
//			return TRUE;
		}
		if(isSingleByteMode(mode)){
			//mask the time into the data byte
			 data[0] = getBcsIoDataTable()[pin].asyncData.currentVal & 0x000000ff;
		}
		return TRUE;
	}
}
/**
 * Set Channel Values
 * This function takes a
 * @param data an array of data values
 * @param ms the time for the transition to take
 *
 */
BOOL SetAllChanelValueHW(INT32 * data, float ms){
	int i;
	for(i=0;i<GetNumberOfIOChannels();i++){
		if(!isStremChannelMode(GetChannelMode(i)))
			SetChanelValueHW(i,1,& data[i], ms);
	}
	return TRUE;
}

/**
 * Set Channel Values
 * This function takes a pin index, a number of values to be delt with, and an array of data values
 * Data is stored into numValues and data
 */
BOOL GetAllChanelValueHW(INT32 * data){
	int i;
	BYTE numValues;
	for(i=0;i<GetNumberOfIOChannels();i++){
		if(!isStremChannelMode(GetChannelMode(i)))
			GetChanelValueHW(i,&numValues,& data[i]);
	}
	return TRUE;
}

/**
 * Configure Channel
 * @param pin the index of the channel to configure
 * @param numValues The number of values passed in to deal with
 * @param data the array of values to use in the configuration step
 */

BOOL ConfigureChannelHW(BYTE pin,BYTE numValues,INT32 * data){
	if(!isStremChannelMode(GetChannelMode(pin)))
		SetNewConfigurationDataTable( pin, data[0]);
	return TRUE;
}


/**
 * Legacy
 *
 *
 */
BOOL SaveValue(BYTE pin,BYTE val){
	switch(GetChannelMode(pin)){
	case IS_SERVO:
	case IS_PWM:
		EEWriteValue(pin,val);
		return TRUE;
	default:
		return FALSE;
	}
}

BOOL GetChannelValue(BowlerPacket * Packet){
	BOOL ret=FALSE;
	BYTE pin = Packet->use.data[0];
	BYTE mode = GetChannelMode(pin);
	int i;
	UINT16 val=GetChanVal(pin);
	if(IsAsync(pin)){
		AsynAck();
	}
	Packet->use.head.Method=BOWLER_POST;
	if ((mode == IS_DC_MOTOR_VEL)||(mode == IS_DC_MOTOR_DIR)||(mode == IS_DO)|| (mode == IS_PWM)|| (mode == IS_SERVO) || (mode == IS_DI) ||(mode == IS_COUNTER_OUTPUT_HOME)||(mode == IS_COUNTER_INPUT_HOME)){
		set8bit(Packet, val,1);
		Packet->use.head.DataLegnth=6;
		ret = TRUE;
	}else if ((mode == IS_ANALOG_IN)){
		val=GetADC(pin);
		set16bit(Packet,val,1);
		Packet->use.head.DataLegnth=7;
		ret = TRUE;
	}else if ( (mode == IS_UART_TX) || (mode == IS_UART_RX)){
		//Number of bytes in the stream to be sent
		Packet->use.head.DataLegnth=5;
		UINT16 numBytes=Get_UART_Byte_CountPassThrough();
		if(numBytes>0){
			UARTGetArrayPassThrough(Packet->use.data+1,numBytes);
			//Offset using pointer, rather then shuffeling
//			for (i=0;i<numBytes;i++){
//				Packet->use.data[(numBytes)-i]=Packet->use.data[(numBytes-1)-i];
//			}
			Packet->use.data[0]=17;
			Packet->use.head.DataLegnth+=numBytes;
		}
		return TRUE;
	}else{
		return FALSE;
	}
	return ret;
}

UINT16 GetChanVal(BYTE pin){
	UINT16 val;
	BYTE mode = GetChannelMode(pin);
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
	}
	return val;
}
BOOL isASetableMode(BYTE mode){
	if ((mode == IS_DO)|| (mode == IS_SERVO) || (mode == IS_PWM)|| (mode == IS_DI)||(mode == IS_DC_MOTOR_VEL)||(mode == IS_DC_MOTOR_DIR)){
		return TRUE;
	}
	return FALSE;
}

BOOL SetAllChannelValue(BowlerPacket * Packet){
	UINT32_UNION time;
	UINT32_UNION data;
	BYTE i;
	time.byte.FB=Packet->use.data[0];
	time.byte.TB=Packet->use.data[1];
	time.byte.SB=Packet->use.data[2];
	time.byte.LB=Packet->use.data[3];
	for(i=0;i<NUM_PINS;i++){
		data.byte.FB=Packet->use.data[4+(i*4)];
		data.byte.TB=Packet->use.data[5+(i*4)];
		data.byte.SB=Packet->use.data[6+(i*4)];
		data.byte.LB=Packet->use.data[7+(i*4)];
		if(isASetableMode(GetChannelMode(i))){
			 SetChanVal(i, data.Val, time.Val);
		}
	}

	return TRUE;
}
BOOL SetChannelValue(BowlerPacket * Packet){
	BOOL ret=FALSE;
	BYTE pin = Packet->use.data[0];
	BYTE mode = GetChannelMode(pin);
	BYTE bval;
	UINT16_UNION wval;
	BYTE zone=128;
	//println_I("Setting Value of mode: ");printMode(mode);print_I(" on pin:");p_sl_I(pin);
	if (isASetableMode(mode)){
		bval = Packet->use.data[1];
		if (Packet->use.head.DataLegnth>6){
			wval.byte.SB = Packet->use.data[2];
			wval.byte.LB = Packet->use.data[3];
		}else{
			//println_I("Packet was 6 or less data bytes");
			wval.Val=0;
		}
		SetChanVal(pin,bval,(float)wval.Val);
		ret = TRUE;
		READY(Packet,zone,0);
	}else if ( (mode == IS_ANALOG_OUT)){
		wval.byte.SB=Packet->use.data[1];
		wval.byte.LB=Packet->use.data[2];
		switch (mode){
			default:
				return FALSE;
			}
		ret = TRUE;
	}else if ((mode == IS_UART_TX) || (mode == IS_UART_RX)){
		//Number of bytes in the stream to be sent
		BYTE i;
		bval = Packet->use.head.DataLegnth-5;
		for (i=0;i<bval;i++){
			WriteAVRUART1(Packet->use.data[i+1]);
		}
		return TRUE;
	}
	return ret;
}



BOOL SetChanVal(BYTE pin,INT32 bval, float time){
	BYTE mode = GetChannelMode(pin);
	//println_I("Setting channel pos\n\tchan: ");p_sl_I(pin);print_I(" \n\tto val: ");p_ul_I(bval);print_I("\n\tin time: ");p_fl_I(time);
	switch (mode){
	case IS_DI:
	case IS_DO:
		SetDIO(pin,bval);
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
		return FALSE;
	}
	return TRUE;
}
