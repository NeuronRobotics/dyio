/**
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

#ifndef DEBUG_H_
#define DEBUG_H_
#include "Defines.h"
#include "AbstractPID.h"
typedef enum _Print_Level{
	NO_PRINT=0,
	ERROR_PRINT=1,
	WARN_PRINT=2,
	DEBUG_PRINT=3,
	INFO_PRINT=4
}Print_Level;

#define setPrintLevelNoPrint() setPrintLevel(NO_PRINT)
#define setPrintLevelErrorPrint() setPrintLevel(ERROR_PRINT)
#define setPrintLevelWarningPrint() setPrintLevel(WARN_PRINT)
#define setPrintLevelInfoPrint() setPrintLevel(INFO_PRINT)

Print_Level setPrintLevel(Print_Level l);
boolean okToprint(Print_Level l);

Print_Level getPrintLevel();
/**
 * Lets you set a custom printstream function pointer
 */
void setPrintStream(int (*sendToStreamPtr)(uint8_t * ,int));

void EnableDebugTerminal(void);
///**
// * enable printing (Defaults to enabled)
// */
//void enableDebug(void);
///**
// * disable printing (Defaults to enabled)
// */
//void disableDebug(void);
/**
 * print a given value as a 16 bit hex value
 */
#define prHEX(A,B) 		prHEX16(A,B)
#define prHEX8(A,B) 	printfDEBUG_BYTE(GetHighNib(A&0x000000ff),B);		printfDEBUG_BYTE(GetLowNib(A&0x000000ff),B)
#define prHEX16(A,B)  	printfDEBUG_BYTE(GetHighNib((A&0x0000ff00)>>8),B);	printfDEBUG_BYTE(GetLowNib((A&0x0000ff00)>>8),B); 	prHEX8(A,B);
#define prHEX24(A,B)  	printfDEBUG_BYTE(GetHighNib((A&0x00ff0000)>>16),B);	printfDEBUG_BYTE(GetLowNib((A&0x00ff0000)>>16),B);	prHEX16(A,B);
#define prHEX32(A,B)  	printfDEBUG_BYTE(GetHighNib((A&0xff000000)>>24),B);	printfDEBUG_BYTE(GetLowNib((A&0xff000000)>>24),B); 	prHEX24(A,B);

/**
 * print the ascii of a float. No new line
 */
#define p_fl(A,B) printfDEBUG_FL(A,B)

/**
 * print the ascii of an unsigned long/int. No new line
 */
#define p_int(A,B)   printfDEBUG_INT(A,B)

/**
 * print the null terminated string with no new lines
 */
#define print_nnl(A,B) printfDEBUG_NNL(A,B)

/**
 * print the null terminated string with a newline inserted at the begining of the string
 */
//#define println(A,B) printfDEBUG(__FILE__,DEBUG_PRINT);printfDEBUG(A,B)
#define println(A,B) printfDEBUG(A,B)

#define printStream(A,B,C) printByteArray(A,B,C);

/*Errors*/

/**
 * print the ascii of a float. No new line
 */
#define p_fl_E(A) printfDEBUG_FL(A,ERROR_PRINT)

/**
 * print the ascii of an unsigned long/int. No new line
 */
#define p_int_E(A)  p_int(A,ERROR_PRINT)

/**
 * print the null terminated string with no new lines
 */
#define print_E(A) printfDEBUG_NNL(A,ERROR_PRINT)

/**
 * print the null terminated string with a newline inserted at the begining of the string
 */
#define println_E(A) println(A,ERROR_PRINT);

#define printStream_E(A,B) printByteArray(A,B,ERROR_PRINT);

/*Warning*/

/**
 * print the ascii of a float. No new line
 */
#define p_fl_W(A) printfDEBUG_FL(A,WARN_PRINT)

/**
 * print the ascii of an unsigned long/int. No new line
 */
#define p_int_W(A)  p_int(A,WARN_PRINT)


/**
 * print the null terminated string with no new lines
 */
#define print_W(A) printfDEBUG_NNL(A,WARN_PRINT)

/**
 * print the null terminated string with a newline inserted at the begining of the string
 */
#define println_W(A) println(A,WARN_PRINT)

#define printStream_W(A,B) printByteArray(A,B,WARN_PRINT);

/*Info*/

/**
 * print the ascii of a float. No new line
 */
#define p_fl_I(A) printfDEBUG_FL(A,INFO_PRINT)

/**
 * print the ascii of an unsigned long/int. No new line
 */
#define p_int_I(A)  p_int(A,INFO_PRINT)


/**
 * print the null terminated string with no new lines
 */
#define print_I(A) printfDEBUG_NNL(A,INFO_PRINT)

/**
 * Clears the print termainal 
 */
#define clearPrint() sendStr("\e[1;1H\e[2J")

/**
 * print the null terminated string with a newline inserted at the begining of the string
 */
#define println_I(A) println(A,INFO_PRINT)

#define printStream_I(A,B) printByteArray(A,B,INFO_PRINT);

/**
 * sends the charrector to the serial port if it is ascii, if it is not ascii, it is converted to a number then sent
 */
void printfDEBUG_BYTE(char b,Print_Level l);

/**
 * print the null terminated string with a newline inserted at the begining of the string
 */
void printfDEBUG( char *str,Print_Level l);

/**
 * print the null terminated string with no new lines
 */
void printfDEBUG_NNL(char *str,Print_Level l);

/**
 * print the ascii of a signed long/int. No new line
 */
void printfDEBUG_INT(int32_t val,Print_Level l);

/**
 * convert a long into an ascii string and place the string into the Buffer
 */
void ultoaMINE(uint32_t Value, uint8_t* Buffer);
/**
 * print all the bytes in a byte array. The legnth of the array must be correct
 */
void printByteArray(uint8_t * stream,uint16_t len,Print_Level l);
/**
 * convert a float into an ascii string and place the string into the outbuf
 */
void ftoa(float f, char * outbuf);
/**
 * print the ascii of a float. No new line
 */
void printfDEBUG_FL(float f,Print_Level l);

/**
 * return the char of the hex value of the low 4 bits of the given byte
 */
char GetLowNib(uint8_t b);
/**
 * return the char of the hex value of the high 4 bits of the given byte
 */
char GetHighNib(uint8_t b);

#define printPIDvals(i) printPIDvalsPointer(getPidGroupDataTable(i))
void printPIDvalsPointer(AbsPID * conf);
void sendStr(const char *str) ;

//Bowler Stack Specific:
#if defined(BOWLERSTRUCTDEF_H_)
#if !defined(NO_PRINTING)
	#define printPacket(a,b) printBowlerPacketDEBUG(a,b)
#else
	#define printPacket(a,b) Nop();
#endif
	void printBowlerPacketDEBUG(BowlerPacket * packet,Print_Level l);
	void printfDEBUG_BYTE(char b,Print_Level l);
#endif

	boolean okToPrint(Print_Level l);
	void setColor(Print_Level l);
#endif /* DEBUG_H_ */
