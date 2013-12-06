/*
 * LED.c
 *
 *  Created on: Nov 22, 2009
 *      Author: hephaestus
 */
#include "arch/pic32/BowlerConfig.h"
#include "Bowler/Bowler.h"

void InitLEDS(void){
	startLED();
}

void SetGreen(WORD Duty){
	SET_GREEN(Duty);
}

void SetRed(WORD Duty){
	SET_RED(Duty);
}

void SetBlue(WORD Duty){
	SET_BLUE(Duty);
}

void SetColor(WORD r,WORD g,WORD b){
	SetGreen(g);
	SetRed(r);
	SetBlue(b);
}
