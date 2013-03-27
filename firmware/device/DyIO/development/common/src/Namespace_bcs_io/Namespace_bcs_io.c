/**
 * @file Namespace_bcs_io.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */


#include "Bowler/Bowler.h"
#include "Namespace/Namespace_bcs_io.h"

const unsigned char ioNSName[] = "bcs.io.*;0.3;;";


static BowlerPacket packetTemp;
BOOL bcsIoAsyncEventCallback(BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){
	initAdvancedAsync();
	int i;
	BOOL update=FALSE;
	for(i=0;i<GetNumberOfIOChannels();i++){
		if(ASYN_RDY(i)){
			update=TRUE;
		}
	}
	if(update){
		populateGACV(&packetTemp);
		packetTemp.use.head.Method=BOWLER_ASYN;
		if(pidAsyncCallbackPtr!=NULL)
			pidAsyncCallbackPtr(& packetTemp);
	}

    return FALSE;
}

// GET structures
static RPC_LIST bcsIo_gchm_g={	BOWLER_GET,// Method
                                "gchm",//RPC as string
                                &GetChannelModeFromPacket,//function pointer to a packet parsing function
                                NULL //Termination
};

static RPC_LIST bcsIo_gacm_g={	BOWLER_GET,// Method
                                "gacm",//RPC as string
                                &GetAllChannelModeFromPacket,//function pointer to a packet parsing function
                                NULL //Termination
};

static RPC_LIST bcsIo_gchv_g={	BOWLER_GET,// Method
                                "gchv",//RPC as string
                                &GetChanelValueFromPacket,//function pointer to a packet parsing function
                                NULL //Termination
};
static RPC_LIST bcsIo_gacv_g={	BOWLER_GET,// Method
                                "gacv",//RPC as string
                                &GetAllChanelValueFromPacket,//function pointer to a packet parsing function
                                NULL //Termination
};
static RPC_LIST bcsIo_asyn_g={	BOWLER_GET,// Method
                                "asyn",//RPC as string
                                &GetAsyncFromPacket,//function pointer to a packet parsing function
                                NULL //Termination
};
static RPC_LIST bcsIo_gchc_g={	BOWLER_GET,// Method
                                "gchc",//RPC as string
                                &GetIOChannelCountFromPacket,//function pointer to a packet parsing function
                                NULL //Termination
};
static RPC_LIST bcsIo_gcml_g={	BOWLER_GET,// Method
                                "gcml",//RPC as string
                                &getFunctionList,//function pointer to a packet parsing function
                                NULL //Termination
};
//POST
static RPC_LIST bcsIo_schv_p={	BOWLER_POST,// Method
                                "schv",//RPC as string
                                &SetChanelValueFromPacket,//function pointer to a packet parsing function
                                NULL //Termination
};
static RPC_LIST bcsIo_sacv_p={	BOWLER_POST,// Method
                                "sacv",//RPC as string
                                &SetAllChannelValueFromPacket,//function pointer to a packet parsing function
                                NULL //Termination
};
static RPC_LIST bcsIo_asyn_p={	BOWLER_POST,// Method
                                "asyn",//RPC as string
                                &SetAsyncFromPacket,//function pointer to a packet parsing function
                                NULL //Termination
};
//CRIT
static RPC_LIST bcsIo_cchn_c={	BOWLER_CRIT,// Method
                                "cchn",//RPC as string
                                &ConfigureChannelFromPacket,//function pointer to a packet parsing function
                                NULL //Termination
};
//@Depricated
	static RPC_LIST bcsIo_schv_c={	BOWLER_CRIT,// Method
									"schv",//RPC as string
									&ConfigureChannelFromPacket,//function pointer to a packet parsing function
									NULL //Termination
	};
//@Depricated
static RPC_LIST bcsIo_asyn_c={	BOWLER_CRIT,// Method
                                "asyn",//RPC as string
                                &configAdvancedAsync,//function pointer to a packet parsing function
                                NULL //Termination
};

//Namespace
static NAMESPACE_LIST bcsIo ={	ioNSName,// The string defining the namespace
                                NULL,// the first element in the RPC list
                                &bcsIoAsyncEventCallback,// async for this namespace
                                NULL// no initial elements to the other namesapce field.
};




static BOOL namespcaedAdded = FALSE;
NAMESPACE_LIST * get_bcsIoNamespace(){
	if(!namespcaedAdded){
		namespcaedAdded =TRUE;
		//Add the RPC structs to the namespace
		//GET
		addRpcToNamespace(&bcsIo,& bcsIo_gchm_g);
		addRpcToNamespace(&bcsIo,& bcsIo_gacm_g);
		addRpcToNamespace(&bcsIo,& bcsIo_gchv_g);
		addRpcToNamespace(&bcsIo,& bcsIo_gacv_g);
		addRpcToNamespace(&bcsIo,& bcsIo_asyn_g);
		addRpcToNamespace(&bcsIo,& bcsIo_gchc_g);
		addRpcToNamespace(&bcsIo,& bcsIo_gcml_g);
		//POST
		addRpcToNamespace(&bcsIo,& bcsIo_schv_p);
		addRpcToNamespace(&bcsIo,& bcsIo_sacv_p);
		addRpcToNamespace(&bcsIo,& bcsIo_asyn_p);
		//CRIT
		addRpcToNamespace(&bcsIo,& bcsIo_cchn_c);
		addRpcToNamespace(&bcsIo,& bcsIo_schv_c);
		addRpcToNamespace(&bcsIo,& bcsIo_asyn_c);

		//IO stack initilizations
		initAdvancedAsync();


	}

	return &bcsIo;//Return pointer to the struct
}


