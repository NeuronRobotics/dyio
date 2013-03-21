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
	switch (Packet->use.head.RPC){
	case SCHM:
		SetChannelMode(Packet);
		break;
	case SACM:
		SetAllChannelMode(Packet);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}



static RPC_LIST bcsIoSetmode_schm_p={	BOWLER_POST,// Method
                                "schm",//RPC as string
                                &bcsIoSetmodeProcessor,//function pointer to a packet parsinf function
                                NULL //Termination
};
static RPC_LIST bcsIoSetmode_sacm_p={	BOWLER_POST,// Method
                                "sacm",//RPC as string
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
                addRpcToNamespace(&bcsIoSetmode,& bcsIoSetmode_schm_p);
                addRpcToNamespace(&bcsIoSetmode,& bcsIoSetmode_sacm_p);
                namespcaedAdded =TRUE;
	}

	return &bcsIoSetmode;//Return pointer to the struct
}
