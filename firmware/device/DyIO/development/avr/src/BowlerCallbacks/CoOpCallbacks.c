/*
 *
 * Copyright 2009 Neuron Robotics, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "UserApp_avr.h"

void setDig(BYTE pin, BYTE val);
void setAnv(BYTE pin, UINT16 val);
//typedef struct __attribute__((__packed__)) _DIG_VALS{
////	unsigned b0;
////	unsigned b1;
////	unsigned b2;
////	unsigned b3;
////	unsigned b4;
////	unsigned b5;
////	unsigned b6;
////	unsigned b7;
////	unsigned b8;
////	unsigned b9 ;
////	unsigned b10;
////	unsigned b11;
////	unsigned b12;
////	unsigned b13;
////	unsigned b14;
////	unsigned b15;
////	unsigned b16;
////	unsigned b17;
////	unsigned b18;
////	unsigned b19;
////	unsigned b20;
////	unsigned b21;
////	unsigned b22;
////	unsigned b23;
////	unsigned 	 :8;
//	BYTE b0;
//	BYTE b1;
//	BYTE b2;
//	BYTE b3;
//	BYTE b4;
//	BYTE b5;
//	BYTE b6;
//	BYTE b7;
//	BYTE b8;
//	BYTE b9 ;
//	BYTE b10;
//	BYTE b11;
//	BYTE b12;
//	BYTE b13;
//	BYTE b14;
//	BYTE b15;
//	BYTE b16;
//	BYTE b17;
//	BYTE b18;
//	BYTE b19;
//	BYTE b20;
//	BYTE b21;
//	BYTE b22;
//	BYTE b23;
//} DIG_VALS;
//typedef struct __attribute__((__packed__)) _ADC_VALS{
//	unsigned b0 :11;
//	unsigned b1 :11;
//	unsigned b2 :11;
//	unsigned b3 :11;
//	unsigned b4 :11;
//	unsigned b5 :11;
//	unsigned b6 :11;
//	unsigned b7 :11;
//
////	UINT16 b0 ;
////	UINT16 b1 ;
////	UINT16 b2 ;
////	UINT16 b3 ;
////	UINT16 b4 ;
////	UINT16 b5 ;
////	UINT16 b6 ;
////	UINT16 b7 ;
//
//} ADC_VALS;
//
//static DIG_VALS dig;
//static ADC_VALS adv;

//BYTE DI_PUSH_val[24];
//UINT16 ADC_val[8];
#define ANALOG_DEAD_BAND 1
//BOOL ack=FALSE;
//RunEveryData asyncSched = {0,10.0};
#define blockTime 24.0f
#define blockInc1 (blockTime/3.0f)
#define blockInc2 (blockInc1+blockInc1)
RunEveryData block0 = {0,blockTime};
RunEveryData block1 = {blockInc1,blockTime};
RunEveryData block2 = {blockInc2,blockTime};

//static BYTE asyncIndex = 0;

void initPinState(BYTE i){
	BYTE mode =GetChannelMode(i);
	if ((mode == IS_ANALOG_IN) ){
		setAnv(i,GetADC(i));
	}else if(((mode == IS_DI) )  || ((mode == IS_COUNTER_INPUT_HOME)||(mode == IS_COUNTER_OUTPUT_HOME))){
		setDig(i,GetDIO(i)?1:0);
	}else{
		SetValFromAsync(i,0);
	}
}

INT16 aval;
BOOL checkAnalog(){
	BOOL update=FALSE;
	int i=0;
	for(i=8;i<16;i++){
		if ((GetChannelMode(i) == IS_ANALOG_IN) ){
			aval = GetADC(i);
			setAnv(i,aval);
		}
	}
	return update;
}
BOOL checkDigital(){
	int i;
	BOOL update=FALSE;
	for(i=0;i<GetNumberOfIOChannels();i++){
		BYTE mode = GetChannelMode(i);
		BOOL run = (((mode == IS_DI) )  || ((mode == IS_COUNTER_INPUT_HOME)||(mode == IS_COUNTER_OUTPUT_HOME) || (mode == IS_SERVO)));
		if (run){
			if(mode == IS_SERVO){
				aval=GetServoPos(i);
			}else{
				aval=GetDIO(i);
			}
			setDig(i,aval);
		}
	}
	return update;
}

void resetBlocks(){
#if ! defined(__AVR_ATmega324P__)
	println_E("Block times b0: ");p_fl_E(block0.MsTime);print_E(", b1: ");p_fl_E(block1.MsTime);print_E(", b2: ");p_fl_E(block2.MsTime);
#endif
	block0.setPoint = blockTime;
	block0.MsTime=getMs();

	block1.setPoint = blockTime;
	block1.MsTime=block0.MsTime+blockInc1 ;

	block2.setPoint = blockTime;
	block2.MsTime=block0.MsTime+blockInc2 ;
#if ! defined(__AVR_ATmega324P__)
	println_E("Fixed to values, b0: ");p_fl_E(block0.MsTime);print_E(", b1: ");p_fl_E(block1.MsTime);print_E(", b2: ");p_fl_E(block2.MsTime);
#endif
}

void UserRun(void){
#if defined(DEBUG)
	if(GetChannelMode(16)!=IS_UART_TX){
		setMode(16,IS_UART_TX);
		ConfigureUART(115200);
	}
#endif
#if defined(WPIRBE)
	SPISlaveServer();
#endif
#if defined(USE_AS_LIBRARY)
	RunUserCode();
#endif

	if (Get_UART_Byte_CountPassThrough()>0){
		PushSerial();
	}

	if(block0.MsTime < 0.0f){
#if ! defined(__AVR_ATmega324P__)
		println_I("Block0 error, ");p_fl_I(block0.MsTime);
#endif
		resetBlocks();
	}
	if(block1.MsTime < 0.0f){
#if ! defined(__AVR_ATmega324P__)
		println_I("Block1 error, ");p_fl_I(block1.MsTime);
#endif
		resetBlocks();
	}
	if(block2.MsTime < 0.0f){
#if ! defined(__AVR_ATmega324P__)
		println_I("Block2 error, ");p_fl_I(block2.MsTime);
#endif
		resetBlocks();
	}

	if (RunEvery(&block0)>0.0f){
		//println_I("Step 0");
		//
		block0.MsTime = getMs();
		RunServo(0);
		//return;
	}
	if (RunEvery(&block1)>0.0f){
		//println_I("Step 1");
		RunServo(1);
		//return;
	}
	if (RunEvery(&block2)>0.0f){
		//println_I("Step 2");
		RunServo(2);
		//Re-align the offsets for the servos
		block0.setPoint = blockTime;
		block1.setPoint = blockTime;
		block2.setPoint = blockTime;
		block1.MsTime=block0.MsTime+blockInc1 ;
		block2.MsTime=block0.MsTime+blockInc2 ;
	}
}

void AsynAck(void){
	ack=TRUE;
}
BOOL getDig(BYTE pin){
	return GetValFromAsync(pin);
}

void setDig(BYTE pin, BYTE val){
	SetValFromAsync(pin,val);
}

UINT16 getAnv(BYTE pin){
	return GetValFromAsync(pin);
}
void setAnv(BYTE pin,UINT16 val){
	SetValFromAsync(pin,val);
}

//BOOL getDig(BYTE pin){
//	switch(pin){
//	case 0:
//		return dig.b0;
//	case 1:
//		return dig.b1;
//	case 2:
//		return dig.b2;
//	case 3:
//		return dig.b3;
//	case 4:
//		return dig.b4;
//	case 5:
//		return dig.b5;
//	case 6:
//		return dig.b6;
//	case 7:
//		return dig.b7;
//	case 8:
//		return dig.b8;
//	case 9:
//		return dig.b9;
//	case 10:
//		return dig.b10;
//	case 11:
//		return dig.b11;
//	case 12:
//		return dig.b12;
//	case 13:
//		return dig.b13;
//	case 14:
//		return dig.b14;
//	case 15:
//		return dig.b15;
//	case 16:
//		return dig.b16;
//	case 17:
//		return dig.b17;
//	case 18:
//		return dig.b18;
//	case 19:
//		return dig.b19;
//	case 20:
//		return dig.b20;
//	case 21:
//		return dig.b21;
//	case 22:
//		return dig.b22;
//	case 23:
//		return dig.b23;
//	default:
//		return 0;
//	}
//}
//
//void setDig(BYTE pin, BYTE val){
//	switch(pin){
//	case 0:
//		dig.b0=val;
//		return;
//	case 1:
//		dig.b1=val;
//		return;
//	case 2:
//		dig.b2=val;
//		return;
//	case 3:
//		dig.b3=val;
//		return;
//	case 4:
//		dig.b4=val;
//		return;
//	case 5:
//		dig.b5=val;
//		return;
//	case 6:
//		dig.b6=val;
//		return;
//	case 7:
//		dig.b7=val;
//		return;
//	case 8:
//		dig.b8=val;
//		return;
//	case 9:
//		dig.b9=val;
//		return;
//	case 10:
//		dig.b10=val;
//		return;
//	case 11:
//		dig.b11=val;
//		return;
//	case 12:
//		dig.b12=val;
//		return;
//	case 13:
//		dig.b13=val;
//		return;
//	case 14:
//		dig.b14=val;
//		return;
//	case 15:
//		dig.b15=val;
//		return;
//	case 16:
//		dig.b16=val;
//		return;
//	case 17:
//		dig.b17=val;
//		return;
//	case 18:
//		dig.b18=val;
//		return;
//	case 19:
//		dig.b19=val;
//		return;
//	case 20:
//		dig.b20=val;
//		return;
//	case 21:
//		dig.b21=val;
//		return;
//	case 22:
//		dig.b22=val;
//		return;
//	case 23:
//		dig.b23=val;
//		return;
//	}
//}
//
//UINT16 getAnv(BYTE pin){
//	switch(pin){
//	case 8:
//		return adv.b0;
//	case 9:
//		return adv.b1;
//	case 10:
//		return adv.b2;
//	case 11:
//		return adv.b3;
//	case 12:
//		return adv.b4;
//	case 13:
//		return adv.b5;
//	case 14:
//		return adv.b6;
//	case 15:
//		return adv.b7;
//	default:
//		return 0;
//	}
//}
//void setAnv(BYTE pin,UINT16 val){
//	switch(pin){
//	case 8:
//		adv.b0=val;
//		return;
//	case 9:
//		adv.b1=val;
//		return;
//	case 10:
//		adv.b2=val;
//		return;
//	case 11:
//		adv.b3=val;
//		return;
//	case 12:
//		adv.b4=val;
//		return;
//	case 13:
//		adv.b5=val;
//		return;
//	case 14:
//		adv.b6=val;
//		return;
//	case 15:
//		adv.b7=val;
//		return;
//	}
//}
