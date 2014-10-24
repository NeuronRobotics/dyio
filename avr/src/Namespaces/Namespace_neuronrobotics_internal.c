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
    return false; 
}

boolean internalProcessor_g(BowlerPacket * Packet){
	zone = 4;
	uint16_t i;
	uint16_t  start;
	uint16_t end;
	//UINT16_UNION adc;
	switch (Packet->use.head.RPC){
	case EEPD:
		start = Packet->use.data[0];
		end = Packet->use.data[1];
		Packet->use.head.Method=BOWLER_POST;
		if (end >= start){
			for (i=start;i<end;i++){
				Packet->use.data[i-start]=EEReadData(i);
			}
			Packet->use.head.DataLegnth= 4+end-start;
		}else
			ERR(Packet,zone,1);
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
		return false; 
	}
	return true; 
}
boolean internalProcessor_p(BowlerPacket * Packet){
	zone = 5;
	uint16_t start;
	uint16_t  end;
	uint16_t i;
	switch (Packet->use.head.RPC){
	case _PWR:

		SetPowerState0(Packet->use.data[2],Packet->use.data[0]);
		SetPowerState1(Packet->use.data[3],Packet->use.data[1]);
		//Packet->use.head.MessageID=44;
		break;
	case EEPD:
		start = Packet->use.data[0];
		end = Packet->use.data[1];
		if (end >= start){
			for (i=0;i<(end-start);i++){
				EEWriteData(i+start,Packet->use.data[i+2]);
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
                                &internalProcessor_g,//function pointer to a packet parsinf function
                                NULL //Termination
};
RPC_LIST internal_rev_g={	BOWLER_GET,// Method
                                "_rev",//RPC as string
                                &internalProcessor_g,//function pointer to a packet parsinf function
                                NULL //Termination
};
RPC_LIST internal_save_g={	BOWLER_GET,// Method
                                "save",//RPC as string
                                &internalProcessor_g,//function pointer to a packet parsinf function
                                NULL //Termination
};

RPC_LIST internal_pwr_p={	BOWLER_POST,// Method
                                "_pwr",//RPC as string
                                &internalProcessor_p,//function pointer to a packet parsinf function
                                NULL //Termination
};
RPC_LIST internal_eepd_p={	BOWLER_POST,// Method
                                "eepd",//RPC as string
                                &internalProcessor_p,//function pointer to a packet parsinf function
                                NULL //Termination
};


RPC_LIST internal_mac_c={	BOWLER_CRIT,// Method
                                "_mac",//RPC as string
                                &internalProcessor_c,//function pointer to a packet parsinf function
                                NULL //Termination
};
RPC_LIST internal_pwr_c={	BOWLER_CRIT,// Method
                                "_pwr",//RPC as string
                                &internalProcessor_c,//function pointer to a packet parsinf function
                                NULL //Termination
};


NAMESPACE_LIST internalNamespace ={	internalNSName,// The string defining the namespace
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
