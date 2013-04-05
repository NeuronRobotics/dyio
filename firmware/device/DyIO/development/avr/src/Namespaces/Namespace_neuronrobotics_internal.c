/**
 * @file Namespace_bcs_pid_dypid.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */
#include "UserApp_avr.h"

const char internalNSName[] = "neuronrobotics.internal*;0.3;;";

RunEveryData pid={0,30};
RunEveryData vel={0,100};

static BYTE zone;
BOOL bcsPidDypidAsyncEventCallback(BowlerPacket* Packet,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){
	checkDigital();
	checkAnalog();

    return FALSE;
}

BOOL bcsPidDypidProcessor_g(BowlerPacket * Packet){
	zone = 4;
	UINT16 i;
	UINT16  start;
	UINT16 end;
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
		return FALSE;
	}
	return TRUE;
}
BOOL bcsPidDypidProcessor_p(BowlerPacket * Packet){
	zone = 5;
	UINT16_UNION v;
	UINT16 start;
	UINT16  end;
	UINT16 i;
	switch (Packet->use.head.RPC){
	case _PWR:
		v.byte.SB = Packet->use.data[2];
		v.byte.LB = Packet->use.data[3];
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
		return FALSE;
	}
	return TRUE;
}

BOOL bcsPidDypidProcessor_c(BowlerPacket * Packet){

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
		return FALSE;
	}
	return TRUE;
}


static RPC_LIST bcsPidDypid_dpid_g={	BOWLER_GET,// Method
                                "dpid",//RPC as string
                                &bcsPidDypidProcessor_g,//function pointer to a packet parsinf function
                                NULL //Termination
};


static NAMESPACE_LIST internalNamespace ={	internalNSName,// The string defining the namespace
                                NULL,// the first element in the RPC list
                                &bcsPidDypidAsyncEventCallback,// async for this namespace
                                NULL// no initial elements to the other namesapce field.
};

static BOOL namespcaedAdded = FALSE;
NAMESPACE_LIST * get_internalNamespace(){
	if(!namespcaedAdded){
                //POST
                //Add the RPC structs to the namespace
                addRpcToNamespace(&internalNamespace,& bcsPidDypid_dpid_g);

                namespcaedAdded =TRUE;
	}

	return &internalNamespace;//Return pointer to the struct
}
