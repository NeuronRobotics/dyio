/*
 * ChannelValues.c
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */
#include "UserApp.h"


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

}

/**
 * Set Channel Values
 * This function takes a pin index, a number of values to be delt with, and an array of data values
 * Data is stored into numValues and data
 */
BOOL GetChanelValueHW(BYTE pin,BYTE * numValues,INT32 * data){

}
/**
 * Set Channel Values
 * This function takes a
 * @param data an array of data values
 * @param ms the time for the transition to take
 *
 */
BOOL SetAllChanelValueHW(INT32 * data, float ms){

}

/**
 * Set Channel Values
 * This function takes a pin index, a number of values to be delt with, and an array of data values
 * Data is stored into numValues and data
 */
BOOL GetAllChanelValueHW(INT32 * data){

}

/**
 * Configure Channel
 * @param pin the index of the channel to configure
 * @param numValues The number of values passed in to deal with
 * @param data the array of values to use in the configuration step
 */

BOOL ConfigureChannelHW(BYTE pin,BYTE numValues,INT32 * data){

}

void set8bit(BowlerPacket * Packet,BYTE val);
void set16bit(BowlerPacket * Packet,WORD val);
void set32bit(BowlerPacket * Packet,INT32 val);
INT32 get32bit(BowlerPacket * Packet, BYTE offset);

BOOL GetChannelValue(BowlerPacket * Packet){
	BOOL ret=FALSE;
	BYTE pin = Packet->use.data[0];
	BYTE mode = GetChannelMode(pin);
	switch(mode){
		case IS_SPI_MOSI:
		case IS_SPI_MISO:
		case IS_SPI_SCK:
		//case IS_SPI_SS:
			println_I("SPI ");
			printMode(mode,INFO_PRINT);
			SendPacketToSPI(Packet);
			Packet->use.head.Method=BOWLER_POST;
			return TRUE;
		case IS_COUNTER_INPUT_INT:
		case IS_COUNTER_INPUT_DIR:
		case IS_COUNTER_INPUT_HOME:
			println_I("Counter input ");
			printMode(mode,INFO_PRINT);
			set32bit(Packet,GetCounterByChannel(pin));
			Packet->use.head.DataLegnth=9;
			Packet->use.head.Method=BOWLER_POST;
			return TRUE;
		case IS_COUNTER_OUTPUT_INT:
		case IS_COUNTER_OUTPUT_DIR:
		case IS_COUNTER_OUTPUT_HOME:
			println_I("Counter output ");
			printMode(mode,INFO_PRINT);
			set32bit(Packet,GetCounterOutput(pin));
			Packet->use.head.DataLegnth=9;
			Packet->use.head.Method=BOWLER_POST;
			return TRUE;
		case IS_PPM_IN:
			GetPPMDataToPacket(Packet);
			return TRUE;
		default:
			println_I("Get Mode not managed by PIC, sending to co-proc ");printMode(mode,INFO_PRINT);
			SendPacketToCoProc(Packet);
			return TRUE;
		}
}
BOOL isASetableMode(BYTE mode){
	switch(mode&0x7f){
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
	case IS_COUNTER_OUTPUT_INT:
	case IS_COUNTER_OUTPUT_DIR:
	case IS_COUNTER_OUTPUT_HOME:
		return TRUE;
	}
	return FALSE;
}
BOOL SetAllChannelValue(BowlerPacket * Packet){
	//println_I("Setting all channel values");
	UINT32_UNION time;
	UINT32_UNION data;
	BYTE i;
	time.byte.FB=Packet->use.data[0];
	time.byte.TB=Packet->use.data[1];
	time.byte.SB=Packet->use.data[2];
	time.byte.LB=Packet->use.data[3];
	for(i=0;i<NUM_PINS;i++){
		if(isASetableMode(GetChannelMode(i))){
			data.byte.FB=Packet->use.data[4+(i*4)];
			data.byte.TB=Packet->use.data[5+(i*4)];
			data.byte.SB=Packet->use.data[6+(i*4)];
			data.byte.LB=Packet->use.data[7+(i*4)];
			SetChanVal(i, data.Val, time.Val);
		}
	}
	SendPacketToCoProc(Packet);
	return TRUE;
}
BOOL SetChannelValue(BowlerPacket * Packet){
	BYTE pin = Packet->use.data[0];
	BYTE mode = GetChannelMode(pin);
	//BYTE bval;
	//INT32_UNION lval;
	//println_I("Attempting to set Channel...");
	switch(mode){
	case IS_SPI_MOSI:
	case IS_SPI_MISO:
	case IS_SPI_SCK:
		//println_I("SPI ");
		//printMode(mode,INFO_PRINT);
		SendPacketToSPI(Packet);
		Packet->use.head.Method = BOWLER_POST;
		return TRUE;
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
	case IS_COUNTER_OUTPUT_INT:
	case IS_COUNTER_OUTPUT_DIR:
	case IS_COUNTER_OUTPUT_HOME:
		SetChanVal(pin,get32bit(Packet,1),get32bit(Packet,5));
		return TRUE;
	case IS_UART_TX:
	case IS_UART_RX:
		SendToSerialPassThrough(Packet);
		return TRUE;
	case IS_PPM_IN:
		ConfigPPM(Packet);
		return TRUE;
	default:
		println_I("Set Mode not managed by PIC, sending to co-proc ");
		printMode(mode,INFO_PRINT);
		SendPacketToCoProc(Packet);
		return (Packet->use.head.RPC != _ERR);
	}
}
BOOL SetChanVal(BYTE pin,INT32 bval, float time){
	BYTE mode = GetChannelMode(pin);
	switch (mode){
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_INPUT_DIR:
	case IS_COUNTER_INPUT_HOME:
		println_I("Counter input ");
		printMode(mode,INFO_PRINT);
		SetCounterInput(pin,bval);
		return TRUE;
	case IS_COUNTER_OUTPUT_INT:
	case IS_COUNTER_OUTPUT_DIR:
	case IS_COUNTER_OUTPUT_HOME:
		println_I("Counter output ");
		printMode(mode,INFO_PRINT);
		SetCounterOutput(pin,bval,time);
		return TRUE;
	}
	return TRUE;
}


void set8bit(BowlerPacket * Packet,BYTE val){
	Packet->use.data[1]=val;
}
void set16bit(BowlerPacket * Packet,WORD val){
	UINT16_UNION wval;
	wval.Val=val;
	Packet->use.data[1]=wval.byte.SB;
	Packet->use.data[2]=wval.byte.LB;
}
void set32bit(BowlerPacket * Packet,INT32 val){
	INT32_UNION lval;
	lval.Val=val;
	Packet->use.data[1]=lval.byte.FB;
	Packet->use.data[2]=lval.byte.TB;
	Packet->use.data[3]=lval.byte.SB;
	Packet->use.data[4]=lval.byte.LB;
}
INT32 get32bit(BowlerPacket * Packet, BYTE offset){
	INT32_UNION lval;
	lval.byte.FB=Packet->use.data[0+offset];
	lval.byte.TB=Packet->use.data[1+offset];
	lval.byte.SB=Packet->use.data[2+offset];
	lval.byte.LB=Packet->use.data[3+offset];
	return lval.Val;
}
