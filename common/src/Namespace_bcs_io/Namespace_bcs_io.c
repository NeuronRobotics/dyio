/**
 * @file Namespace_bcs_io.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */


#include "Bowler/Bowler.h"
#include "Namespace/Namespace_bcs_io.h"

//char ioNSName[] = "bcs.io.*;0.3;;";

boolean bcsIoAsyncEventCallback(BowlerPacket *Packet, boolean (*pidAsyncCallbackPtr)(BowlerPacket *)) {

    int i;
    boolean update = false; 
    //println_W("Async ");print_W(ioNSName);
    for (i = 0; i < GetNumberOfIOChannels(); i++) {
        //println_W("Checking ");p_int_W(i);
        if (pushAsyncReady(i)) {
            update = true; 
        }
    }
    if (update) {
        println_I(__FILE__);
        println_I("Async: ");
        populateGACV(Packet);
        Packet->use.head.Method = BOWLER_ASYN;
        FixPacket(Packet);
        printBowlerPacketDEBUG(Packet, INFO_PRINT);
        if (pidAsyncCallbackPtr != NULL) {
            pidAsyncCallbackPtr(Packet);
        }
    }
    //println_W("Done ");print_W(ioNSName);
    return false; 
}



// GET structures

RPC_LIST bcsIo_gchm_g = {BOWLER_GET, // Method
    "gchm", //RPC as string
    &GetChannelModeFromPacket, //function pointer to a packet parsing function
    ((const char []) {
        BOWLER_I08, // channel
        0
    }),// Calling arguments
    BOWLER_POST, // response method
    ((const char []) {
        BOWLER_I08, // channel
        BOWLER_I08, // mode
        0
    }),// Calling arguments
    NULL //Termination
};

RPC_LIST bcsIo_gacm_g = {BOWLER_GET, // Method
    "gacm", //RPC as string
    &GetAllChannelModeFromPacket, //function pointer to a packet parsing function
     ((const char []) {
        0
    }),// Calling arguments
    BOWLER_POST, // response method
    ((const char [])  {
        BOWLER_STR, // all of the channel modes
        0
    }),// Calling arguments
    NULL //Termination
};

RPC_LIST bcsIo_gchv_g = {BOWLER_GET, // Method
    "gchv", //RPC as string
    &GetChanelValueFromPacket, //function pointer to a packet parsing function
     ((const char []) {
        BOWLER_I08, // channel
        0
    }),// Calling arguments
    BOWLER_POST, // response method
     ((const char []) {
        BOWLER_I08, // channel
        BOWLER_I32, // value
        0
    }),// Calling arguments
    NULL //Termination
};

RPC_LIST bcsIo_gacv_g = {BOWLER_GET, // Method
    "gacv", //RPC as string
    &GetAllChanelValueFromPacket, //function pointer to a packet parsing function
    ((const char [])  {
        0
    }),// Calling arguments
    BOWLER_POST, // response method
    ((const char [])  {
        BOWLER_I32STR,
        0
    }),// Calling arguments
    NULL //Termination
};

RPC_LIST bcsIo_asyn_g = {BOWLER_GET, // Method
    "asyn", //RPC as string
    &GetAsyncFromPacket, //function pointer to a packet parsing function
     ((const char []) {

        BOWLER_I08, // channel
        0
    }),// Calling arguments
    BOWLER_POST, // response method
    ((const char [])  {
        BOWLER_I08, // channel
        BOWLER_I08, // Async mode for given channel
        0
    }),// Calling arguments
    NULL //Termination
};

RPC_LIST bcsIo_gchc_g = {BOWLER_GET, // Method
    "gchc", //RPC as string
    &GetIOChannelCountFromPacket, //function pointer to a packet parsing function
    ((const char []) {
        0
    }),// Calling arguments
    BOWLER_POST, // response method
     ((const char []) {
        BOWLER_I32,
        0
    }),// Calling arguments
    NULL //Termination
};

RPC_LIST bcsIo_gcml_g = {BOWLER_GET, // Method
    "gcml", //RPC as string
    &getFunctionList, //function pointer to a packet parsing function
    ((const char [])  {

        BOWLER_I08, // channel
        0
    }),// Calling arguments
    BOWLER_POST, // response method
    ((const char [])  {
        BOWLER_STR,
        0
    }),// Calling arguments
    NULL //Termination
};
//POST

RPC_LIST bcsIo_strm_p = {BOWLER_POST, // Method
    "strm", //RPC as string
    &SetChanelStreamFromPacket, //function pointer to a packet parsing function
    ((const char [])  {
        BOWLER_I08, // channel
        BOWLER_I32STR, // value
        0
    }),// Calling arguments
    BOWLER_POST, // response method
    ((const char [])  {
        BOWLER_I08, // code
        BOWLER_I08, // trace
        0
    }),// Calling arguments
    NULL //Termination
};

RPC_LIST bcsIo_schv_p = {BOWLER_POST, // Method
    "schv", //RPC as string
    &SetChanelValueFromPacket, //function pointer to a packet parsing function
    ((const char [])  {
        BOWLER_I08, // channel
        BOWLER_I32, // value
        BOWLER_I32, // time in ms
        0
    }),// Calling arguments
    BOWLER_POST, // response method
    ((const char [])  {
        BOWLER_I08, // code
        BOWLER_I08, // trace
        0
    }),// Calling arguments
    NULL //Termination
};

RPC_LIST bcsIo_sacv_p = {BOWLER_POST, // Method
    "sacv", //RPC as string
    &SetAllChannelValueFromPacket, //function pointer to a packet parsing function
     ((const char []) {
        BOWLER_STR,
        0
    }),// Calling arguments
    BOWLER_POST, // response method
    ((const char [])  {
        BOWLER_I08, // code
        BOWLER_I08, // trace
        0
    }),// Calling arguments
    NULL //Termination
};

RPC_LIST bcsIo_asyn_p = {BOWLER_POST, // Method
    "asyn", //RPC as string
    &SetAsyncFromPacket, //function pointer to a packet parsing function
    ((const char [])  {
        BOWLER_I08, // channel
        BOWLER_I08, // async mode
        0
    }),// Calling arguments
    BOWLER_POST, // response method
    ((const char []) {
        0
    }),// Calling arguments
    NULL //Termination
};

//CRIT
RPC_LIST bcsIo_cchn_c = {BOWLER_CRIT, // Method
    "cchn", //RPC as string
    &ConfigureChannelFromPacket, //function pointer to a packet parsing function
    ((const char []) {
        BOWLER_I08, // channel
        BOWLER_I32STR, // values
        0
    }),// Calling arguments
    BOWLER_POST, // response method
     ((const char []) {
        0
    }),// Calling arguments
    NULL //Termination
};
//@Depricated

RPC_LIST bcsIo_schv_c = {BOWLER_CRIT, // Method
    "schv", //RPC as string

    &SetChanelValueFromPacket, //function pointer to a packet parsing function
    ((const char [])  {
        BOWLER_I08, // channel
        BOWLER_I32STR, // values
        0
    }),// Calling arguments
    BOWLER_POST, // response method
    ((const char [])  {
        0
    }),// Calling arguments
    NULL //Termination
};
//@Depricated

RPC_LIST bcsIo_asyn_c = {BOWLER_CRIT, // Method
    "asyn", //RPC as string
    &configAdvancedAsync, //function pointer to a packet parsing function
    ((const char [])  {
        BOWLER_I08, // channel
        BOWLER_I08, // type
        BOWLER_I32, // time in ms
        BOWLER_I32, // compare value
        BOWLER_I08, // threshhold direction
        0
    }),// Calling arguments
    BOWLER_POST, // response method
     ((const char []) {
        0
    }),// Calling arguments
    NULL //Termination
};

//Namespace
NAMESPACE_LIST bcsIo = {"bcs.io.*;0.3;;", // The string defining the namespace
    NULL, // the first element in the RPC list
    &bcsIoAsyncEventCallback, // async for this namespace
    NULL// no initial elements to the other namesapce field.
};




boolean bcsIonamespcaedAdded = false;

NAMESPACE_LIST * get_bcsIoNamespace() {
    if (!bcsIonamespcaedAdded) {
    	bcsIonamespcaedAdded = true;
        //Add the RPC structs to the namespace
        //GET
        addRpcToNamespace(&bcsIo, & bcsIo_gchm_g);
        addRpcToNamespace(&bcsIo, & bcsIo_gacm_g);
        addRpcToNamespace(&bcsIo, & bcsIo_gchv_g);
        addRpcToNamespace(&bcsIo, & bcsIo_gacv_g);
        addRpcToNamespace(&bcsIo, & bcsIo_asyn_g);
        addRpcToNamespace(&bcsIo, & bcsIo_gchc_g);
        addRpcToNamespace(&bcsIo, & bcsIo_gcml_g);
        //POST
        addRpcToNamespace(&bcsIo, & bcsIo_strm_p);
        addRpcToNamespace(&bcsIo, & bcsIo_schv_p);
        addRpcToNamespace(&bcsIo, & bcsIo_sacv_p);
        addRpcToNamespace(&bcsIo, & bcsIo_asyn_p);
        //CRIT
        addRpcToNamespace(&bcsIo, & bcsIo_cchn_c);
        addRpcToNamespace(&bcsIo, & bcsIo_schv_c);
        addRpcToNamespace(&bcsIo, & bcsIo_asyn_c);

        //IO stack initilizations
        initAdvancedAsync();

    }

    return &bcsIo; //Return pointer to the struct
}


