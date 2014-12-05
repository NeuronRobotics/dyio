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

#ifndef BOWLERSTRUCTDEF_H_
#define BOWLERSTRUCTDEF_H_

//	typedef union _RPC_VALUE {
//		  unsigned char ASCII[4];
//		  unsigned long int		   value;
//	}RPC_VALUE;
#if !defined(__STACK_TSK_H) && !defined(_SOCKET_H_)
	typedef struct __attribute__((__packed__)) _MAC_ADDR
	{
		uint8_t v[6];
	} MAC_ADDR;
#endif
	typedef struct __attribute__((__packed__)) _HEADER
	{
		unsigned char		ProtocolRevision;
		MAC_ADDR			MAC;				// The MAC address of the packet
		unsigned char       Method;				// The method type
		unsigned			MessageID    :7;			// Semi unique Transaction ID
		unsigned    		ResponseFlag :1;		// Is this packet a response packet
		unsigned char		DataLegnth;			// Length of data to come
		unsigned char		CRC;				// CRC for packet
		unsigned long int				RPC;				// 4 byte RPC stored as a 32 bit int for single compare;
	} HEADER;
#define FullPacketDataSize 251
	typedef union  _BowlerPacket{
		unsigned char stream[FullPacketDataSize+sizeof(HEADER)];
		struct
		{
			HEADER head;
			unsigned char data[FullPacketDataSize];
		} use;
	}BowlerPacket;
#define MiniPacketDataSize FullPacketDataSize
	typedef union _BowlerPacketMini{
		unsigned char stream[MiniPacketDataSize+sizeof(HEADER)];
		struct
		{
			HEADER head;
			unsigned char data[MiniPacketDataSize];
		} use;
	}BowlerPacketMini;


typedef struct  __attribute__((__packed__)) _INTERPOLATE_DATA
{
	//Target value for the interpolator to get to
	float set;
	//Initial starting point value of target
	float start;
	//How many ms the interpolation should take
	float setTime;
	//The timestamp of when the interpolation began.
	float startTime;

} INTERPOLATE_DATA;

#endif /* WASPSTRUCTDEF_H_ */
