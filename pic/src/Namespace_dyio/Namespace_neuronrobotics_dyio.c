/**
 * @file Namespace_neuronrobotics_dyio.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */
#include "UserApp.h"

//char dyioNSName[] = "neuronrobotics.dyio.*;1.0;;";
RunEveryData syncVolt = {0, 200};
RunEveryData ppm = {0, 50};

boolean pwr = false; 

boolean heartBeatLock = true;
int heartBeatLockTime = 1;


extern MAC_ADDR MyMAC __attribute__((section(".scs_global_var")));

void UpdateAVRLED(void) {
    pwr = true; 
}

void setHeartBeatState(boolean hb, int time) {
    heartBeatLock = hb;
    heartBeatLockTime = time * 2;
}

int getHeartBeatTime() {
    return heartBeatLockTime / 2;
}

boolean getHeartBeatLock() {
    return heartBeatLock;
}

boolean neuronRoboticsDyIOAsyncEventCallback(BowlerPacket *Packet, boolean(*pidAsyncCallbackPtr)(BowlerPacket *Packet)) {
    //println_W("Async ");print_W(dyioNSName);
    buttonCheck(7);

    int i;
    for (i = 0; i < GetNumberOfIOChannels(); i++) {
        if (GetChannelMode(i) == IS_COUNTER_INPUT_INT || GetChannelMode(i) == IS_COUNTER_OUTPUT_INT) {
            getBcsIoDataTable(i)->PIN.asyncDataCurrentVal = GetCounterByChannel(i);
        }
    }
    if (RunEvery(&ppm) > 0)
        RunPPMCheck();



    //	if ((RunEvery(&syncVolt)>0)){
    //		//UpdateAVRLED();
    //		println_I("Voltages\n");
    //		int i;
    //		for(i=12;i<16;i++){
    //			uint32_t val = getDyIOVoltage(i);
    //			println_I("\t# ");p_int_I(i);
    //			print_I("\t");p_int_I(val);
    //			print_I("\t");p_int_I(getAdcRaw(i, 5));
    ////			UINT32_UNION tmp;
    ////			tmp.Val = val;
    ////			printStream_I(tmp.v,4);
    ////			println_I(" ");
    //		}
    //	}
    CheckSwitches();

    if (pwr) {
        DownstreamPowerChange();
        pwr = false; 
    }

    float now = getMs();
    if ((now - getLastPacketTime()) > heartBeatLockTime) {
        if (heartBeatLock) {
            lockServos();
        }
    } else {
        unlockServos();
    }

    SyncDataTable();

    SetColor((isLocked()) ? 1 : 0, (isActive() && !isLocked()) ? 1 : 0, 1);
    //println_W("Done ");print_W(dyioNSName);
    return false; 
}

boolean neuronRoboticsDyIOProcessor_g(BowlerPacket * Packet) {
    //int zone = 1;
    char tmpName[17];
    int i;
    uint8_t rev[3];
    switch (Packet->use.head.RPC) {
        case _PWR:
            POWER(Packet);
            break;
        case _REV:
            SendPacketToCoProc(Packet);

            //			if(Packet->use.head.RPC == _ERR){
            //				break;
            //			}
            Packet->use.head.DataLegnth = 4 + 3;
            if ((Packet->use.data[0] == MAJOR_REV) && (Packet->use.data[1] == MINOR_REV) && (Packet->use.data[2] == FIRMWARE_VERSION)) {
                SetColor(0, 0, 1);
            } else {
                SetColor(1, 0, 0);
            }
            //		FlashGetFwRev(rev);
            //		for (i=0;i<3;i++){
            //			Packet->use.data[i]=rev[i];
            //		}
            Packet->use.data[0] = MAJOR_REV;
            Packet->use.data[1] = MINOR_REV;
            Packet->use.data[2] = FIRMWARE_VERSION;
            FlashGetBlRev(rev);
            for (i = 0; i < 3; i++) {
                Packet->use.data[i + 3] = rev[i];
            }
            Packet->use.head.DataLegnth = 4 + 6;
            Packet->use.head.Method = BOWLER_POST;
            break;
        case INFO:
            FlashGetName(tmpName);
            i = 0;
            while (tmpName[i] != 0) {
                Packet->use.data[i] = tmpName[i];
                i++;
                buttonCheck(15);
            }
            Packet->use.data[i] = '\0';
            Packet->use.head.Method = BOWLER_POST;
            Packet->use.head.DataLegnth = 4 + i + 1;
            break;

        default:
            return false; 
    }
    return true; 
}

boolean neuronRoboticsDyIOProcessor_p(BowlerPacket * Packet) {
    //uint8_t temp0;
    switch (Packet->use.head.RPC) {

        default:
            return false; 
    }
    return true; 
}

boolean neuronRoboticsDyIOProcessor_c(BowlerPacket * Packet) {
    uint8_t zone = 3;
    char tmpName[17];
    int i;
    switch (Packet->use.head.RPC) {
        case _MAC:
            //SendPacketToCoProc(Packet);
            for (i = 0; i < 6; i++) {
                MyMAC.v[i] = Packet->use.data[i];
            }
            if (FlashSetMac(MyMAC.v)) {
                READY(Packet, zone, 2);
            } else
                ERR(Packet, zone, 2);
            break;

        case _PWR:
            setBrownOutDetect(Packet->use.data[0] ? 0 : 1);
            SendPacketToCoProc(Packet);
            READY(Packet, zone, 5);
            break;
        case INFO:
            if ((Packet->use.head.DataLegnth > 4 + 16) || (Packet->use.head.DataLegnth <= 4)) {
                ERR(Packet, zone, 3);
                break;
            } else
                for (i = 0; i < 17; i++) {
                    tmpName[i] = '\0';
                }
            println_I("Setting name: ");
            Packet->use.data[Packet->use.head.DataLegnth - 4] = '\0';
            //print_I(Packet->use.data);
            print_I(" Num Bytes:");
            p_int_I(Packet->use.head.DataLegnth - 4);
            for (i = 0; i < Packet->use.head.DataLegnth - 4; i++) {
                tmpName[i] = Packet->use.data[i];
            }
            FlashSetName(tmpName);
            READY(Packet, zone, 4);
            break;
        default:
            return false; 
    }
    return true; 
}

RPC_LIST neuronRoboticsDyIO__rev_g = {BOWLER_GET, // Method
    "_rev", //RPC as string
    &neuronRoboticsDyIOProcessor_g, //function pointer to a packet parsinf function
    {0}, // Calling arguments
    BOWLER_POST, // response method
     {
        BOWLER_I08, //major
        BOWLER_I08, // minor
        BOWLER_I08, // FW version
        BOWLER_I08, // AVR major
        BOWLER_I08, // AVR minor
        BOWLER_I08, // AVR FW version
        0
    }, // Response arguments
    NULL //Termination
};

RPC_LIST neuronRoboticsDyIO__pwr_g = {BOWLER_GET, // Method
    "_pwr", //RPC as string
    &neuronRoboticsDyIOProcessor_g, //function pointer to a packet parsinf function
    {0}, // Calling arguments
    BOWLER_POST, // response method
     {
        BOWLER_I08, // 0 regulated
        BOWLER_I08, // 1 regulated
        BOWLER_I16, // Voltage
        0
    }, // Calling arguments
    NULL //Termination
};

RPC_LIST neuronRoboticsDyIO_info_g = {BOWLER_GET, // Method
    "info", //RPC as string
    &neuronRoboticsDyIOProcessor_g, //function pointer to a packet parsinf function
    {0}, // Calling arguments
    BOWLER_POST, // response method
    {
        BOWLER_ASCII,
        0
    }, // Response arguments
    NULL //Termination
};

RPC_LIST neuronRoboticsDyIO__mac_c = {BOWLER_CRIT, // Method
    "_mac", //RPC as string
    &neuronRoboticsDyIOProcessor_c, //function pointer to a packet parsinf function
     {
        BOWLER_I08, // mac address
        BOWLER_I08,
        BOWLER_I08,
        BOWLER_I08,
        BOWLER_I08,
        BOWLER_I08,
        0
    }, // Calling arguments
    BOWLER_POST, // response method
     {
        BOWLER_I08, // code
        BOWLER_I08, // trace
        0
    }, // Response arguments
    NULL //Termination
};

RPC_LIST neuronRoboticsDyIO__pwr_c = {BOWLER_CRIT, // Method
    "_pwr", //RPC as string
    &neuronRoboticsDyIOProcessor_c, //function pointer to a packet parsinf function
     {
        BOWLER_I08, // Brown out override
        0
    }, // Calling arguments
    BOWLER_POST, // response method
    {
        BOWLER_I08, // code
        BOWLER_I08, // trace
        0
    }, // Response arguments
    NULL //Termination
};

RPC_LIST neuronRoboticsDyIO_info_c = {BOWLER_CRIT, // Method
    "info", //RPC as string
    &neuronRoboticsDyIOProcessor_c, //function pointer to a packet parsinf function
     {
        BOWLER_ASCII,
        0
    }, // Calling arguments
    BOWLER_POST, // response method
     {
        BOWLER_I08, // code
        BOWLER_I08, // trace
        0
    }, // Response arguments
    NULL //Termination
};

NAMESPACE_LIST neuronRoboticsDyIO = {"neuronrobotics.dyio.*;1.0;;", // The string defining the namespace
    NULL, // the first element in the RPC list
    &neuronRoboticsDyIOAsyncEventCallback, // async for this namespace
    NULL// no initial elements to the other namesapce field.
};

boolean neuronRoboticsDyIOnamespcaedAdded = false;

NAMESPACE_LIST * get_neuronRoboticsDyIONamespace() {
    if (!neuronRoboticsDyIOnamespcaedAdded) {
        //GET
        //Add the RPC structs to the namespace
        addRpcToNamespace(&neuronRoboticsDyIO, & neuronRoboticsDyIO__rev_g);
        addRpcToNamespace(&neuronRoboticsDyIO, & neuronRoboticsDyIO__pwr_g);
        addRpcToNamespace(&neuronRoboticsDyIO, & neuronRoboticsDyIO_info_g);

        addRpcToNamespace(&neuronRoboticsDyIO, & neuronRoboticsDyIO__mac_c);
        addRpcToNamespace(&neuronRoboticsDyIO, & neuronRoboticsDyIO__pwr_c);
        addRpcToNamespace(&neuronRoboticsDyIO, & neuronRoboticsDyIO_info_c);

        neuronRoboticsDyIOnamespcaedAdded = true;
    }

    return &neuronRoboticsDyIO; //Return pointer to the struct
}
