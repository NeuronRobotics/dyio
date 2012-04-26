/*
 * Switches.c
 *
 *  Created on: Feb 11, 2010
 *      Author: hephaestus
 */

#include "UserApp.h"

static BYTE switched;
static BYTE bankState[2];
static float lastVolt=0;
static float volt;


void CheckSwitches(void){
	switched=0;
	volt = GetRawVoltage();
	BOOL up = FALSE;

	//println_I("Voltage on raw:");
	//p_fl_I(volt);

	//println_I("Voltage on bank0:");
	//p_fl_I(GetRail0Voltage());

	//println_I("Voltage on bank1:");
	//p_fl_I(GetRail1Voltage());

	BYTE reg = isRegulated_0();
	if (bankState[0] != reg ){
		bankState[0]=reg;
		up=TRUE;
	}


	reg = isRegulated_1();
	if (bankState[1] != reg){
		bankState[1] = reg;
		up=TRUE;
	}

	//if(! (bankState[1] == 1 && bankState[0] ==1 ) ){
		if ((lastVolt>RawVoltageMin) && (volt<RawVoltageMin)){
			up=TRUE;
			lastVolt = volt;
		}
		if ((lastVolt<RawVoltageMin) && (volt>RawVoltageMin)){
			up=TRUE;
			lastVolt = volt;
		}
	//}
	if(up){
		print_I("\nPushing upstream Power Packet bank 0: ");p_sl_I(bankState[0]);print_I(" bank 1: ");p_ul_I(bankState[1]);print_I(" \nPower Code 0: ");p_ul_I(GetRawVoltageCode(0));print_I(" \nPower Code 1 : ");p_ul_I(GetRawVoltageCode(1));print_I(" \nRaw: ");p_fl_I(GetRawVoltage());
		UpstreamPushPowerChange();
	}
}

BYTE IsRegulated(float voltage){
	float raw = GetRawVoltage();//adding the voltage drop across the diaode
	if((voltage < raw+.01)&&(voltage > raw-.01))
		return FALSE;
	if ((voltage<(RawVoltageMin))&&(voltage>(4.4))){//USB spec is 5.25v to 4.4v.
		return TRUE;
	}
	return FALSE;
}
