/*
 * Switches.c
 *
 *  Created on: Feb 11, 2010
 *      Author: hephaestus
 */

#include "UserApp.h"

uint8_t switched;
uint8_t bankState[2];
float lastVolt=0;
float volt;


void CheckSwitches(void){

	Print_Level l = getPrintLevel();
	setPrintLevelInfoPrint();
	switched=0;
	volt = GetRawVoltage();
	boolean up = false; 

	uint8_t reg = isRegulated_0();
	if (bankState[0] != reg ){
		bankState[0]=reg;
		up=true; 
	}


	reg = isRegulated_1();
	if (bankState[1] != reg){
		bankState[1] = reg;
		up=true; 
	}

	if ((lastVolt>RawVoltageMin) && (volt<RawVoltageMin)){
		up=true; 
		lastVolt = volt;
	}
	if ((lastVolt<RawVoltageMin) && (volt>RawVoltageMin)){
		up=true; 
		lastVolt = volt;
	}

	if(up){
//		println_I("\nVoltage on raw:   \t");
//		p_fl_I(volt);
//
//		println_I("Voltage on bank0: \t");
//		p_fl_I(GetRail0Voltage());
//
//		println_I("Voltage on bank1:\t");
//		p_fl_I(GetRail1Voltage());
//		println_I("Pushing upstream Power Packet bank 0: ");p_int_I(bankState[0]);print_I(" bank 1: ");p_int_I(bankState[1]);
//		println_I("Power Code 0: ");p_int_I(GetRawVoltageCode(0));
//		println_I("Power Code 1 : ");p_int_I(GetRawVoltageCode(1));
//		println_I("Raw: ");p_fl_I(GetRawVoltage());
		UpstreamPushPowerChange();
//                println_I("Pusing change");
	}
	setPrintLevel(l);
}

uint8_t IsRegulated(float voltage){
	float raw = GetRawVoltage()-130;//adding the voltage drop across the diaode
	if((voltage < raw+10)&&(voltage > raw-10))
		return false; 
	if ((voltage<(RawVoltageMin))&&(voltage>(FiveVoltADC))){//USB spec is 5.25v to 4.4v.
		return true; 
	}
	return false; 
}
