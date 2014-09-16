/**
 * @file Namespace_bcs_pid_dypid.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */
#include "UserApp.h"

char dypidNSName[] = "bcs.pid.dypid.*;0.3;;";
RunEveryData pid = {0, 30};
RunEveryData vel = {0, 100};

boolean bcsPidDypidAsyncEventCallback(BowlerPacket *Packet, boolean(*pidAsyncCallbackPtr)(BowlerPacket *Packet)) {
    //println_W("Async ");print_W(dypidNSName);
    if (RunEvery(&pid) > 0) {
        RunPIDControl();
    }
    //println_I("Run Velocity ");
#if defined(USE_VELOCITY)
    if (RunEvery(&vel) > 0) {
        RunVel();
    }
#endif
    //println_W("Done ");print_W(dypidNSName);
    return false; 
}

boolean bcsPidDypidProcessor_g(BowlerPacket * Packet) {
    //uint8_t temp0;
    switch (Packet->use.head.RPC) {
        case DPID:
            GetConfigDyPID(Packet);
            break;
        default:
            return false; 
    }
    return true; 
}

boolean bcsPidDypidProcessor_c(BowlerPacket * Packet) {
    //uint8_t temp0;
    uint8_t zone = 4;
    switch (Packet->use.head.RPC) {
        case DPID:
            if (ConfigDyPID(Packet)) {
                READY(Packet, zone, 1);
            } else
                ERR(Packet, zone, 1);
            break;
        default:
            return false; 
    }
    return true; 
}

static RPC_LIST bcsPidDypid_dpid_g = {BOWLER_GET, // Method
    "dpid", //RPC as string
    &bcsPidDypidProcessor_g, //function pointer to a packet parsinf function
    ((const char [2]) {
        BOWLER_I08, // group
        0
    }), // Calling arguments
    BOWLER_POST, // response method
    ((const char [6]) {
        BOWLER_I08, // group
        BOWLER_I08, // input channel
        BOWLER_I08, // input mode
        BOWLER_I08, // output channel
        BOWLER_I08, // output mode
        0
    }), // Response arguments
    NULL //Termination
};

static RPC_LIST bcsPidDypid_dpid_c = {BOWLER_CRIT, // Method
    "dpid", //RPC as string
    &bcsPidDypidProcessor_c, //function pointer to a packet parsinf function
    ((const char [6]) {
        BOWLER_I08, // group
        BOWLER_I08, // input channel
        BOWLER_I08, // input mode
        BOWLER_I08, // output channel
        BOWLER_I08, // output mode
        0
    }), // Response arguments
    BOWLER_POST, // response method
    ((const char [1]) {
        0
    }), // Response arguments
    NULL //Termination
};

static NAMESPACE_LIST bcsPidDypid = {dypidNSName, // The string defining the namespace
    NULL, // the first element in the RPC list
    &bcsPidDypidAsyncEventCallback, // async for this namespace
    NULL// no initial elements to the other namesapce field.
};

static boolean namespcaedAdded = false; 

NAMESPACE_LIST * get_bcsPidDypidNamespace() {
    if (!namespcaedAdded) {
        //POST
        //Add the RPC structs to the namespace
        addRpcToNamespace(&bcsPidDypid, & bcsPidDypid_dpid_g);
        addRpcToNamespace(&bcsPidDypid, & bcsPidDypid_dpid_c);

        namespcaedAdded = true; 
    }

    return &bcsPidDypid; //Return pointer to the struct
}
