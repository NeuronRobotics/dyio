/*
 * User_Bowler_RPC_Process.c
 *
 *  Created on: Nov 29, 2009
 *      Author: hephaestus
 */

#include "UserApp.h"

//void setAsync(BYTE channel,BOOL async);
////extern DATA_STRUCT DATA;
//static BYTE temp0;
////static BYTE temp1;
////static BYTE temp2;
////static BYTE temp3;
////static INT32_UNION PID_Temp;
////static BYTE chan;
//int i;
//extern DATA_STRUCT DATA __attribute__ ((section (".scs_global_var")));
//extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));
//static UINT16_UNION timeUnion;
//BYTE UserGetRPCs(BowlerPacket *Packet){
//	int zone = 1;
//	char tmpName[17];
//	int i;
//	BYTE rev[3];
//	static INT32_UNION PID_Temp;
//
//	switch (Packet->use.head.RPC){
//
//
//
//
//
//	default:
//		if(CartesianControllerGetPacket(Packet) == FALSE && (ProcessPIDPacket(Packet)==FALSE)){
//			SyncSessionTime(getMs());
//			SendPacketToCoProc(Packet);
//		}
//		break;
//	}
//	SyncSessionTime(getMs());
//	return TRUE;
//}
//BYTE UserPostRPCs(BowlerPacket *Packet){
//	int zone = 2;
//	//INT32 val;
//	//float time;
//	switch (Packet->use.head.RPC){
//
//
//	default:
//		if(CartesianControllerPostPacket(Packet) == FALSE && (ProcessPIDPacket(Packet)==FALSE)){
//			SyncSessionTime(getMs());
//			SendPacketToCoProc(Packet);
//		}
//		break;
//	}
//	SyncSessionTime(getMs());
//	return TRUE;
//}
//BYTE UserCriticalRPCs(BowlerPacket *Packet){
//	int zone = 3;
//	char tmpName[17];
//	int i;
//	switch (Packet->use.head.RPC){
//
//
//
//	default:
//		if(CartesianControllerCriticalPacket(Packet) == FALSE && (ProcessPIDPacket(Packet)==FALSE)){
//			SyncSessionTime(getMs());
//			SendPacketToCoProc(Packet);
//		}
//		break;
//	}
//	SyncSessionTime(getMs());
//	return TRUE;
//}

