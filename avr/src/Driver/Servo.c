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

static boolean powerOverRide = 0xff;
static INTERPOLATE_DATA velocity[NUM_PINS];
static boolean servoEngineStarted =false;
static uint8_t bOK[2]={false,false};
static uint8_t blockServo[2]={true,true};




boolean getPowerOverRide(){
	if(powerOverRide == 0xff)
		setPowerOverride(EEReadData(189));
	return powerOverRide;
}


void InitServo(uint8_t PIN){
	//println_I("Starting servo");
	ClearPinState(PIN);
	SetPinTris(PIN,OUTPUT);
	//DATA.PIN[PIN].State=IS_SERVO;
	SetServoPos(PIN,EEReadValue(PIN),0);
	if( servoEngineStarted != true){
		servoEngineStarted =true;
		startServoLoops();
	}

}

void setPowerOverride(boolean set){
	//println_W("powerOverRide: ");p_int_W(set);
	powerOverRide = set?true:false;
}


void SetPowerState(int bank,boolean railOk,boolean regulated){
	bOK[bank]=false;
	if (regulated == 1){
		if(bank==0){
			Bank0Green();
		}else{
			Bank1Green();
		}
	}else {
		if(railOk==2 ||  railOk==1){
			bOK[bank]=true;
		}
		if(railOk ==1 ||railOk ==3  ){
			if(bank==0){
				Bank0Red();
			}else{
				Bank1Red();
			}
		}else{
			if(bank==0){
				Bank0Off();
			}else{
				Bank1Off();
			}
		}
		if(railOk == 3||railOk == 0 ){
			blockServo[bank]=true;
		}
	}
}

void SetPowerState0(boolean railOk,boolean regulated){
	SetPowerState(0,railOk,regulated);
}
void SetPowerState1(boolean railOk,boolean regulated){
	SetPowerState(1,railOk,regulated);
}
boolean print = 0xff;
void SetServoPos(uint8_t pin,uint8_t val,float time){
	if(time<30)
		time=0;
	if(val == velocity[pin].set){
		return;
	}
//
//	println_W("Servo ");p_int_W(pin);
//	print_W(" time= ");p_fl_W(time);
//	print_W(" to val= ");p_int_W(val);
//	print_W(" val was= ");p_fl_W(velocity[pin].set);

	if(time<30 || isnan(velocity[pin].set)){
		velocity[pin].setTime=0;
		velocity[pin].start = (float)val;
	}else{
		// Set the start value to the pervious value
		velocity[pin].setTime=time;
		velocity[pin].start=velocity[pin].set;
	}
	velocity[pin].set=(float)val;
	velocity[pin].startTime=getMs();

	getInterpolatedPin( pin);

	if(pin<12){
		blockServo[0]=false;
	}else{
		blockServo[1]=false;
	}
	if(GetChannelMode(pin)!=IS_SERVO)
		return;
	print = pin;

}
uint8_t GetServoPos(uint8_t pin){
	return getInterpolatedPin( pin);
}

boolean pinServoOk(uint8_t pin){
	int bank = (pin > 11)?1:0;
	if(GetChannelMode(pin)==IS_SERVO){
		// If the power override is cleared, then the pin should be on no matter what else
		if(getPowerOverRide()==false) {
			return true;
		}
		// If we are are in the lock out mode, no servos on this bank
		if(	blockServo[bank] == true) {
			return false;
		}
		// If the voltage is invalid, no servos on this bank
		if(	(bOK[bank]==false ) ) {
			return false;
		}

		// All lock outs have passed, pin is ok to be a servo output
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
uint8_t getInterpolatedPin(uint8_t pin){
	if(GetChannelMode(pin)!=IS_SERVO){
		return 0;
	}
	//char cSREG;
	//cSREG = SREG;
	/* store SREG value */
	/*
	disable interrupts during timed sequence */
	//StartCritical();
	float ip = interpolate(&velocity[pin],getMs());
	//SREG = cSREG;
	boolean error = false;
	if(ip>(255- SERVO_BOUND)){
		println_W("Upper=");
		error = true;
	}
	if(ip<SERVO_BOUND){
		println_W("Lower=");
		error = true;
	}
	int dataTableSet = (getDataTableCurrentValue(pin)&0x000000ff);
	int interpolatorSet = ((int32_t)velocity[pin].set);
	if(dataTableSet!=interpolatorSet){
//		println_W("Setpoint=");
//				error = true;
		SetServoPos(pin,dataTableSet,(float)((getDataTableCurrentValue(pin)>>16)&0x0000ffff));
	}
	if(error){
//		p_fl_W(ip);print_W(" on chan=");p_int_W(pin);print_W(" target=");p_int_W(interpolatorSet);
//		print_W(" Data Table=");p_int_W(dataTableSet);
//		println_W("set=      \t");p_fl_W(velocity[pin].set);
//		println_W("start=    \t");p_fl_W(velocity[pin].start);
//		println_W("setTime=  \t");p_fl_W(velocity[pin].setTime);
//		println_W("startTime=\t");p_fl_W(velocity[pin].startTime);
		ip=velocity[pin].set;
		SetServoPos(pin,dataTableSet,(float)((getDataTableCurrentValue(pin)>>16)&0x0000ffff));
	}
	int tmp = (int)ip;

	return tmp;
}

//void runLinearInterpolationServo(uint8_t blockStart,uint8_t blockEnd){
//	uint8_t i;
//	for (i=blockStart;i<blockEnd;i++){
//		if(GetChannelMode(i)==IS_SERVO){
//			int32_t ip = interpolate(&velocity[i],getMs());
//			if(ip>(255- SERVO_BOUND)){
//	#if ! defined(__AVR_ATmega324P__)
//				println_I("Servo Upper out of bounds! got=");p_int_I(ip);print_I(" on time=");p_fl_I(velocity[i].setTime);
//	#endif
//				ip=(255- SERVO_BOUND);
//			}
//			if(ip<SERVO_BOUND){
//	#if ! defined(__AVR_ATmega324P__)
//				println_I("Servo Lower out of bounds! got=");p_int_I(ip);print_I(" on chan=");p_int_I(i);
//	#endif
//				ip=SERVO_BOUND;
//			}
//			int tmp = (int)ip;
//			setDataTableCurrentValue(i,tmp);
//		}
//	}
//
//}
