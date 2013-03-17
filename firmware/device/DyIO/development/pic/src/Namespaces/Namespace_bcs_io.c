/**
 * @file Namespace_bcs_io.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */
#include "UserApp.h"

const unsigned char ioNSName[] = "bcs.io.*;0.3;;";
RunEveryData ppm={0,200};

BOOL bcsIoAsyncEventCallback(BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){
	RunAsync();
	if (RunEvery(&ppm)>0)
		RunPPMCheck();


    return FALSE;
}

BOOL bcsIoProcessor(BowlerPacket * Packet){
	BYTE temp0;
	switch (Packet->use.head.RPC){
	case GCHM:
		temp0=Packet->use.data[0];
		Packet->use.data[1]=GetChannelMode(temp0);
		Packet->use.head.DataLegnth=6;
		Packet->use.head.Method=BOWLER_POST;
		break;
	case GACM:
		Packet->use.head.Method=BOWLER_POST;
		for (i=0;i<24;i++){
			Packet->use.data[i]=GetChannelMode(i);
		}
		Packet->use.head.DataLegnth=4+24;
		break;
	case GCHV:
		if(!GetChannelValue(Packet)){
			//ERR(Packet,zone,0);
		}
		break;
	case GACV:
		populateGACV(Packet);
		break;
	case ASYN:
		Packet->use.head.Method=BOWLER_POST;
		Packet->use.data[1]=IsAsync(Packet->use.data[0]);
		Packet->use.head.DataLegnth=4+2;
		break;
	default:
		return FALSE;
	}
	return TRUE;
}



static RPC_LIST bcsIo_gchm_g={	BOWLER_GET,// Method
                                "gchm",//RPC as string
                                &bcsIoProcessor,//function pointer to a packet parsinf function
                                NULL //Termination
};

static RPC_LIST bcsIo_gacm_g={	BOWLER_GET,// Method
                                "gacm",//RPC as string
                                &bcsIoProcessor,//function pointer to a packet parsinf function
                                NULL //Termination
};

static RPC_LIST bcsIo_gchv_g={	BOWLER_GET,// Method
                                "gchv",//RPC as string
                                &bcsIoProcessor,//function pointer to a packet parsinf function
                                NULL //Termination
};
static RPC_LIST bcsIo_gacv_g={	BOWLER_GET,// Method
                                "gacv",//RPC as string
                                &bcsIoProcessor,//function pointer to a packet parsinf function
                                NULL //Termination
};
static RPC_LIST bcsIo_asyn_g={	BOWLER_GET,// Method
                                "asyn",//RPC as string
                                &bcsIoProcessor,//function pointer to a packet parsinf function
                                NULL //Termination
};


static NAMESPACE_LIST bcsIo ={	ioNSName,// The string defining the namespace
                                NULL,// the first element in the RPC list
                                &bcsIoAsyncEventCallback,// async for this namespace
                                NULL// no initial elements to the other namesapce field.
};

static BOOL namespcaedAdded = FALSE;
NAMESPACE_LIST * get_bcsIoNamespace(){
	if(!namespcaedAdded){
		//POST
		//Add the RPC structs to the namespace
		addRpcToNamespace(&bcsIo,& bcsIo_gchm_g);
		addRpcToNamespace(&bcsIo,& bcsIo_gacm_g);
		addRpcToNamespace(&bcsIo,& bcsIo_gchv_g);
		addRpcToNamespace(&bcsIo,& bcsIo_gacv_g);
		addRpcToNamespace(&bcsIo,& bcsIo_asyn_g);

		namespcaedAdded =TRUE;
	}

	return &bcsIo;//Return pointer to the struct
}


