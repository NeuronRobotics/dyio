/**
 * @file DCMotorDriver.c
 *
 *  Created on: Sep 9, 2010
 * @author Kevin Harrington
 */
#include "UserApp_avr.h"


uint8_t pwm,dir;

void setPwmDir(uint8_t pin){
	if(pin>7){
		dir=pin;
		pwm=dir-4;
	}else{
		pwm=pin;
		dir=pwm+4;
	}
}

boolean InitDCMotor(uint8_t pin){
	if (!(	pinHasFunction(pin,IS_DC_MOTOR_DIR) ||
			pinHasFunction(pin,IS_DC_MOTOR_VEL))){
		return false; 
	}
	setPwmDir(pin);

	configPinMode(pwm,IS_DC_MOTOR_VEL,OUTPUT,OFF);
	configPinMode(dir,IS_DC_MOTOR_DIR,OUTPUT,OFF);

	SetDCMotor(pwm,128);

	return true; 
}

void ClearDCMotor(uint8_t pin){
	if (!(	pinHasFunction(pin,IS_DC_MOTOR_DIR) ||
			pinHasFunction(pin,IS_DC_MOTOR_VEL))){
		return;
	}
	setPwmDir(pin);
	if((GetChannelMode(pwm)==IS_DC_MOTOR_VEL)&&(GetChannelMode(dir)==IS_DC_MOTOR_DIR)){
		ClearPWM(pwm);
		//DATA.PIN[pwm].State=IS_DI;
		//DATA.PIN[dir].State=IS_DI;
		configPinMode(pwm,IS_DI,INPUT,ON);
		configPinMode(dir,IS_DI,INPUT,ON);
	}


}
uint8_t GetDCMotor(uint8_t pin){
	if (!(	pinHasFunction(pin,IS_DC_MOTOR_DIR) ||
			pinHasFunction(pin,IS_DC_MOTOR_VEL))){
		return 0;
	}
	setPwmDir(pin);
	return getBcsIoDataTable(pin)->PIN.currentValue;
}
void SetDCMotor(uint8_t pin,uint8_t vel){
	if (!(	pinHasFunction(pin,IS_DC_MOTOR_DIR) ||
			pinHasFunction(pin,IS_DC_MOTOR_VEL))){
		return;
	}
	setPwmDir(pin);

	int tmp = vel-128;

	setDataTableCurrentValue(pwm,vel);

	if(tmp>0){
		SetDIO(dir,0);
		int val = tmp<<1;
		if (val>255)
			val=255;
		if(val<0)
			val=0;
		SetPWM(pwm,val);
	}else{
		SetDIO(dir,1);
		int val =(tmp*-1)<<1;
		if (val>255)
			val=255;
		if(val<0)
			val=0;
		SetPWM(pwm,val);
	}
}
