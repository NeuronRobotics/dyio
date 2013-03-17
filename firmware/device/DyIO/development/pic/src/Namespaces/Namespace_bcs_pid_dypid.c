/**
 * @file Namespace_bcs_pid_dypid.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */
#include "UserApp.h"

const unsigned char dypidNSName[] = "bcs.pid.dypid.*;0.3;;";
RunEveryData pid={0,30};
RunEveryData vel={0,100};

BOOL bcsPidDypidAsyncEventCallback(BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){

	if (RunEvery(&pid)>0){
		RunPID();
	}
#if defined(USE_VELOCITY)
	if (RunEvery(&vel)>0){
		RunVel();
	}
#endif
    return FALSE;
}

BOOL bcsPidDypidProcessor(BowlerPacket * Packet){
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



static RPC_LIST bcsPidDypid_gchm={	BOWLER_POST,// Method
                                "gchm",//RPC as string
                                &bcsPidDypidProcessor,//function pointer to a packet parsinf function
                                NULL //Termination
};



static NAMESPACE_LIST bcsPidDypid ={	ioNSName,// The string defining the namespace
                                NULL,// the first element in the RPC list
                                &bcsPidDypidAsyncEventCallback,// async for this namespace
                                NULL// no initial elements to the other namesapce field.
};

static BOOL namespcaedAdded = FALSE;
NAMESPACE_LIST * get_bcsPidDypidNamespace(){
	if(!namespcaedAdded){
                //POST
                //Add the RPC structs to the namespace
                addRpcToNamespace(&bcsPidDypid,& bcsPidDypid_gchm);

                namespcaedAdded =TRUE;
	}

	return &bcsPidDypid;//Return pointer to the struct
}
