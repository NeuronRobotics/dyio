/**
 * @file Namespace_bcs_pid_dypid.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */
#include "UserApp_avr.h"

const unsigned char internalNSName[] = "neuronrobotics.internal*;0.3;;";

RunEveryData pid={0,30};
RunEveryData vel={0,100};

BOOL bcsPidDypidAsyncEventCallback(BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){
	checkDigital();
	checkAnalog();

    return FALSE;
}

BOOL bcsPidDypidProcessor_g(BowlerPacket * Packet){

	switch (Packet->use.head.RPC){

	default:
		return FALSE;
	}
	return TRUE;
}

BOOL bcsPidDypidProcessor_c(BowlerPacket * Packet){

	switch (Packet->use.head.RPC){

	default:
		return FALSE;
	}
	return TRUE;
}


static RPC_LIST bcsPidDypid_dpid_g={	BOWLER_GET,// Method
                                "dpid",//RPC as string
                                &bcsPidDypidProcessor_g,//function pointer to a packet parsinf function
                                NULL //Termination
};


static NAMESPACE_LIST internalNamespace ={	internalNSName,// The string defining the namespace
                                NULL,// the first element in the RPC list
                                &bcsPidDypidAsyncEventCallback,// async for this namespace
                                NULL// no initial elements to the other namesapce field.
};

static BOOL namespcaedAdded = FALSE;
NAMESPACE_LIST * get_internalNamespace(){
	if(!namespcaedAdded){
                //POST
                //Add the RPC structs to the namespace
                addRpcToNamespace(&internalNamespace,& bcsPidDypid_dpid_g);
                int i;

                namespcaedAdded =TRUE;
	}

	return &internalNamespace;//Return pointer to the struct
}
