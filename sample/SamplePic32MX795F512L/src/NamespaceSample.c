#include "Bowler/Bowler.h"

static const unsigned char cartNSName[]  = "bcs.sample.*;0.3;;";

BOOL sampleAsyncEventCallback(BowlerPacket * Packet,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){

    // This gets called by the stack when the system is serviced. If you need to use async,
    // fill the provided packet and push it
    return FALSE;
}

BOOL onSamplePost(BowlerPacket *Packet){
    //this is the processor
    
}


static RPC_LIST sample_TEST={	BOWLER_POST,// Method
                                "TEST",//RPC as string
                                &onSamplePost,//function pointer to a packet parsinf function
                                ((const char [4]){	BOWLER_I32,//
                                                        BOWLER_I32,//
							BOWLER_I32,//
                                			0}),//
                                BOWLER_POST,// response method
                                ((const char [4]){	BOWLER_I32,//
                                                        BOWLER_I32,//
							BOWLER_I32,//
                                			0}),//
                                NULL //Termination
};

static NAMESPACE_LIST bcsSample ={	cartNSName,// The string defining the namespace
                                NULL,// the first element in the RPC list
                                &sampleAsyncEventCallback,// async for this namespace
                                NULL// no initial elements to the other namesapce field.
};

static BOOL namespcaedAdded = FALSE;
NAMESPACE_LIST * getBcsSampleNamespace(){
	if(!namespcaedAdded){
                //POST
                addRpcToNamespace(&bcsSample,& sample_TEST);
                namespcaedAdded =TRUE;
	}

	return &bcsSample;//Return pointer to the struct
}
