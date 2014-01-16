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
#include "Bowler/Bowler.h"

#define __WASP2_C

const MAC_ADDR Broadcast={{{0,0,0,0,0,0}}};
MAC_ADDR MyMAC ={{{0x74,0xf7,0x26,0x01,0x01,0x01}}} ;
//static BYTE i;
#if defined(USE_LINKED_LIST_NAMESPACE)

#else
const unsigned char coreName[] = "bcs.core.*;0.3;;";
#endif

void Bowler_Init(void){
	//no longer doing hardwar inits from stack
//	startScheduler();
//	Bowler_HAL_Init();

#if defined(USE_LINKED_LIST_NAMESPACE)
	addNamespaceToList((NAMESPACE_LIST * ) getBcsCoreNamespace());
        addNamespaceToList((NAMESPACE_LIST * ) getBcsRpcNamespace());
#else
	AddNamespace(sizeof(coreName),coreName);
#endif
}

BOOL process(BowlerPacket * Packet){
	int i;
	//if(debug){
		if(	Packet->use.head.RPC != GetRPCValue("_pwr") &&
			Packet->use.head.RPC != GetRPCValue("_png")
				){//Ignore Power Packet
			println("Got:",INFO_PRINT);printPacket(Packet,INFO_PRINT);
		}
	//}
	if ( (CheckAddress(MyMAC.v,Packet->use.head.MAC.v) == TRUE) || ((CheckAddress((BYTE *)Broadcast.v,(BYTE *)Packet->use.head.MAC.v) == TRUE) )) {
		Process_Self_Packet(Packet);
		for (i=0;i<6;i++){
			Packet->use.head.MAC.v[i]=MyMAC.v[i];
		}
		SetCRC(Packet);
		return TRUE;
	}else{

		println("Packet not addressed to me: ",ERROR_PRINT);
		printByteArray(Packet->use.head.MAC.v,6,ERROR_PRINT);
		print(" is not mine: ",ERROR_PRINT);
		printByteArray(MyMAC.v,6,ERROR_PRINT);

	}
	return FALSE;
}

/**
 * Run an instance of the server. THis uses static memory
 */
BYTE Bowler_Server_Static(BowlerPacket * Packet,BYTE_FIFO_STORAGE * fifo){

	BOOL back = GetBowlerPacket(Packet, fifo);

	if (back){
		return process( Packet);;
	}//Have a packet

	return FALSE;
}

BYTE Bowler_Server(BowlerPacket * Packet, BOOL debug){

	BOOL back = GetBowlerPacket_arch(Packet);

	if (back){
		SetColor(0,1,0);
		if(process( Packet)){
			//Packet found, sending
			PutBowlerPacket(Packet);
			if(	Packet->use.head.RPC != GetRPCValue("_pwr") &&
				Packet->use.head.RPC != GetRPCValue("_png")
					){//Ignore Power Packet
				println("Response:",INFO_PRINT);printPacket(Packet,INFO_PRINT);
			}
			SetColor(0,0,1);
			return TRUE;
		}
	}//Have a packet

	return FALSE;
}









