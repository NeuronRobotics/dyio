/**
 * @file Namespace_bcs_io_setmode.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */
#include "Bowler/Bowler.h"
#include "Namespace/Namespace_bcs_io_setmode.h"

char setModeNSName[] = "bcs.io.setmode.*;0.3;;";

boolean bcsIoSetmodeAsyncEventCallback(BowlerPacket *Packet, boolean(*pidAsyncCallbackPtr)(BowlerPacket *Packet)) {
    //no async
    //println_W("No Async ");print_W(setModeNSName);
    return false; 
}

RPC_LIST bcsIoSetmode_schm_p = {BOWLER_POST, // Method
    "schm", //RPC as string
    &AbstractSetChannelMode, //function pointer to a packet parsing function
    ((const char [4]) {
        BOWLER_I08, // Channel
        BOWLER_I08, // mode
        BOWLER_I08, // async
        0
    }), // Calling arguments
    BOWLER_POST, // response method
    ((const char [1]) {
        0
    }), // Response arguments
    NULL //Termination
};

RPC_LIST bcsIoSetmode_sacm_p = {BOWLER_POST, // Method
    "sacm", //RPC as string
    &AbstractSetAllChannelMode, //function pointer to a packet parsinf function
    ((const char [2]) {
        BOWLER_STR,
        0
    }), // Calling arguments
    BOWLER_POST, // response method
    ((const char [1]) {
        0
    }), // Response arguments
    NULL //Termination
};


NAMESPACE_LIST bcsIoSetmode = {setModeNSName, // The string defining the namespace
    NULL, // the first element in the RPC list
    &bcsIoSetmodeAsyncEventCallback, // async for this namespace
    NULL// no initial elements to the other namesapce field.
};

boolean bcsIoSetnamespcaedAdded = false;

NAMESPACE_LIST * get_bcsIoSetmodeNamespace() {
    if (!bcsIoSetnamespcaedAdded) {
        //POST
        //Add the RPC structs to the namespace
        addRpcToNamespace(&bcsIoSetmode, & bcsIoSetmode_schm_p);
        addRpcToNamespace(&bcsIoSetmode, & bcsIoSetmode_sacm_p);
        bcsIoSetnamespcaedAdded = true;
    }

    return &bcsIoSetmode; //Return pointer to the struct
}
