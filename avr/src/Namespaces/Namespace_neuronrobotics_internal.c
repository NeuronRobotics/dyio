/**
 * @file Namespace_bcs_pid_dypid.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */
#include "UserApp_avr.h"

const char internalNSName[] = "neuronrobotics.internal*;0.3;;";

RunEveryData vel={0,1000};

static uint8_t zone;
boolean internalAsyncEventCallback(BowlerPacket* Packet,boolean (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){
	checkDigital();
	checkAnalog();
//	TIMSK1bits._OCIE1A=1;// Pin timer
//	TCCR1Bbits._CS =2;
//	if(RunEvery(&vel)>0){
//		clearPrint();
//		Print_Level l = getPrintLevel();
//		setPrintLevelInfoPrint();
//		printSortedData();
//		setPrintLevel(l);
//	}

    return false; 
}

boolean internalProcessor_g(BowlerPacket * Packet){
	zone = 4;
	uint16_t i;

	uint16_t end, size,start;
	Print_Level l = getPrintLevel();
	setPrintLevelInfoPrint();

	//UINT16_UNION adc;
	switch (Packet->use.head.RPC){
	case EEPD:

		start = Packet->use.data[0];
		end = Packet->use.data[1];
		size = end-start;
//		println_W("Got<< eeprom page: ");p_int_W(start);
//		print_W(" to ");p_int_W(end);
//		print_W(" size ");p_int_W(size);
//		printBowlerPacketDEBUG(Packet,WARN_PRINT);

		Packet->use.data[0]=size;
		Packet->use.head.Method=BOWLER_POST;
		if (size>0){
			for (i=0;i<size;i++){
				Packet->use.data[i+1]=EEReadData(i+start);
			}

		}else
			ERR(Packet,zone,1);
		Packet->use.head.DataLegnth = 4+1+size;
//		println_W("RX>> ");
//		printBowlerPacketDEBUG(Packet,WARN_PRINT);
		break;
	case _PWR:

		SetPowerState0(Packet->use.data[2],Packet->use.data[0]);
		SetPowerState1(Packet->use.data[3],Packet->use.data[1]);
		//Packet->use.head.MessageID=44;
		Packet->use.data[4]=getPowerOverRide();
		break;
	case _REV:
		Packet->use.data[0]=MAJOR_REV;
		Packet->use.data[1]=MINOR_REV;
		Packet->use.data[2]=FIRMWARE_VERSION;
		Packet->use.head.DataLegnth=4+3;
		break;
	case SAVE:
		Packet->use.head.Method=BOWLER_POST;
		Packet->use.head.DataLegnth = 4 + NUM_PINS;
		for (i=0;i<NUM_PINS;i++){
			Packet->use.data[i]=EEReadValue(i);
		}
		break;
	default:
		println_E("ERR>> ");
		printBowlerPacketDEBUG(Packet,ERROR_PRINT);
		setPrintLevel(l);
		return false; 
	}
	setPrintLevel(l);
	return true; 
}
boolean internalProcessor_p(BowlerPacket * Packet){
	zone = 5;
	uint16_t start;
	uint16_t  end;
	uint16_t i;
	switch (Packet->use.head.RPC){

	case EEPD:
		start = Packet->use.data[0];
		end = Packet->use.data[1];

		if (end >= start){
			for (i=0;i<(end-start);i++){
				EEWriteData(i+start,Packet->use.data[i+3]);
			}
		}else
			ERR(Packet,zone,4);
		break;

	default:
		return false; 
	}
	return true; 
}

boolean internalProcessor_c(BowlerPacket * Packet){

	switch (Packet->use.head.RPC){
	case _MAC:
		if(ProvisionMAC(Packet->use.data)){
			READY(Packet,zone,1);
			break;
		}
		else
			ERR(Packet,zone,1);
		break;
	case _PWR:
		setPowerOverride(Packet->use.data[0]);
		break;
	default:
		return false; 
	}
	return true; 
}


RPC_LIST internal_eepd_g={	BOWLER_GET,// Method
                                "eepd",//RPC as string
                                &internalProcessor_g,//function pointer to a packet parsing function
                                { 		BOWLER_I08, // start address
                                        BOWLER_I08, //end address
                                        0}, // Calling arguments
                                BOWLER_POST, // response method
                                {	BOWLER_STR, // values
                                		0}, // Calling arguments
                                NULL //Termination
};
RPC_LIST internal_rev_g={	BOWLER_GET,// Method
                                "_rev",//RPC as string
                                &internalProcessor_g,//function pointer to a packet parsing function
                                {0}, // Calling arguments
                                BOWLER_POST, // response method
                                {0}, // Calling arguments
                                NULL //Termination
};
RPC_LIST internal_save_g={	BOWLER_GET,// Method
                                "save",//RPC as string
                                &internalProcessor_g,//function pointer to a packet parsing function
                                {0}, // Calling arguments
                                BOWLER_POST, // response method
                                {0}, // Calling arguments
                                NULL //Termination
};

RPC_LIST internal_pwr_p={	BOWLER_GET,// Method
                                "_pwr",//RPC as string
                                &internalProcessor_g,//function pointer to a packet parsing function
                                {0}, // Calling arguments
                                BOWLER_POST, // response method
                                {
                                    BOWLER_I08, // 0 regulated
                                    BOWLER_I08, // 1 regulated
                                    BOWLER_I16, // Voltage
                                    BOWLER_BOOL,// override mode
                                    0
                                }, // Calling arguments
                                NULL //Termination
};
RPC_LIST internal_eepd_p={	BOWLER_POST,// Method
                                "eepd",//RPC as string
                                &internalProcessor_p,//function pointer to a packet parsing function
                                {		BOWLER_I08, // start address
                                        BOWLER_I08, //end address
                                        BOWLER_STR, // values
                                        0}, // Calling arguments
                                BOWLER_POST, // response method
                                {0}, // Calling arguments
                                NULL //Termination
};


RPC_LIST internal_mac_c={	BOWLER_CRIT,// Method
                                "_mac",//RPC as string
                                &internalProcessor_c,//function pointer to a packet parsing function
                                {0}, // Calling arguments
                                BOWLER_POST, // response method
                                {0}, // Calling arguments
                                NULL //Termination
};
RPC_LIST internal_pwr_c={	BOWLER_CRIT,// Method
                                "_pwr",//RPC as string
                                &internalProcessor_c,//function pointer to a packet parsing function
                                {0}, // Calling arguments
                                BOWLER_POST, // response method
                                {0}, // Calling arguments
                                NULL //Termination
};


NAMESPACE_LIST internalNamespace ={	"neuronrobotics.internal*;0.3;;",// The string defining the namespace
                                NULL,// the first element in the RPC list
                                &internalAsyncEventCallback,// async for this namespace
                                NULL// no initial elements to the other namesapce field.
};

boolean bcsPidDypidnamespcaedAdded = false;
NAMESPACE_LIST * get_internalNamespace(){
	if(!bcsPidDypidnamespcaedAdded){
                //POST
                //Add the RPC structs to the namespace
                addRpcToNamespace(&internalNamespace,& internal_eepd_g);
                addRpcToNamespace(&internalNamespace,& internal_rev_g);
                addRpcToNamespace(&internalNamespace,& internal_save_g);

                addRpcToNamespace(&internalNamespace,& internal_pwr_p);
                addRpcToNamespace(&internalNamespace,& internal_eepd_p);

                addRpcToNamespace(&internalNamespace,& internal_pwr_c);
                addRpcToNamespace(&internalNamespace,& internal_mac_c);

                bcsPidDypidnamespcaedAdded =true; 
	}

	return &internalNamespace;//Return pointer to the struct
}
