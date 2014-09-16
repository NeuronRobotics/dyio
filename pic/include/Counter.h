/*
 * Counter.h
 *
 *  Created on: Feb 7, 2010
 *      Author: hephaestus
 */

#ifndef COUNTER_H_
#define COUNTER_H_

#define CHAN0P0			_RE7
#define CHAN0P1			_RD8
#define CHAN1P0			_RE6
#define CHAN1P1			_RD9
#define CHAN2P0			_RE5
#define CHAN2P1			_RD10
#define CHAN3P0			_RE4
#define CHAN3P1			_RD11

#define CHAN0P0_tris	_TRISE7
#define CHAN0P1_tris	_TRISD8
#define CHAN1P0_tris	_TRISE6
#define CHAN1P1_tris	_TRISD9
#define CHAN2P0_tris	_TRISE5
#define CHAN2P1_tris	_TRISD10
#define CHAN3P0_tris	_TRISE4
#define CHAN3P1_tris	_TRISD11
#define OFF 			0
#define ON 				1
#define BTReset 			0
#define BTNotReset 			1

typedef struct __attribute__((__packed__)) _COUNTER
{
	LONG SETPOINT;
	LONG CURRENT;
	uint8_t STEP_INDEX;
	uint8_t TimeOffset;
	uint8_t TimeStep;
	boolean OutputEnabled;
	boolean Homed;
	INTERPOLATE_DATA interpolate;
} COUNTER;

typedef struct __attribute__((__packed__)) _COUNTER_PINS
{

		uint8_t INT;
		uint8_t DIR;
		uint8_t HOME;
} COUNTER_PINS;

void runCounterGroup(uint8_t group);
void setPinsByGroup(uint8_t chan,uint8_t pin1,uint8_t pin2);
#define NUM_COUNTER_GROUPS 4

void InitCounterPins(void);
void ClearCounter(uint8_t pin);
boolean StartCounterInput(uint8_t pin);
void initCounterAsync(uint8_t chan,int32_t val);
boolean StartCounterOutput(uint8_t pin);
void RunCounter(void);
boolean SetCounterInput(uint8_t chan,LONG val);
LONG GetCounterByGroup(uint8_t chan);
LONG GetCounterByChannel(uint8_t chan);
boolean SetCounterOutput(uint8_t chan,LONG val, uint32_t ms);
LONG GetCounterOutput(uint8_t chan);
void SetupCounterTimer(void);

uint8_t channelToCounterGroup(uint8_t pin);
uint8_t getCounterIntChannnel(uint8_t group);
uint8_t getCounterDirChannnel(uint8_t group);
uint8_t getCounterHomeChannnel(uint8_t group);

void findCounterPins(uint8_t * pins,uint8_t pin);

#endif /* COUNTER_H_ */
