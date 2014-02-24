/**
 * @file Namespace_bcs_safe.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */
#include "UserApp.h"
int getHeartBeatTime();
BOOL getHeartBeatLock();
void setHeartBeatState( BOOL hb, int time);

const char safeNSName[] = "bcs.safe.*;0.3;;";


BOOL bcsSafeAsyncEventCallback(BowlerPacket *Packet,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){
	println_W("Async ");print_W(safeNSName);

    return FALSE;
}

BOOL bcsSafeProcessor_g(BowlerPacket * Packet){
	//BYTE temp0;
	UINT16_UNION timeUnion;
	switch (Packet->use.head.RPC){
	case SAFE:
		Packet->use.head.Method=BOWLER_POST;
		Packet->use.data[0]=getHeartBeatLock();
		timeUnion.Val = getHeartBeatTime();
		Packet->use.data[1]=timeUnion.byte.SB;
		Packet->use.data[2]=timeUnion.byte.LB;
		Packet->use.head.DataLegnth=4+3;
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
BOOL bcsSafeProcessor_p(BowlerPacket * Packet){
	//BYTE temp0;
	UINT16_UNION timeUnion;
	BYTE zone =5;
	switch (Packet->use.head.RPC){

	case SAFE:
		timeUnion.byte.SB=Packet->use.data[1];
		timeUnion.byte.LB=Packet->use.data[2];
		setHeartBeatState(Packet->use.data[0],timeUnion.Val);
		READY(Packet,zone,7);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}


static RPC_LIST bcsSafe_safe_g={	BOWLER_GET,// Method
                                "safe",//RPC as string
                                &bcsSafeProcessor_g,//function pointer to a packet parsinf function
                                ((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
								NULL //Termination
};
static RPC_LIST bcsSafe_safe_p={	BOWLER_POST,// Method
                                "safe",//RPC as string
                                &bcsSafeProcessor_p,//function pointer to a packet parsinf function
                                ((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
								NULL //Termination
};



static NAMESPACE_LIST bcsSafe ={	safeNSName,// The string defining the namespace
                                NULL,// the first element in the RPC list
                                &bcsSafeAsyncEventCallback,// async for this namespace
                                NULL// no initial elements to the other namesapce field.
};

static BOOL namespcaedAdded = FALSE;
NAMESPACE_LIST * get_bcsSafeNamespace(){
	if(!namespcaedAdded){
                //POST
                //Add the RPC structs to the namespace
                addRpcToNamespace(&bcsSafe,& bcsSafe_safe_g);
                addRpcToNamespace(&bcsSafe,& bcsSafe_safe_p);

                namespcaedAdded =TRUE;
	}

	return &bcsSafe;//Return pointer to the struct
}
