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

BOOL (*setChanelValueHWPtr)(BYTE,BYTE,INT32 *,float);
BOOL (*getChanelValueHWPtr)(BYTE,BYTE*,INT32 *);
BOOL (*setAllChanelValueHWPtr)(INT32 *,float);
BOOL (*getAllChanelValueHWPtr)(INT32 *);
BOOL (*configChannelHWPtr)(BYTE,BYTE,INT32 *);


BOOL bcsIoProcessor_c(BowlerPacket * Packet){
	int zone=2;
	switch (Packet->use.head.RPC){
	case CCHN:
		SendPacketToCoProc(Packet);
		break;
	case SCHV:
		getBcsIoDataTable()[Packet->use.data[0]].PIN.ServoPos=Packet->use.data[1];
		SendPacketToCoProc(Packet);
		break;
	}
	return TRUE;
}

void InitilizeBcsIo(int numPins,
					DATA_STRUCT * dataPtrLocal,
					BOOL (*setChanelValueHWPtrLocal)(BYTE,BYTE,INT32 *,float),
					BOOL (*getChanelValueHWPtrLocal)(BYTE,BYTE*,INT32 *),
					BOOL (*setAllChanelValueHWPtrLocal)(INT32 *,float),
					BOOL (*getAllChanelValueHWPtrLocal)(INT32 *),
					BOOL (*configChannelHWPtrLocal)(BYTE,BYTE,INT32 *)
){
	if(	NumberOfIOChannels < 1 ||
		dataPtrLocal==NULL||
		setChanelValueHWPtrLocal==NULL||
		getChanelValueHWPtrLocal==NULL||
		setAllChanelValueHWPtrLocal==NULL||
		getAllChanelValueHWPtrLocal==NULL||
		configChannelHWPtrLocal==NULL
	){
		//FAIL sanity check
		while(1);
	}

	NumberOfIOChannels = numPins;
	dataPtr = dataPtrLocal;
	setChanelValueHWPtr=setChanelValueHWPtrLocal;
	getChanelValueHWPtr=getChanelValueHWPtrLocal;
	setAllChanelValueHWPtr=setAllChanelValueHWPtrLocal;
	getAllChanelValueHWPtr=getAllChanelValueHWPtrLocal;
	configChannelHWPtr=configChannelHWPtrLocal;
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
	return getBcsIoDataTable()[chan].PIN.currentChannelMode & 0x7f;
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
BOOL SetAsyncFromPacket(BowlerPacket * Packet){
	Packet->use.head.Method=BOWLER_POST;
	setAsync(Packet->use.data[0],Packet->use.data[1]);
	Packet->use.head.DataLegnth=4;
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

BOOL SetChanelValueFromPacket(BowlerPacket * Packet){
	BYTE pin = Packet->use.data[0];
	BYTE mode = GetChannelMode(pin);
	if(isStremChannelMode(mode)){
		if(setChanelValueHWPtr!=NULL)
			// Load the data directly into the packet as the buffer
			//Data pointer is offset by one to start after the pin index
			setChanelValueHWPtr(pin,
								Packet->use.head.DataLegnth-(4+1),
								(Packet->use.data)+1,
								(float)0);
			READY(Packet,1,3);
	}else{
		UINT32 data = 0;
		UINT32 time = 0;

		if(isSingleByteMode(mode)){
			data = Packet->use.data[1];
			if (Packet->use.head.DataLegnth>(4+2)){
				time = get16bit(Packet,2);
			}else{
				time=0;
			}
		}else if(isTwoByteMode(mode)){
			data=get16bit(Packet,1);
			if (Packet->use.head.DataLegnth>(4+3)){
				time=time = get32bit(Packet,3);
			}else{
				time=0;
			}
		}else{
			data=get32bit(Packet,1);
			if (Packet->use.head.DataLegnth>(4+5)){
				time=time = get32bit(Packet,5);
			}else{
				time=0;
			}
		}
		if(setChanelValueHWPtr!=NULL)
			setChanelValueHWPtr(pin,1,&data,(float)time);
		READY(Packet,2,3);
	}

	return TRUE;
}
BOOL SetAllChannelValueFromPacket(BowlerPacket * Packet){
	if(setAllChanelValueHWPtr!=NULL){
		UINT32_UNION time;
		BYTE i;
		time.byte.FB=Packet->use.data[0];
		time.byte.TB=Packet->use.data[1];
		time.byte.SB=Packet->use.data[2];
		time.byte.LB=Packet->use.data[3];
		//REVERSE?
		setAllChanelValueHWPtr(((INT32 *)Packet->use.data)+4,time.Val);
		READY(Packet,3,3);
	}else{
		return FALSE;
	}
	return TRUE;
}
BOOL GetChanelValueFromPacket(BowlerPacket * Packet){
	BYTE pin = Packet->use.data[0];
	BYTE mode = GetChannelMode(pin);
	BYTE numValues;
	if(isStremChannelMode(mode)){

		if(getChanelValueHWPtr!=NULL){
			// Load the data directly into the packet as the buffer
			//Data pointer is offset by one to start after the pin index
			getChanelValueHWPtr(pin,
								&numValues,
								(Packet->use.data)+1);
			Packet->use.head.DataLegnth = 4+1+numValues;
		}else{
			return FALSE;
		}
	}else{
		UINT32 data;
		if(getChanelValueHWPtr!=NULL){
			getChanelValueHWPtr(pin,
								&numValues,
								&data);
		}else{
			return FALSE;
		}
		if(isSingleByteMode(mode)){
			set8bit(Packet,data, 1);
			numValues=1;
		}else if(isTwoByteMode(mode)){
			set16bit(Packet,data, 1);
			numValues=2;
		}else{
			set32bit(Packet,data, 1);
			numValues=4;
		}
		Packet->use.head.DataLegnth = 4+1+numValues;
	}
	return TRUE;
}
BOOL GetAllChanelValueFromPacket(BowlerPacket * Packet){
	if(getAllChanelValueHWPtr!=NULL){
		//REVERSE?
		getAllChanelValueHWPtr((INT32 * )Packet->use.data);
		Packet->use.head.DataLegnth = 4+GetNumberOfIOChannels()*4;
	}else
		return FALSE;
	return TRUE;
}
BOOL ConfigureChannelFromPacket(BowlerPacket * Packet){
	BYTE pin = Packet->use.data[0];
	BYTE mode = GetChannelMode(pin);

	if(configChannelHWPtr!=NULL){
		if(Packet->use.head.DataLegnth>5 && mode != IS_SERVO){
			int numVals = (Packet->use.head.DataLegnth-(4+1))/4;
			//REVERSE?
			configChannelHWPtr(pin,numVals,(INT32 * )(Packet->use.data+1));
		}else{
			// Single Byte Servo, legacy HACK
			INT32 value  = Packet->use.data[1];
			configChannelHWPtr(pin,1,&value);
		}
	}else{
		return FALSE;
	}
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

void set8bit(BowlerPacket * Packet,BYTE val, BYTE offset){
	Packet->use.data[1+offset]=val;
}
void set16bit(BowlerPacket * Packet,WORD val, BYTE offset){
	UINT16_UNION wval;
	wval.Val=val;
	Packet->use.data[1+offset]=wval.byte.SB;
	Packet->use.data[2+offset]=wval.byte.LB;
}
void set32bit(BowlerPacket * Packet,INT32 val, BYTE offset){
	INT32_UNION lval;
	lval.Val=val;
	Packet->use.data[1+offset]=lval.byte.FB;
	Packet->use.data[2+offset]=lval.byte.TB;
	Packet->use.data[3+offset]=lval.byte.SB;
	Packet->use.data[4+offset]=lval.byte.LB;
}
INT32 get32bit(BowlerPacket * Packet, BYTE offset){
	INT32_UNION lval;
	lval.byte.FB=Packet->use.data[0+offset];
	lval.byte.TB=Packet->use.data[1+offset];
	lval.byte.SB=Packet->use.data[2+offset];
	lval.byte.LB=Packet->use.data[3+offset];
	return lval.Val;
}

INT32 get16bit(BowlerPacket * Packet, BYTE offset){
	UINT16_UNION wval;
	wval.byte.SB=Packet->use.data[0+offset];
	wval.byte.LB=Packet->use.data[1+offset];
	return wval.Val;
}


