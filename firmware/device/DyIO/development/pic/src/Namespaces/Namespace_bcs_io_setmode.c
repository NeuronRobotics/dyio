/**
 * @file Namespace_bcs_io_setmode.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */
#include "UserApp.h"

const unsigned char setModeNSName[] = "bcs.io.setmode.*;0.3;;";

BOOL bcsIoSetmodeAsyncEventCallback(BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){
	//no async

    return FALSE;
}

BOOL bcsIoSetmodeProcessor(BowlerPacket * Packet){
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



static RPC_LIST bcsIoSetmode_gchm={	BOWLER_POST,// Method
                                "gchm",//RPC as string
                                &bcsIoSetmodeProcessor,//function pointer to a packet parsinf function
                                NULL //Termination
};



static NAMESPACE_LIST bcsIoSetmode ={	ioNSName,// The string defining the namespace
                                NULL,// the first element in the RPC list
                                &bcsIoSetmodeAsyncEventCallback,// async for this namespace
                                NULL// no initial elements to the other namesapce field.
};

static BOOL namespcaedAdded = FALSE;
NAMESPACE_LIST * get_bcsIoSetmodeNamespace(){
	if(!namespcaedAdded){
                //POST
                //Add the RPC structs to the namespace
                addRpcToNamespace(&bcsIoSetmode,& bcsIoSetmode_gchm);

                namespcaedAdded =TRUE;
	}

	return &bcsIoSetmode;//Return pointer to the struct
}
