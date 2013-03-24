/*
 * Abstract_bcs_io.c
 *
 *  Created on: Mar 21, 2013
 *      Author: hephaestus
 */

#include "Bowler/Bowler.h"
#include "Namespace/Namespace_bcs_io.h"


static int NumberOfIOChannels = 0;
static DATA_STRUCT * dataPtr = NULL;

BOOL (*setChanelValueHWPtr)(BYTE,BYTE*,INT32 *,float);
BOOL (*getChanelValueHWPtr)(BYTE,BYTE*,INT32 *);

void InitilizeBcsIo(int numPins,
					DATA_STRUCT * dataPtrLocal,
					BOOL (*setChanelValueHWPtrLocal)(BYTE,BYTE*,INT32 *,float),
					BOOL (*getChanelValueHWPtrLocal)(BYTE,BYTE*,INT32 *),
){
	if(	NumberOfIOChannels ==0||
		dataPtrLocal==NULL||
		setChanelValueHWPtrLocal==NULL||
		getChanelValueHWPtrLocal==NULL
	){
		//FAIL sanity check
		while(1);
	}

	NumberOfIOChannels = numPins;
	dataPtr = dataPtrLocal;
	setChanelValueHWPtr=setChanelValueHWPtrLocal;
	getChanelValueHWPtr=getChanelValueHWPtrLocal;
}


int GetNumberOfIOChannels(){
	return NumberOfIOChannels;
}

BYTE GetChannelMode(BYTE chan){
	if(chan>0 && chan<GetNumberOfIOChannels()){
		//FAIL sanity check
		while(1);
	}
	//Strip off the internally stored High Bit
	return getBcsIoDataTable()[chan].PIN.State & 0x7f;
}


DATA_STRUCT * getBcsIoDataTable(){
	if(dataPtr==NULL){
		//FAIL sanity check
		while(1);
	}
	return dataPtr;
}

BOOL GetChannelModeFromPacket(BowlerPacket * Packet){
	Packet->use.data[1]=GetChannelMode(Packet->use.data[0]);
	Packet->use.head.DataLegnth=6;
	Packet->use.head.Method=BOWLER_POST;
	return TRUE;
}


BOOL GetAllChannelModeFromPacket(BowlerPacket * Packet){
	int i;
	Packet->use.head.Method=BOWLER_POST;
	for (i=0;i<GetNumberOfIOChannels();i++){
		Packet->use.data[i]=GetChannelMode(i);
	}
	Packet->use.head.DataLegnth=4+GetNumberOfIOChannels();
	break;
	return TRUE;
}

BOOL GetAsyncFromPacket(BowlerPacket * Packet){
	Packet->use.head.Method=BOWLER_POST;
	Packet->use.data[1]=IsAsync(Packet->use.data[0]);
	Packet->use.head.DataLegnth=4+2;
	return TRUE;
}
BOOL GetIOChannelCountFromPacket(BowlerPacket * Packet){
	Packet->use.head.Method=BOWLER_POST;
	Packet->use.data[0]=GetNumberOfIOChannels();
	Packet->use.data[1]=0;
	Packet->use.data[2]=0;
	Packet->use.data[3]=0;
	Packet->use.head.DataLegnth=4+4;
	return TRUE;
}



BOOL pinHasFunction(BYTE pin, BYTE function){
	switch(function){
	case IS_DI:
		return TRUE;
	case IS_DO:
		return TRUE;
	case IS_ANALOG_IN:
		return getBcsIoDataTable()[pin].FUNCTION.HAS_ANALOG_IN;
	case IS_ANALOG_OUT:
		return FALSE;
		//return getBcsIoDataTable()[pin].FUNCTION.HAS_ANALOG_OUT;
	case IS_PWM:
		return getBcsIoDataTable()[pin].FUNCTION.HAS_PWM;
	case IS_SERVO:
		return TRUE;
	case IS_UART_TX:
		return getBcsIoDataTable()[pin].FUNCTION.HAS_UART_T;
	case IS_UART_RX:
		return getBcsIoDataTable()[pin].FUNCTION.HAS_UART_R;
	case IS_SPI_MOSI:
		return getBcsIoDataTable()[pin].FUNCTION.HAS_SPI_O;
	case IS_SPI_MISO:
		return getBcsIoDataTable()[pin].FUNCTION.HAS_SPI_I;
	case IS_SPI_SCK	:
		return getBcsIoDataTable()[pin].FUNCTION.HAS_SPI_C;
	case IS_COUNTER_INPUT_INT:
		return getBcsIoDataTable()[pin].FUNCTION.HAS_COUNTER_INPUT_I;
	case IS_COUNTER_INPUT_DIR:
		return getBcsIoDataTable()[pin].FUNCTION.HAS_COUNTER_INPUT_D;
	case IS_COUNTER_INPUT_HOME:
		return getBcsIoDataTable()[pin].FUNCTION.HAS_COUNTER_INPUT_H;
	case IS_COUNTER_OUTPUT_INT:
		return getBcsIoDataTable()[pin].FUNCTION.HAS_COUNTER_OUTPUT_I;
	case IS_COUNTER_OUTPUT_DIR:
		return getBcsIoDataTable()[pin].FUNCTION.HAS_COUNTER_OUTPUT_D;
	case IS_COUNTER_OUTPUT_HOME:
		return getBcsIoDataTable()[pin].FUNCTION.HAS_COUNTER_OUTPUT_H;
	case IS_DC_MOTOR_VEL:
		return getBcsIoDataTable()[pin].FUNCTION.HAS_PWM;
	case IS_DC_MOTOR_DIR:
		return getBcsIoDataTable()[pin].FUNCTION.HAS_DC_MOTOR;
	case IS_PPM_IN:
		return getBcsIoDataTable()[pin].FUNCTION.HAS_PPM;
	default:
		return FALSE;
	}
}

BOOL getFunctionList(BowlerPacket * Packet){
	int chan = Packet->use.data[0];

	int index =0;
	int i=0;
	for(i=0;i<IO_MODE_MAX;i++){
		if(pinHasFunction(chan,i)){
			Packet->use.data[index++]=i;
		}
	}
	Packet->use.head.DataLegnth=4+index;
	return TRUE;
}
