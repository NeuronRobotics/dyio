/**
 * @file Namespace_bcs_safe.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */
#include "UserApp.h"

const unsigned char safeNSName[] = "bcs.safe.*;0.3;;";


BOOL bcsSafeAsyncEventCallback(BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){


    return FALSE;
}

BOOL bcsSafeProcessor(BowlerPacket * Packet){
	BYTE temp0;
	switch (Packet->use.head.RPC){
	case GCHM:
		temp0=Packet->use.data[0];
		Packet->use.data[1]=GetChannelMode(temp0);
		Packet->use.head.DataLegnth=6;
		Packet->use.head.Method=BOWLER_POST;
		break;
	default:
		return FALSE;
	}
	return TRUE;
}



static RPC_LIST bcsSafe_gchm={	BOWLER_POST,// Method
                                "gchm",//RPC as string
                                &bcsSafeProcessor,//function pointer to a packet parsinf function
                                NULL //Termination
};



static NAMESPACE_LIST bcsSafe ={	ioNSName,// The string defining the namespace
                                NULL,// the first element in the RPC list
                                &bcsSafeAsyncEventCallback,// async for this namespace
                                NULL// no initial elements to the other namesapce field.
};

static BOOL namespcaedAdded = FALSE;
NAMESPACE_LIST * get_bcsSafeNamespace(){
	if(!namespcaedAdded){
                //POST
                //Add the RPC structs to the namespace
                addRpcToNamespace(&bcsSafe,& bcsSafe_gchm);

                namespcaedAdded =TRUE;
	}

	return &bcsSafe;//Return pointer to the struct
}
