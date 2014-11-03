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

void UserInit(void){
	StartCritical();

	//println_W(startmessage);// All printfDEBUG functions do not need to be removed from code if debug is disabled
#if defined(DEBUG)
	ConfigureUART(115200);
	if(GetChannelMode(16)!=IS_UART_TX)
		setMode(16,IS_UART_TX);
#endif
	setPrintLevelInfoPrint();
	println_I(/*PSTR*/("\e[1;1H\e[2J ***Starting User initialization***"));
	InitFlagPins();
	InitBankLEDs();
	SetPowerState0(0,0);
	SetPowerState1(0,0);


	//_delay_ms(1);

#if defined(WPIRBE)
	SPISlaveInit();
#endif



	InitPins();
	//println_I(/*PSTR*/("Adding IO Initialization"));
	addNamespaceToList((NAMESPACE_LIST *)get_bcsIoNamespace());
	//println_I(/*PSTR*/("Adding IO.SETMODE Initialization"));
	addNamespaceToList((NAMESPACE_LIST *)get_bcsIoSetmodeNamespace());
	//println_I(/*PSTR*/("Adding Internal Initialization"));
	addNamespaceToList((NAMESPACE_LIST *)get_internalNamespace());
	setNoAsyncMode(true);
	//SetPinTris(0,OUTPUT);
	//SetDIO(0,OFF);

#if defined(USE_AS_LIBRARY)
	InitializeUserCode();
#endif
	EndCritical();
	println_I(/*PSTR*/("Starting Pin Initialization"));
//	setMode(22,IS_DO);
//	setMode(23,IS_DI);
//	println_I(/*PSTR*/("Pin done"));
}


