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

RunEveryData block0 = {0,1000};


void initPinState(uint8_t i){
	uint8_t mode =GetChannelMode(i);
	if ((mode == IS_ANALOG_IN) ){
		setDataTableCurrentValue(i,GetADC(i));
	}else if(((mode == IS_DI) )  || ((mode == IS_COUNTER_INPUT_HOME)||(mode == IS_COUNTER_OUTPUT_HOME))){
		setDataTableCurrentValue(i,GetDIO(i)?1:0);
	}else{
		//setDataTableCurrentValue(i,0);
	}
}

boolean checkAnalog(){
	int i=0;
	for(i=8;i<16;i++){
		if ((GetChannelMode(i) == IS_ANALOG_IN) ){
			setDataTableCurrentValue(i, GetADC(i));
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
				//setDataTableCurrentValue(i,GetServoPos(i));
			}else{
				if(GetValFromAsync(i) != GetDIO(i)){
					setDataTableCurrentValue(i,GetDIO(i));
					//printAsync();
				}
			}
		}
		if(mode == IS_UART_RX){
			setDataTableCurrentValue(i,Get_UART_Byte_CountPassThrough());
		}
	}
	return true; 
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

//	if (Get_UART_Byte_CountPassThrough()>0){
//		PushSerial();
//	}

	if (RunEvery(&block0)>0.0f){
		//println_W("Loop ");p_fl_W(getMs()/1000);
	}

}
