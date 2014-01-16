/**
 * @file Namespace_bcs_io_setmode.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */
#include "Bowler/Bowler.h"
#include "Namespace/Namespace_bcs_io_setmode.h"

const char setModeNSName[] = "bcs.io.setmode.*;0.3;;";



BOOL bcsIoSetmodeAsyncEventCallback(BowlerPacket *Packet,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){
	//no async

    return FALSE;
}


static RPC_LIST bcsIoSetmode_schm_p={	BOWLER_POST,// Method
                                "schm",//RPC as string
                                &AbstractSetChannelMode,//function pointer to a packet parsinf function
                                ((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
								NULL //Termination
};
static RPC_LIST bcsIoSetmode_sacm_p={	BOWLER_POST,// Method
                                "sacm",//RPC as string
                                &AbstractSetAllChannelMode,//function pointer to a packet parsinf function
                                ((const char [1]){
													0}),// Calling arguments
								BOWLER_POST,// response method
								( (const char [1]){
													0}),// Response arguments
								NULL //Termination
};


static NAMESPACE_LIST bcsIoSetmode ={	setModeNSName,// The string defining the namespace
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
