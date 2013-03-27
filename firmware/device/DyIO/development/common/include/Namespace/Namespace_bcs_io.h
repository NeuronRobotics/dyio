/*
 * Namespace_bcs_io.h
 *
 *  Created on: Mar 21, 2013
 *      Author: hephaestus
 */

#ifndef NAMESPACE_BCS_IO_H_
#define NAMESPACE_BCS_IO_H_

/*
 * This is the case statements for using the DyIO channel modes in a switch statement
case IS_DI:
	break;
case IS_DO:
	break;
case IS_ANALOG_IN:
	break;
case IS_ANALOG_OUT:
	break;
case IS_PWM:
	break;
case IS_SERVO:
	break;
case IS_UART_TX:
	break;
case IS_UART_RX:
	break;
case IS_SPI_MOSI:
	break;
case IS_SPI_MISO:
	break;
case IS_SPI_SCK	:
	break;
case IS_COUNTER_INPUT_INT:
	break;
case IS_COUNTER_INPUT_DIR:
	break;
case IS_COUNTER_INPUT_HOME:
	break;
case IS_COUNTER_OUTPUT_INT:
	break;
case IS_COUNTER_OUTPUT_DIR:
	break;
case IS_COUNTER_OUTPUT_HOME:
	break;
case IS_DC_MOTOR_VEL:
	break;
case IS_DC_MOTOR_DIR:
	break;
case IS_PPM_IN:
	break;
 */

#define NO_CHANGE	 	 		0x00
#define HIGH_IMPEDANCE 	 		0x01
#define IS_DI	 		 		0x02
#define IS_DO		 			0x03
#define IS_ANALOG_IN 			0x04
#define IS_ANALOG_OUT			0x05
#define IS_PWM	 				0x06
#define IS_SERVO 				0x07
#define IS_UART_TX		 		0x08
#define IS_UART_RX	 			0x09
#define IS_SPI_MOSI				0x0A
#define IS_SPI_MISO				0x0B
#define IS_SPI_SCK	 			0x0C
//#define IS_SPI_SS	 			0x0D
#define IS_COUNTER_INPUT_INT	0x0E
#define IS_COUNTER_INPUT_DIR	0x0F
#define IS_COUNTER_INPUT_HOME	0x10
#define IS_COUNTER_OUTPUT_INT	0x11
#define IS_COUNTER_OUTPUT_DIR	0x12
#define IS_COUNTER_OUTPUT_HOME	0x13
#define IS_DC_MOTOR_VEL			0x14
#define IS_DC_MOTOR_DIR			0x15
#define IS_PPM_IN				0x16

#define IO_MODE_MAX				(IS_PPM_IN+1)

#define isStremChannelMode(A) ( (A==IS_UART_TX)||\
								(A==IS_UART_RX)||\
								(A==IS_SPI_MOSI)||\
								(A==IS_SPI_MISO)||\
								(A==IS_SPI_SCK)||\
								(A==IS_PPM_IN))
#define isSingleByteMode(A)  ( 	(A==IS_DO)||\
								(A==IS_DI)||\
								(A==IS_PWM)||\
								(A==IS_DC_MOTOR_VEL	)||\
								(A==IS_DC_MOTOR_DIR	)||\
								(A==IS_SERVO)\
							)
#define isTwoByteMode(A)  ( 	(A==IS_ANALOG_IN)||\
								(A==IS_ANALOG_OUT)\
							)



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
typedef union __attribute__((__packed__)) _FUNCTION_MAP
	{
		struct{
			unsigned HAS_ANALOG_IN			:1;
			unsigned HAS_PWM				:1;
			unsigned HAS_UART_T				:1;
			unsigned HAS_UART_R				:1;
			unsigned HAS_SPI_C				:1;
			unsigned HAS_SPI_O				:1;
			unsigned HAS_SPI_I				:1;
			unsigned HAS_COUNTER_INPUT_D	:1;
			unsigned HAS_COUNTER_OUTPUT_D	:1;
			unsigned HAS_COUNTER_INPUT_I	:1;
			unsigned HAS_COUNTER_OUTPUT_I	:1;
			unsigned HAS_COUNTER_INPUT_H	:1;
			unsigned HAS_COUNTER_OUTPUT_H	:1;
			unsigned HAS_DC_MOTOR			:1;
			unsigned HAS_PPM				:1;
			unsigned unused					:16;
		};
		UINT32 b;
	} FUNCTION_MAP;
	typedef struct __attribute__((__packed__)) _PIN_MAP
	{
		INT32 currentValue;
		INT32 currentChannelMode;
		BYTE  currentConfiguration;
		//Used to detect any hardware state change and synchronize
		INT32 previousValue;
		INT32 previousConfiguration;
		BYTE  previousChannelMode;
	} PIN_MAP;

typedef struct __attribute__((__packed__)) _DATA
{
	//STORAGE self;
	PIN_MAP PIN;
	FUNCTION_MAP FUNCTION;
	AdvancedAsyncData asyncData;
} DATA_STRUCT;



/**
 * This returns the number of IO channels availible
 */
int GetNumberOfIOChannels();

/**
 * Gets the channel mode
 */
BYTE GetChannelMode(BYTE chan);


/**
 * Initialize Bcs.IO namespace
 * Pass in the data table and the call back functions to start the namespace
 *
 */
void InitilizeBcsIo(int numPins,
					DATA_STRUCT * dataPtrLocal,
					BOOL (*setChanelValueHWPtrLocal)(BYTE,BYTE,INT32 *,float),
					BOOL (*getChanelValueHWPtrLocal)(BYTE,BYTE*,INT32 *),
					BOOL (*setAllChanelValueHWPtrLocal)(INT32 *,float),
					BOOL (*getAllChanelValueHWPtrLocal)(INT32 *),
					BOOL (*configChannelHWPtrLocal)(BYTE,BYTE,INT32 *)
);

//These are the Hardware interface functions that need to be declared and passed in for Initilaize

/**
 * Set Channel Values
 * This function takes a
 * @param pin pin index
 * @param numValues a number of values to be delt with
 * @param data an array of data values
 * @param ms the time for the transition to take
 *
 */
BOOL SetChanelValueHW(BYTE pin,BYTE numValues,INT32 * data, float ms);

/**
 * Set Channel Values
 * This function takes a pin index, a number of values to be delt with, and an array of data values
 * Data is stored into numValues and data
 */
BOOL GetChanelValueHW(BYTE pin,BYTE * numValues,INT32 * data);
/**
 * Set Channel Values
 * This function takes a
 * @param data an array of data values
 * @param ms the time for the transition to take
 *
 */
BOOL SetAllChanelValueHW(INT32 * data, float ms);

/**
 * Set Channel Values
 * This function takes a pin index, a number of values to be delt with, and an array of data values
 * Data is stored into numValues and data
 */
BOOL GetAllChanelValueHW(INT32 * data);

/**
 * Configure Channel
 * @param pin the index of the channel to configure
 * @param numValues The number of values passed in to deal with
 * @param data the array of values to use in the configuration step
 */

BOOL ConfigureChannelHW(BYTE pin,BYTE numValues,INT32 * data);


#endif /* NAMESPACE_BCS_IO_H_ */
