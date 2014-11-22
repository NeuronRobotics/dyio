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


boolean powerOverRide = true;

INTERPOLATE_DATA velocity[NUM_PINS];
void runLinearInterpolationServo(uint8_t blockStart,uint8_t blockEnd);
boolean pinServoOk(uint8_t pin);

uint8_t pinOn(uint8_t pin);
void pinOff(uint8_t pin);

boolean servoEngineStarted =false;

void InitServo(uint8_t PIN){
	//println_I("Starting servo");
	ClearPinState(PIN);
	SetPinTris(PIN,OUTPUT);
	//DATA.PIN[PIN].State=IS_SERVO;
	SetServoPos(PIN,EEReadValue(PIN),0);
	if( servoEngineStarted != true){
		servoEngineStarted =true;
		setTimerLowTime();
	}
	TIMSK1bits._OCIE1A=1;
}

void setPowerOverride(boolean set){
	println_W("powerOverRide: ");p_int_W(set);
	//powerOverRide = set;
}
uint8_t b0OK=true;
uint8_t b1OK=true;
uint8_t b0lock=false;
uint8_t b1lock=false;
//uint8_t b0OK=false;
//uint8_t b1OK=false;
//uint8_t b0lock=true;
//uint8_t b1lock=true;

void SetPowerState0(boolean railOk,boolean regulated){
	return;
	b0OK=false; 
	if (regulated == 1){
		Bank0Green();
	}else {
		if(railOk==2 ||  railOk==1){
			b0OK=true; 
		}
		if(railOk ==1 ||railOk ==3  ){
			Bank0Red();
		}else{
			Bank0Off();
		}
		if(railOk == 3||railOk == 0 ){
			b0lock=true; 
		}
	}
}
void SetPowerState1(boolean railOk,boolean regulated){
	return;
	b1OK=false; 
	if (regulated==1){
		Bank1Green();
	}else {
		if(railOk ==1 ||railOk ==3  ){
			Bank1Red();
		}else{
			Bank1Off();
		}
		if(railOk==2 ||  railOk==1){
			b1OK=true; 
		}
		if(railOk == 3 ||railOk == 0 ){
			b1lock=true; 
		}
	}
}
boolean print = 0xff;
void SetServoPos(uint8_t pin,uint8_t val,float time){
	if(time<30)
		time=0;
	if(val == velocity[pin].set){
		return;
	}


	velocity[pin].setTime=time;
	velocity[pin].set=(float)val;
	velocity[pin].start=(float)getBcsIoDataTable(pin)->PIN.currentValue;
	velocity[pin].startTime=getMs();
	if (val==getBcsIoDataTable(pin)->PIN.currentValue){
		velocity[pin].setTime=0;
	}
	if(pin<12){
		b0lock=false; 
	}else{
		b1lock=false; 
	}
	if(GetChannelMode(pin)!=IS_SERVO)
		return;
	print = pin;

//	if(pinServoOk(pin) == false){
//		println_W("Servo\tchan: ");p_int_W(pin);
//		print_W(" \tto val: ");p_int_W(val);
//		print_W("\tin time: ");p_fl_W(time);
//		if(pin > 11){
//			print_W(" \tb1OK: ");p_int_W(b1OK);
//			print_W(" \tpowerOverRide: ");p_int_W(powerOverRide);
//			print_W(" \tb1lock: ");p_int_W(b1lock);
//		}else{
//			print_W(" \tb0OK: ");p_int_W(b0OK);
//			print_W(" \tpowerOverRide: ");p_int_W(powerOverRide);
//			print_W(" \tb0lock: ");p_int_W(b0lock);
//		}
//	}

}
uint8_t GetServoPos(uint8_t pin){
	return getBcsIoDataTable(pin)->PIN.currentValue;
}

//void RunServo(uint8_t block){
//
//	return;//short circuit servo system
//	//disableDebug();
//	uint16_t j;
//	uint8_t xIndex;
//	//return;
//	uint8_t start=block*BLOCK_SIZE;
//	uint8_t stop=(block*BLOCK_SIZE)+BLOCK_SIZE;
//
//	runLinearInterpolationServo(start,stop);
//	FlagBusy_IO=1;
//	//Short delay to allow any stray transactions to finish
//	_delay_us(800);
//	uint8_t num=0;
//	for (j=start;j<stop;j++){
//		num+=pinOn(j);
//	}
//	//run minimal .75 ms pulse
//	DelayPreServo();
//	//loop 255 times and turn off all servos as their set position is equal to the loop counter
//	for (j=0;j<256;j++){
//		//check all servo positions
//		for (xIndex=start; xIndex < stop ;xIndex++){
//			if (j == getBcsIoDataTable(xIndex)->PIN.currentValue){
//				//turn off if it is time to turn off
//				pinOff(xIndex);
//			}
//		}
//		// Small delay to pad the loop
//		//_delay_us(1);
//		//Nop();Nop();Nop();  Nop();Nop();Nop();  Nop();Nop();Nop();   Nop();Nop();
//	}
//	FlagBusy_IO=0;
//	for (xIndex=start; xIndex < stop ;xIndex++){
//			pinOff(xIndex);
//	}
//
////	if(print!=0xff){
////		print_I("\n\tset: ");p_fl_I(velocity[print].set);
////		print_I("\n\tServoPos: ");p_int_I(DATA.PIN[print].ServoPos);
////		print = 0xff;
////	}
//	//enableDebug();
//}

boolean pinServoOk(uint8_t pin){
	if(GetChannelMode(pin)==IS_SERVO){
		if((pin > 11)){
			if(		(b1OK==false && !powerOverRide) ||
					b1lock == true) {
				return false;
			}
		}else if(	(b0OK==false && !powerOverRide)||
					b0lock == true) {
			return false;
		}
		return true;
	}
	return false;
}

uint8_t pinOn(uint8_t pin){
	if(pinServoOk(pin) ==true){
		SetDIO(pin,ON);
		return 1;
	}
	return 0;
}

void pinOff(uint8_t pin){
	if(GetChannelMode(pin)==IS_SERVO){
		SetDIO(pin,OFF);
	}
}

//void DelayPreServo(void){
//	volatile uint32_t _dcnt = 290;
//	while (_dcnt--);
//}

void runLinearInterpolationServo(uint8_t blockStart,uint8_t blockEnd){
	uint8_t i;
	for (i=blockStart;i<blockEnd;i++){
		if(GetChannelMode(i)==IS_SERVO){
			int32_t ip = interpolate(&velocity[i],getMs());
			if(ip>(255- SERVO_BOUND)){
	#if ! defined(__AVR_ATmega324P__)
				println_I("Servo Upper out of bounds! got=");p_int_I(ip);print_I(" on time=");p_fl_I(velocity[i].setTime);
	#endif
				ip=(255- SERVO_BOUND);
			}
			if(ip<SERVO_BOUND){
	#if ! defined(__AVR_ATmega324P__)
				println_I("Servo Lower out of bounds! got=");p_int_I(ip);print_I(" on chan=");p_int_I(i);
	#endif
				ip=SERVO_BOUND;
			}
			int tmp = (int)ip;
			setDataTableCurrentValue(i,tmp);
		}
	}

}
