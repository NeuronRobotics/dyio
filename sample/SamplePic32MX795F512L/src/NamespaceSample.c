#include "Bowler/Bowler.h"
#define setLed(a,b,c) 	_RD0=a;_RD1=b;_RD2=c;

static const unsigned char cartNSName[]  = "bcs.sample.*;0.3;;";

BOOL sampleAsyncEventCallback(BowlerPacket * Packet,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){

    // This gets called by the stack when the system is serviced. If you need to use async,
    // fill the provided packet and push it
    return FALSE;
}

BOOL onSamplePost(BowlerPacket *Packet){

    // get the values to use for the LED values
    int val0 = get32bit( Packet, 0);
    int val1 = get32bit( Packet, 4);
    int val2 = get32bit( Packet, 8);

    _RD0=val0?1:0;
    _RD1=val1?1:0;
    _RD2=val2?1:0;

    // set the button values back into the packet
    set32bit(Packet,_RD6, 0);
    set32bit(Packet,_RD7, 4);
    set32bit(Packet,_RD13, 8);
}


static RPC_LIST sample_TEST={	BOWLER_POST,// Method
                                "TEST",//RPC as string
                                &onSamplePost,//function pointer to a packet parsing function
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
