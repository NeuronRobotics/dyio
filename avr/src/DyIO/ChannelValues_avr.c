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
	if(isStremChannelMode(mode)){
		//uint8_t * bData = (uint8_t *)data;
		switch(mode){
//		case IS_SPI_MOSI:
//		case IS_SPI_MISO:
//		case IS_SPI_SCK:
//			SendPacketToSPIFromArray(numValues,bData);
//			return true; 
//		case IS_UART_TX:
//		case IS_UART_RX:
//			LoadSerialTxData( numValues,bData);
//			return true; 
//		case IS_PPM_IN:
//			ConfigPPMFromArray(bData);
//			return true; 
		}
	}else{
		switch(mode){
//		case IS_COUNTER_INPUT_INT:
//		case IS_COUNTER_INPUT_DIR:
//		case IS_COUNTER_OUTPUT_INT:
//		case IS_COUNTER_OUTPUT_DIR:
//			SetChanVal(pin,data[0],ms);
//			return true; 
		}
		if(isSingleByteMode(mode)){
			int32_t time = (int32_t)ms;
			//mask the time into the data byte
			int32_t tmp = (data[0]&0x000000ff);
			if(setDataTableCurrentValue(pin,tmp)){
				if(isOutputMode(mode)){
					SetChanVal(pin,getBcsIoDataTable(pin)->PIN.currentValue, time);
				}else{
					println_I("INPUT\tchan: ");p_int_I(pin);
					print_I(" \tto val: ");p_int_I(tmp);
				}
			}
		}
		return true; 
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
	if(isStremChannelMode(mode)){
		//uint8_t * bData = (uint8_t *)data;
		switch(mode){
//		case IS_SPI_MOSI:
//		case IS_SPI_MISO:
//		case IS_SPI_SCK:
//			SendPacketToSPIFromArray(numValues[0],bData);
//			return true; 
//		case IS_UART_TX:
//		case IS_UART_RX:
//			 numValues[0] = GetSerialRxData( bData);
//			return true; 
//		case IS_PPM_IN:
//			numValues[0] = GetPPMDataToArray(bData);
//			return true; 
		}
	}else{
		numValues[0]=1;
		switch(mode){
//		case IS_COUNTER_INPUT_INT:
//		case IS_COUNTER_INPUT_DIR:
//			data[0] = GetCounterByChannel(pin);
//			return true; 
//		case IS_COUNTER_OUTPUT_INT:
//		case IS_COUNTER_OUTPUT_DIR:
//			data[0] = GetCounterOutput(pin);
//			return true; 
		}
		if(isSingleByteMode(mode)){
			//mask the time into the data byte
			data[0] = getBcsIoDataTable(pin)->PIN.currentValue & 0x000000ff;

		}else{
			data[0] = getBcsIoDataTable(pin)->PIN.currentValue;
		}
		//data[0] = pin;
		return true; 
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
    Print_Level l = getPrintLevel();
    setPrintLevelInfoPrint();
    clearPrint();
	int i;
	for(i=0;i<GetNumberOfIOChannels();i++){
		if(!isStremChannelMode(GetChannelMode(i)))
			SetChanelValueHW(i,1,& data[i], ms);
	}


    printValues();
    //printModes();
    setPrintLevel(l);

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
		if(!isStremChannelMode(GetChannelMode(i)))
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
	if(!isStremChannelMode(GetChannelMode(pin)))
		SetNewConfigurationDataTable( pin, data[0]);
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

boolean GetChannelValue(BowlerPacket * Packet){
	boolean ret=false; 
	uint8_t pin = Packet->use.data[0];
	uint8_t mode = GetChannelMode(pin);
	//int i;
	uint16_t val=GetChanVal(pin);
	if(IsAsync(pin)){
		//AsynAck();
	}
	Packet->use.head.Method=BOWLER_POST;
	if ((mode == IS_DC_MOTOR_VEL)||(mode == IS_DC_MOTOR_DIR)||(mode == IS_DO)|| (mode == IS_PWM)|| (mode == IS_SERVO) || (mode == IS_DI) ||(mode == IS_COUNTER_OUTPUT_HOME)||(mode == IS_COUNTER_INPUT_HOME)){
		set8bit(Packet, val,1);
		Packet->use.head.DataLegnth=6;
		ret = true; 
	}else if ((mode == IS_ANALOG_IN)){
		val=GetADC(pin);
		set16bit(Packet,val,1);
		Packet->use.head.DataLegnth=7;
		ret = true; 
	}else if ( (mode == IS_UART_TX) || (mode == IS_UART_RX)){
		//Number of bytes in the stream to be sent
		Packet->use.head.DataLegnth=5;
		uint16_t numBytes=Get_UART_Byte_CountPassThrough();
		if(numBytes>0){
			UARTGetArrayPassThrough(Packet->use.data+1,numBytes);
			//Offset using pointer, rather then shuffeling
//			for (i=0;i<numBytes;i++){
//				Packet->use.data[(numBytes)-i]=Packet->use.data[(numBytes-1)-i];
//			}
			Packet->use.data[0]=17;
			Packet->use.head.DataLegnth+=numBytes;
		}
		return true; 
	}else{
		return false; 
	}
	return ret;
}

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

//boolean SetAllChannelValue(BowlerPacket * Packet){
//	UINT32_UNION time;
//	UINT32_UNION data;
//	uint8_t i;
//	time.byte.FB=Packet->use.data[0];
//	time.byte.TB=Packet->use.data[1];
//	time.byte.SB=Packet->use.data[2];
//	time.byte.LB=Packet->use.data[3];
//	for(i=0;i<NUM_PINS;i++){
//		data.byte.FB=Packet->use.data[4+(i*4)];
//		data.byte.TB=Packet->use.data[5+(i*4)];
//		data.byte.SB=Packet->use.data[6+(i*4)];
//		data.byte.LB=Packet->use.data[7+(i*4)];
//		if(isASetableMode(GetChannelMode(i))){
//			 SetChanVal(i, data.Val, time.Val);
//		}
//	}
//
//
//	return true;
//}
//boolean SetChannelValue(BowlerPacket * Packet){
//	boolean ret=false;
//	uint8_t pin = Packet->use.data[0];
//	uint8_t mode = GetChannelMode(pin);
//	uint8_t bval;
//	UINT16_UNION wval;
//	uint8_t zone=128;
//	//println_I("Setting Value of mode: ");printMode(mode);print_I(" on pin:");p_int_I(pin);
//	if (isASetableMode(mode)){
//		bval = Packet->use.data[1];
//		if (Packet->use.head.DataLegnth>6){
//			wval.byte.SB = Packet->use.data[2];
//			wval.byte.LB = Packet->use.data[3];
//		}else{
//			//println_I("Packet was 6 or less data bytes");
//			wval.Val=0;
//		}
//		SetChanVal(pin,bval,(float)wval.Val);
//		ret = true;
//		READY(Packet,zone,0);
//	}else if ( (mode == IS_ANALOG_OUT)){
//		wval.byte.SB=Packet->use.data[1];
//		wval.byte.LB=Packet->use.data[2];
//		switch (mode){
//			default:
//				return false;
//			}
//		ret = true;
//	}else if ((mode == IS_UART_TX) || (mode == IS_UART_RX)){
//		//Number of bytes in the stream to be sent
//		uint8_t i;
//		bval = Packet->use.head.DataLegnth-5;
//		for (i=0;i<bval;i++){
//			WriteAVRUART1(Packet->use.data[i+1]);
//		}
//		return true;
//	}
//	return ret;
//}



boolean SetChanVal(uint8_t pin,int32_t bval, float time){

	uint8_t mode = GetChannelMode(pin);

		println_I("Setting channel pos\tchan: ");p_int_I(pin);
		print_I(" \tto val: ");p_int_I(bval);
		print_I("\tin time: ");p_fl_I(time);
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
			return false;
		}
		return true;

}
