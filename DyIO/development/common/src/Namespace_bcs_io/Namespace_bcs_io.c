/**
 * @file Namespace_bcs_io.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */


#include "Bowler/Bowler.h"
#include "Namespace/Namespace_bcs_io.h"

char ioNSName[] = "bcs.io.*;0.3;;";

BOOL bcsIoAsyncEventCallback(BowlerPacket *Packet,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *)){

	int i;
	BOOL update=FALSE;
	//println_W("Async ");print_W(ioNSName);
	for(i=0;i<GetNumberOfIOChannels();i++){
		//println_W("Checking ");p_int_W(i);
		if(pushAsyncReady(i)){
			update=TRUE;
		}
	}
	if(update){
		println_I(__FILE__);println_I("Async: ");
		populateGACV(Packet);
		Packet->use.head.Method=BOWLER_ASYN;
		FixPacket(Packet);
		printBowlerPacketDEBUG(Packet,INFO_PRINT);
		if(pidAsyncCallbackPtr!=NULL){
			pidAsyncCallbackPtr(Packet);
		}
	}
	//println_W("Done ");print_W(ioNSName);
    return FALSE;
}

// GET structures
static RPC_LIST bcsIo_gchm_g={	BOWLER_GET,// Method
		(const char*)"gchm",//RPC as string
                                &GetChannelModeFromPacket,//function pointer to a packet parsing function
                                ((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
								NULL //Termination
};

static RPC_LIST bcsIo_gacm_g={	BOWLER_GET,// Method
		(const char*) "gacm",//RPC as string
                                &GetAllChannelModeFromPacket,//function pointer to a packet parsing function
                                ((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
								NULL //Termination
};

static RPC_LIST bcsIo_gchv_g={	BOWLER_GET,// Method
		(const char*) "gchv",//RPC as string
                                &GetChanelValueFromPacket,//function pointer to a packet parsing function
                                ((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
								NULL //Termination
};
static RPC_LIST bcsIo_gacv_g={	BOWLER_GET,// Method
		(const char*) "gacv",//RPC as string
                                &GetAllChanelValueFromPacket,//function pointer to a packet parsing function
                                ((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
								NULL //Termination
};
static RPC_LIST bcsIo_asyn_g={	BOWLER_GET,// Method
		(const char*) "asyn",//RPC as string
                                &GetAsyncFromPacket,//function pointer to a packet parsing function
                                ((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
								NULL //Termination
};
static RPC_LIST bcsIo_gchc_g={	BOWLER_GET,// Method
		(const char*) "gchc",//RPC as string
                                &GetIOChannelCountFromPacket,//function pointer to a packet parsing function
                                ((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
								NULL //Termination
};
static RPC_LIST bcsIo_gcml_g={	BOWLER_GET,// Method
		(const char*)"gcml",//RPC as string
                                &getFunctionList,//function pointer to a packet parsing function
                                ((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
								NULL //Termination
};
//POST
static RPC_LIST bcsIo_schv_p={	BOWLER_POST,// Method
		(const char*) "schv",//RPC as string
                                &SetChanelValueFromPacket,//function pointer to a packet parsing function
                                ((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
								NULL //Termination
};
static RPC_LIST bcsIo_sacv_p={	BOWLER_POST,// Method
		(const char*) "sacv",//RPC as string
                                &SetAllChannelValueFromPacket,//function pointer to a packet parsing function
                                ((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
								NULL //Termination
};
static RPC_LIST bcsIo_asyn_p={	BOWLER_POST,// Method
		(const char*) "asyn",//RPC as string
                                &SetAsyncFromPacket,//function pointer to a packet parsing function
                                ((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
								NULL //Termination
};
//CRIT
static RPC_LIST bcsIo_cchn_c={	BOWLER_CRIT,// Method
		(const char*) "cchn",//RPC as string
                                &ConfigureChannelFromPacket,//function pointer to a packet parsing function
                                ((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
								NULL //Termination
};
//@Depricated
	static RPC_LIST bcsIo_schv_c={	BOWLER_CRIT,// Method
			(const char*)"schv",//RPC as string
									&ConfigureChannelFromPacket,//function pointer to a packet parsing function
									((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
								NULL //Termination
	};
//@Depricated
static RPC_LIST bcsIo_asyn_c={	BOWLER_CRIT,// Method
		(const char*)"asyn",//RPC as string
                                &configAdvancedAsync,//function pointer to a packet parsing function
                                ((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
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


