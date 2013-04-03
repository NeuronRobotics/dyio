/**
 * @file DCMotorDriver.c
 *
 *  Created on: Sep 9, 2010
 * @author Kevin Harrington
 */
#include "UserApp_avr.h"


BYTE pwm,dir;

void setPwmDir(BYTE pin){
	if(pin>7){
		dir=pin;
		pwm=dir-4;
	}else{
		pwm=pin;
		dir=pwm+4;
	}
}

BOOL InitDCMotor(BYTE pin){
	if (!(	pinHasFunction(pin,IS_DC_MOTOR_DIR) ||
			pinHasFunction(pin,IS_DC_MOTOR_VEL))){
		return FALSE;
	}
	setPwmDir(pin);

	configPinMode(pwm,IS_DC_MOTOR_VEL,OUTPUT,OFF);
	configPinMode(dir,IS_DC_MOTOR_DIR,OUTPUT,OFF);

	SetDCMotor(pwm,128);

	return TRUE;
}

void ClearDCMotor(BYTE pin){
	if (!(	pinHasFunction(pin,IS_DC_MOTOR_DIR) ||
			pinHasFunction(pin,IS_DC_MOTOR_VEL))){
		return;
	}
	setPwmDir(pin);
	if((GetChannelMode(pwm)==IS_DC_MOTOR_VEL)&&(GetChannelMode(dir)==IS_DC_MOTOR_DIR)){
		ClearPWM(pwm);
		//DATA.PIN[pwm].State=IS_DI;
		//DATA.PIN[dir].State=IS_DI;
		EEWriteMode(pwm,IS_DI);
		EEWriteMode(dir,IS_DI);
	}


}
BYTE GetDCMotor(BYTE pin){
	if (!(	pinHasFunction(pin,IS_DC_MOTOR_DIR) ||
			pinHasFunction(pin,IS_DC_MOTOR_VEL))){
		return 0;
	}
	setPwmDir(pin);
	return getBcsIoDataTable()[pin].PIN.currentValue;
}
void SetDCMotor(BYTE pin,BYTE vel){
	if (!(	pinHasFunction(pin,IS_DC_MOTOR_DIR) ||
			pinHasFunction(pin,IS_DC_MOTOR_VEL))){
		return;
	}
	setPwmDir(pin);

	int tmp = vel-128;

	getBcsIoDataTable()[pwm].PIN.currentValue = vel;

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
