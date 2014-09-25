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

#define ANALOG_DEAD_BAND 1

#define blockTime 24.0f
#define blockInc1 (blockTime/3.0f)
#define blockInc2 (blockInc1+blockInc1)
RunEveryData block0 = {0,blockTime};
RunEveryData block1 = {blockInc1,blockTime};
RunEveryData block2 = {blockInc2,blockTime};


void initPinState(uint8_t i){
	uint8_t mode =GetChannelMode(i);
	if ((mode == IS_ANALOG_IN) ){
		SetValFromAsync(i,GetADC(i));
	}else if(((mode == IS_DI) )  || ((mode == IS_COUNTER_INPUT_HOME)||(mode == IS_COUNTER_OUTPUT_HOME))){
		SetValFromAsync(i,GetDIO(i)?1:0);
	}else{
		SetValFromAsync(i,0);
	}
}

boolean checkAnalog(){
	int i=0;
	for(i=8;i<16;i++){
		if ((GetChannelMode(i) == IS_ANALOG_IN) ){
			SetValFromAsync(i, GetADC(i));
		}
	}
	return true; 
}
boolean checkDigital(){
	int i;
	for(i=0;i<GetNumberOfIOChannels();i++){
		uint8_t mode = GetChannelMode(i);
		boolean run = (((mode == IS_DI) )  || ((mode == IS_COUNTER_INPUT_HOME)||(mode == IS_COUNTER_OUTPUT_HOME) || (mode == IS_SERVO)));
		if (run){
			if(mode == IS_SERVO){
				SetValFromAsync(i,GetServoPos(i));
			}else{
				if(GetValFromAsync(i) != GetDIO(i)){
					SetValFromAsync(i,GetDIO(i));
					//printAsync();
				}
			}
		}
	}
	return true; 
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
