/**
 * @file Namespace_neuronrobotics_dyio.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */
#include "UserApp.h"

const unsigned char dyioNSName[] = "neuronrobotics.dyio.*;0.3;;";
RunEveryData syncVolt={0,2000};
BOOL pwr=FALSE;

static BOOL heartBeatLock = TRUE;
static int heartBeatLockTime = 1;

void UpdateAVRLED(void){
	pwr=TRUE;
}

void setHeartBeatState( BOOL hb, int time){
	heartBeatLock = hb;
	heartBeatLockTime=time*2;
}

int getHeartBeatTime(){
	return heartBeatLockTime/2;
}
BOOL getHeartBeatLock(){
	return heartBeatLock;
}

BOOL neuronRoboticsDyIOAsyncEventCallback(BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){

	//BYTE i;
	buttonCheck(7);

	//SetGreen(FLAG_BUSY);
	//RTS_HO_IO=FLAG_BUSY;
	if ((RunEvery(&syncVolt)>0)){
		UpdateAVRLED();
	}
	CheckSwitches();

	if(pwr){
		DownstreamPowerChange();
		pwr = FALSE;
	}

	float now = getMs();
	if((now-getLastPacketTime()) > heartBeatLockTime){
		if(heartBeatLock){
			lockServos();
		}
	}else{
		unlockServos();
	}
	SetColor((isLocked() )?1:0,(isActive() && !isLocked())?1:0,1);

    return FALSE;
}

BOOL neuronRoboticsDyIOProcessor(BowlerPacket * Packet){
	BYTE temp0;
	switch (Packet->use.head.RPC){
	case GCHM:
		temp0=Packet->use.data[0];
		Packet->use.data[1]=GetChannelMode(temp0);
		Packet->use.head.DataLegnth=6;
		Packet->use.head.Method=BOWLER_POST;
		break;
	default:
		return FALSE;
	}
	return TRUE;
}



static RPC_LIST neuronRoboticsDyIO_gchm={	BOWLER_POST,// Method
                                "gchm",//RPC as string
                                &neuronRoboticsDyIOProcessor,//function pointer to a packet parsinf function
                                NULL //Termination
};



static NAMESPACE_LIST neuronRoboticsDyIO ={	ioNSName,// The string defining the namespace
                                NULL,// the first element in the RPC list
                                &neuronRoboticsDyIOAsyncEventCallback,// async for this namespace
                                NULL// no initial elements to the other namesapce field.
};

static BOOL namespcaedAdded = FALSE;
NAMESPACE_LIST * get_neuronRoboticsDyIONamespace(){
	if(!namespcaedAdded){
                //POST
                //Add the RPC structs to the namespace
                addRpcToNamespace(&neuronRoboticsDyIO,& neuronRoboticsDyIO_gchm);

                namespcaedAdded =TRUE;
	}

	return &neuronRoboticsDyIO;//Return pointer to the struct
}
