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

#define INTERNAL_BAUD 				230400
//#define INTERNAL_BAUD 				115200

#define BOWLER_PacketSize		(BowlerHeaderSize+255)
#define ASSERTED				0
#define NOT_ASSERTED			1

//Method Codes
#define BOWLER_STATUS 					0x00
#define BOWLER_GET					0x10
#define BOWLER_POST  					0x20
#define BOWLER_CRIT 	 				0x30
#define BOWLER_ASYN 	 				0x40

// 1 byte
#define BOWLER_I08      8 // 8 bit integer
#define BOWLER_BOOL    43// a boolean value
//2 byte
#define BOWLER_I16      16//16 bit integer
//4 byte
#define BOWLER_I32      32//32 bit integer
#define BOWLER_FIXED100    41// float
#define BOWLER_FIXED1K    42// float
//streams
#define BOWLER_STR      37// first byte is number of values, next is byte values
#define BOWLER_I32STR   38// first byte is number of values, next is 32 bit values
#define BOWLER_FIXED1K_STR   44// first byte is number of values, next is floats
// ASCII
#define BOWLER_ASCII    39// ASCII string, null terminated


#define B_TRUE 1
#define B_FALSE 0
typedef unsigned char			B_BOOL;
#if !defined(__GENERIC_TYPE_DEFS_H_)
//#define TRUE 1
//#define FALSE 0
//	typedef unsigned char			BOOL;
        typedef enum _BOOL { FALSE = 0, TRUE } BOOL;    /* Undefined size */
	typedef unsigned char			BYTE;
	typedef signed int          	INT;
	typedef signed char         	INT8;
	typedef signed short int    	INT16;
	typedef signed long int     	INT32;
	typedef signed long long    	INT64;

	typedef unsigned int        	UINT;
	typedef unsigned char       	UINT8;
	typedef unsigned short int  	UINT16;
	typedef unsigned long int   	UINT32;
	typedef unsigned long long  	UINT64;
#endif
typedef union _INT16_UNION
{
	INT16 Val;
    BYTE v[2];
    struct
    {
        BYTE LB;
        BYTE SB;
    } byte;
} INT16_UNION;

typedef union _UINT16_UNION
{
	UINT16 Val;
    BYTE v[2];
    struct
    {
        BYTE LB;
        BYTE SB;
    } byte;
} UINT16_UNION;

typedef union _INT32_UNION
{
	INT32 Val;
    BYTE v[4];
    struct
    {
        BYTE LB;
        BYTE SB;
        BYTE TB;
        BYTE FB;
    } byte;
    float f;

} INT32_UNION;
/*
typedef union _UINT64_UNION_DOUBLE
{
    UINT64 Val;
    BYTE v[8];
    struct
    {
        UINT32_UNION LI;
        UINT32_UNION SI;

    } uint;
    double d;

} UINT64_UNION_DOUBLE;*/

typedef union _UINT32_UNION
{
	UINT32 Val;
    BYTE v[4];
    struct
    {
        BYTE LB;
        BYTE SB;
        BYTE TB;
        BYTE FB;
    } byte;

} UINT32_UNION;
#if !defined(NULL)
	#define NULL 0
#endif

#endif /* DEFINES_H_ */
