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


BOOL powerOverRide = FALSE;

INTERPOLATE_DATA velocity[NUM_PINS];
void runLinearInterpolationServo(BYTE blockStart,BYTE blockEnd);


BYTE pinOn(BYTE pin);
void pinOff(BYTE pin);

void InitServo(BYTE PIN){
	//println_I("Starting servo");
	ClearPinState(PIN);
	SetPinTris(PIN,OUTPUT);
	//DATA.PIN[PIN].State=IS_SERVO;
}

void setPowerOverride(BOOL set){
	powerOverRide = set;
}

BYTE b0OK=FALSE;
BYTE b1OK=FALSE;
BYTE b0lock=TRUE;
BYTE b1lock=TRUE;

void SetPowerState0(BOOL railOk,BOOL regulated){
	b0OK=FALSE;
	if (regulated == 1){
		Bank0Green();
	}else {
		if(railOk==2 ||  railOk==1){
			b0OK=TRUE;
		}
		if(railOk ==1 ||railOk ==3  ){
			Bank0Red();
		}else{
			Bank0Off();
		}
		if(railOk == 3||railOk == 0 ){
			b0lock=TRUE;
		}
	}
}
void SetPowerState1(BOOL railOk,BOOL regulated){
	b1OK=FALSE;
	if (regulated==1){
		Bank1Green();
	}else {
		if(railOk ==1 ||railOk ==3  ){
			Bank1Red();
		}else{
			Bank1Off();
		}
		if(railOk==2 ||  railOk==1){
			b1OK=TRUE;
		}
		if(railOk == 3 ||railOk == 0 ){
			b1lock=TRUE;
		}
	}
}
BOOL print = 0xff;
void SetServoPos(BYTE pin,BYTE val,float time){
	if(time<30)
		time=0;
	velocity[pin].setTime=time;
	velocity[pin].set=(float)val;
	velocity[pin].start=(float)getBcsIoDataTable(pin)->PIN.asyncDataCurrentVal;
	velocity[pin].startTime=getMs();
	if (val==getBcsIoDataTable(pin)->PIN.asyncDataCurrentVal){
		velocity[pin].setTime=0;
	}
	if(pin<12){
		b0lock=FALSE;
	}else{
		b1lock=FALSE;
	}
	if(GetChannelMode(pin)!=IS_SERVO)
		return;
	print = pin;
}
BYTE GetServoPos(BYTE pin){
	return getBcsIoDataTable(pin)->PIN.asyncDataCurrentVal;
}

void RunServo(BYTE block){

	//disableDebug();
	UINT16 j;
	BYTE xIndex;
	//return;
	BYTE start=block*BLOCK_SIZE;
	BYTE stop=(block*BLOCK_SIZE)+BLOCK_SIZE;

	runLinearInterpolationServo(start,stop);
	FlagBusy_IO=1;
	//Short delay to allow any stray transactions to finish
	_delay_us(800);
	BYTE num=0;
	for (j=start;j<stop;j++){
		num+=pinOn(j);
	}
	//run minimal .75 ms pulse
	DelayPreServo();
	//loop 255 times and turn off all servos as their set position is equal to the loop counter
	for (j=0;j<256;j++){
		//check all servo positions
		for (xIndex=start; xIndex < stop ;xIndex++){
			if (j == getBcsIoDataTable(xIndex)->PIN.asyncDataCurrentVal){
				//turn off if it is time to turn off
				pinOff(xIndex);
			}
		}
		// Small delay to pad the loop
		//_delay_us(1);
		//Nop();Nop();Nop();  Nop();Nop();Nop();  Nop();Nop();Nop();   Nop();Nop();
	}
	FlagBusy_IO=0;
	for (xIndex=start; xIndex < stop ;xIndex++){
			pinOff(xIndex);
	}

//	if(print!=0xff){
//		print_I("\n\tset: ");p_fl_I(velocity[print].set);
//		print_I("\n\tServoPos: ");p_int_I(DATA.PIN[print].ServoPos);
//		print = 0xff;
//	}
	//enableDebug();
}

BYTE pinOn(BYTE pin){
	if(GetChannelMode(pin)==IS_SERVO){
		if((pin > 11)){
			if(		(b1OK==FALSE && !powerOverRide) ||
					b1lock == TRUE){
				return 0;
			}
		}else if(	(b0OK==FALSE && !powerOverRide)||
					b0lock == TRUE){
			return 0;
		}

		SetDIO(pin,ON);
		return 1;
	}
	return 0;
}

void pinOff(BYTE pin){
	if(GetChannelMode(pin)==IS_SERVO){
		SetDIO(pin,OFF);
	}
}

void DelayPreServo(void){
	volatile UINT32 _dcnt = 290;
	while (_dcnt--);
}

void runLinearInterpolationServo(BYTE blockStart,BYTE blockEnd){
	BYTE i;
	for (i=blockStart;i<blockEnd;i++){
		if(GetChannelMode(i)==IS_SERVO){
			INT32 ip = interpolate(&velocity[i],getMs());
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
			getBcsIoDataTable(i)->PIN.asyncDataCurrentVal=  tmp;
		}
	}

}
