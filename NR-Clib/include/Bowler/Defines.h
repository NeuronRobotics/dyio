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
#ifndef DEFINES_H_
#define DEFINES_H_

#include <stddef.h>
#include <stdint.h>
#define BOWLER_VERSION			3
#define BowlerHeaderSize		11
#define CRCIndex				10
#define DataSizeIndex			9
#define SessionIDIndex			8
#define ResponseFlagIndex		8
#define MethodIndex				7
#define RPCDataStart 			15
#define RPCCodeStart 			BowlerHeaderSize

#define PRINT_BAUD 			115200
/**
AVR Baud = 115200 	Pic Baud = 114942	Percent = 0.22349936143040042 AVR Baud = 9 	Pic Baud = 173
AVR Baud = 115200 	Pic Baud = 115606	Percent = -0.35324341682722765 AVR Baud = 9 	Pic Baud = 172
AVR Baud = 128000 	Pic Baud = 127388	Percent = 0.4777070063694282 AVR Baud = 8 	Pic Baud = 156
AVR Baud = 128000 	Pic Baud = 128205	Percent = -0.1602564102564088 AVR Baud = 8 	Pic Baud = 155
AVR Baud = 144000 	Pic Baud = 143884	Percent = 0.07993605115906476 AVR Baud = 7 	Pic Baud = 138
AVR Baud = 164571 	Pic Baud = 163934	Percent = 0.387067395264128 AVR Baud = 6 	Pic Baud = 121
AVR Baud = 164571 	Pic Baud = 165289	Percent = -0.4361799816345233 AVR Baud = 6 	Pic Baud = 120
AVR Baud = 192000 	Pic Baud = 192307	Percent = -0.1602564102564126 AVR Baud = 5 	Pic Baud = 103
AVR Baud = 230400 	Pic Baud = 229885	Percent = 0.22349936143040042 AVR Baud = 4 	Pic Baud = 86
AVR Baud = 384000 	Pic Baud = 384615	Percent = -0.1602564102564126 AVR Baud = 2 	Pic Baud = 51
AVR Baud = 576000 	Pic Baud = 571428	Percent = 0.793650793650785 AVR Baud = 1 	Pic Baud = 34
 */

//#define INTERNAL_BAUD 				384000 // 0.160% difference
//#define INTERNAL_BAUD 				144000 // 0.079% difference
//#define INTERNAL_BAUD 					192000 // 0.160% difference

#define INTERNAL_BAUD_AVR 2
#define INTERNAL_BAUD_PIC 51

#define BOWLER_PacketSize		(BowlerHeaderSize+255)
#define ASSERTED				0
#define NOT_ASSERTED			1

//Method Codes
#define BOWLER_STATUS 					0x00
#define BOWLER_GET					0x10
#define BOWLER_POST  					0x20
#define BOWLER_CRIT 	 				0x30
#define BOWLER_ASYN 	 				0x40

// 1 uint8_t
#define BOWLER_I08      8 // 8 bit integer
#define BOWLER_BOOL    43// a boolean value
//2 uint8_t
#define BOWLER_I16      16//16 bit integer
//4 uint8_t
#define BOWLER_I32      32//32 bit integer
#define BOWLER_FIXED100    41// float
#define BOWLER_FIXED1K    42// float
//streams
#define BOWLER_STR      37// first uint8_t  is number of values, next is uint8_t  values
#define BOWLER_I32STR   38// first uint8_t  is number of values, next is 32 bit values
#define BOWLER_FIXED1K_STR   44// first uint8_t  is number of values, next is floats
// ASCII
#define BOWLER_ASCII    39// ASCII string, null terminated

#define true 1
#define false 0
typedef uint8_t			boolean;
//#if !defined(__GENERIC_TYPE_DEFS_H_)
////#define B_B_true 1
////#define B_B_false 0
////	typedef unsigned char			BOOL;
//        typedef enum _boolean { B_B_false = 0, B_B_true } BOOL;    /* Undefined size */
//	typedef unsigned char			uint8_t ;
//	typedef signed int          	INT;
//	typedef signed char         	INT8;
//	typedef signed short int    	INT16;
//	typedef signed long int     	INT32;
//	typedef signed long long    	INT64;
//
//	typedef unsigned int        	UINT;
//	typedef unsigned char       	UINT8;
//	typedef unsigned short int  	UINT16;
//	typedef unsigned long int   	UINT32;
//	typedef unsigned long long  	UINT64;
//#endif

typedef union _INT16_UNION {
    int16_t Val;
    uint8_t v[2];

    struct {
        uint8_t LB;
        uint8_t SB;
    } byte;
} INT16_UNION;

typedef union _UINT16_UNION {
    uint16_t Val;
    uint8_t v[2];

    struct {
        uint8_t LB;
        uint8_t SB;
    } byte;
} UINT16_UNION;

typedef union _INT32_UNION {
    int32_t Val;
    uint8_t v[4];

    struct {
        uint8_t LB;
        uint8_t SB;
        uint8_t TB;
        uint8_t FB;
    } byte;
    float f;

} INT32_UNION;

/*
typedef union _UINT64_UNION_DOUBLE
{
    uint64_t Val;
    uint8_t  v[8];
    struct
    {
        UINT32_UNION LI;
        UINT32_UNION SI;

    } uint;
    double d;

} UINT64_UNION_DOUBLE;*/

typedef union _UINT32_UNION {
    uint32_t Val;
    uint8_t v[4];

    struct {
        uint8_t LB;
        uint8_t SB;
        uint8_t TB;
        uint8_t FB;
    } byte;

} UINT32_UNION;
#if !defined(NULL)
#define NULL 0
#endif

#endif /* DEFINES_H_ */
