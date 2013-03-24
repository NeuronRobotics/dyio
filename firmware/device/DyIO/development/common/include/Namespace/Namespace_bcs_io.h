/*
 * Namespace_bcs_io.h
 *
 *  Created on: Mar 21, 2013
 *      Author: hephaestus
 */

#ifndef NAMESPACE_BCS_IO_H_
#define NAMESPACE_BCS_IO_H_

//bcs.io
#define GCHM				0x6D686367// Get channel mode
#define GACM				0x6D636167// Get all channel mode
#define SCHV				0x76686373// Set channel value
#define SACV				0x76636173// Set all channel values
#define GCHV				0x76686367// Get channel value
#define GACV				0x76636167// Get all channel values
#define CCHN				0x6E686363// Configure channel
#define ASYN				0x6e797361 // 'asyn'  Set/Get asynchronous mode
#define GCHC				0x63686367 // 'gchc'  Get Channel Count
#define GCML				0x6c6d6367 // 'gcml'  Get channel Mode List

int getNumberOfIOChannels();// Returns the number of IO channels availible

typedef union __attribute__((__packed__)) _FUNCTION_MAP
	{
		struct{
			unsigned HAS_ANALOG_IN		:1;
			unsigned HAS_ANALOG_PUSHED	:1;
			unsigned HAS_PWM			:1;
			unsigned HAS_UART			:1;
			unsigned HAS_SPI			:1;
			unsigned HAS_COUNTER_INPUT	:1;
			unsigned HAS_COUNTER_OUTPUT	:1;
			unsigned HAS_DC_MOTOR		:1;
		};
		BYTE b;
	} FUNCTION_MAP;
	typedef struct __attribute__((__packed__)) _PIN_MAP
	{
		BYTE ServoPos;
#if !defined(__AVR_ATmega324P__)
		BYTE State;
#endif
	} PIN_MAP;

typedef struct __attribute__((__packed__)) _DATA
{
	//STORAGE self;
	PIN_MAP PIN;
	FUNCTION_MAP FUNCTION;
} DATA_STRUCT;

/**
 * Set Channel Values
 * This function takes a
 * @param pin pin index
 * @param numValues a number of values to be delt with
 * @param data an array of data values
 * @param ms the time for the transition to take
 *
 */
BOOL SetChanelValueHW(BYTE pin,BYTE * numValues,INT32 * data, float ms);

/**
 * Set Channel Values
 * This function takes a pin index, a number of values to be delt with, and an array of data values
 * Data is stored into numValues and data
 */
BOOL GetChanelValueHW(BYTE pin,BYTE * numValues,INT32 * data);


#endif /* NAMESPACE_BCS_IO_H_ */
