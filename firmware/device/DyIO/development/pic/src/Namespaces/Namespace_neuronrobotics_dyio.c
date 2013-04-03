/**
 * @file Namespace_neuronrobotics_dyio.c
 *
 * Created on: Mar 16, 2013
 * @author hephaestus
 */
#include "UserApp.h"

const unsigned char dyioNSName[] = "neuronrobotics.dyio.*;0.3;;";
RunEveryData syncVolt={0,2000};
RunEveryData ppm={0,50};

BOOL pwr=FALSE;

static BOOL heartBeatLock = TRUE;
static int heartBeatLockTime = 1;


extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));

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

	buttonCheck(7);

	int i;
	for(i=0;i<GetNumberOfIOChannels();i++){
		if(GetChannelMode(i)==IS_COUNTER_INPUT_INT || GetChannelMode(i)==IS_COUNTER_OUTPUT_INT){
			getBcsIoDataTable()[i].asyncData.currentVal = GetCounterByChannel(i);
		}
	}
	if (RunEvery(&ppm)>0)
		RunPPMCheck();

	PushCoProcAsync();

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

	SyncDataTable();

	SetColor((isLocked() )?1:0,(isActive() && !isLocked())?1:0,1);

    return FALSE;
}

BOOL neuronRoboticsDyIOProcessor_g(BowlerPacket * Packet){
	int zone = 1;
	char tmpName[17];
	int i;
	BYTE rev[3];
	switch (Packet->use.head.RPC){
		case _PWR:
				POWER(Packet);
				break;
		case _REV:
			SendPacketToCoProc(Packet);

//			if(Packet->use.head.RPC == _ERR){
//				break;
//			}
			Packet->use.head.DataLegnth=4+3;
			if((Packet->use.data[0]==MAJOR_REV) && (Packet->use.data[1]==MINOR_REV) && (Packet->use.data[2]==FIRMWARE_VERSION) ){
				SetColor(0,0,1);
			}else{
				SetColor(1,0,0);
			}
	//		FlashGetFwRev(rev);
	//		for (i=0;i<3;i++){
	//			Packet->use.data[i]=rev[i];
	//		}
			Packet->use.data[0]=MAJOR_REV;
			Packet->use.data[1]=MINOR_REV;
			Packet->use.data[2]=FIRMWARE_VERSION;
			FlashGetBlRev(rev);
			for (i=0;i<3;i++){
				Packet->use.data[i+3]=rev[i];
			}
			Packet->use.head.DataLegnth=4+6;
			Packet->use.head.Method=BOWLER_POST;
			break;
		case INFO:
			FlashGetName(tmpName);
			i=0;
			while(tmpName[i]!=0){
				Packet->use.data[i]=tmpName[i];
				i++;
				buttonCheck(15);
			}
			Packet->use.data[i]='\0';
			Packet->use.head.Method=BOWLER_POST;
			Packet->use.head.DataLegnth=4+i+1;
			break;

	default:
		return FALSE;
	}
	return TRUE;
}
BOOL neuronRoboticsDyIOProcessor_p(BowlerPacket * Packet){
	BYTE temp0;
	switch (Packet->use.head.RPC){

	default:
		return FALSE;
	}
	return TRUE;
}

BOOL neuronRoboticsDyIOProcessor_c(BowlerPacket * Packet){
	BYTE zone = 3;
	char tmpName[17];
	int i;
	switch (Packet->use.head.RPC){
	case _MAC:
		//SendPacketToCoProc(Packet);
		for (i=0;i<6;i++){
			MyMAC.v[i]=Packet->use.data[i];
		}
		if(FlashSetMac(MyMAC.v)){
			READY(Packet,zone,2);
		}else
			ERR(Packet,zone,2);
		break;

	case _PWR:
		setBrownOutDetect(Packet->use.data[0]?0:1);
		SendPacketToCoProc(Packet);
		READY(Packet,zone,5);
		break;
	case INFO:
		if ((Packet->use.head.DataLegnth>4+16)||(Packet->use.head.DataLegnth<=4)){
			ERR(Packet,zone,3);
			break;
		}else
			for(i=0;i<17;i++){
				tmpName[i]='\0';
			}
			println_I("Setting name: ");
			Packet->use.data[Packet->use.head.DataLegnth-4]='\0';
			print_I((const char *)Packet->use.data);
			print_I(" Num Bytes:");
			p_sl_I(Packet->use.head.DataLegnth-4);
			for(i=0;i<Packet->use.head.DataLegnth-4;i++){
				tmpName[i]=Packet->use.data[i];
			}
		FlashSetName(tmpName);
		READY(Packet,zone,4);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

static RPC_LIST neuronRoboticsDyIO__rev_g={	BOWLER_GET,// Method
                                "_rev",//RPC as string
                                &neuronRoboticsDyIOProcessor_g,//function pointer to a packet parsinf function
                                NULL //Termination
};
static RPC_LIST neuronRoboticsDyIO__pwr_g={	BOWLER_GET,// Method
                                "_pwr",//RPC as string
                                &neuronRoboticsDyIOProcessor_g,//function pointer to a packet parsinf function
                                NULL //Termination
};
static RPC_LIST neuronRoboticsDyIO_info_g={	BOWLER_GET,// Method
                                "info",//RPC as string
                                &neuronRoboticsDyIOProcessor_g,//function pointer to a packet parsinf function
                                NULL //Termination
};

static RPC_LIST neuronRoboticsDyIO__mac_c={	BOWLER_POST,// Method
                                "_mac",//RPC as string
                                &neuronRoboticsDyIOProcessor_c,//function pointer to a packet parsinf function
                                NULL //Termination
};
static RPC_LIST neuronRoboticsDyIO__pwr_c={	BOWLER_POST,// Method
                                "_pwr",//RPC as string
                                &neuronRoboticsDyIOProcessor_c,//function pointer to a packet parsinf function
                                NULL //Termination
};
static RPC_LIST neuronRoboticsDyIO_info_c={	BOWLER_POST,// Method
                                "info",//RPC as string
                                &neuronRoboticsDyIOProcessor_c,//function pointer to a packet parsinf function
                                NULL //Termination
};

static NAMESPACE_LIST neuronRoboticsDyIO ={	dyioNSName,// The string defining the namespace
                                NULL,// the first element in the RPC list
                                &neuronRoboticsDyIOAsyncEventCallback,// async for this namespace
                                NULL// no initial elements to the other namesapce field.
};

static BOOL namespcaedAdded = FALSE;
NAMESPACE_LIST * get_neuronRoboticsDyIONamespace(){
	if(!namespcaedAdded){
                //GET
                //Add the RPC structs to the namespace
                addRpcToNamespace(&neuronRoboticsDyIO,& neuronRoboticsDyIO__rev_g);
                addRpcToNamespace(&neuronRoboticsDyIO,& neuronRoboticsDyIO__pwr_g);
                addRpcToNamespace(&neuronRoboticsDyIO,& neuronRoboticsDyIO_info_g);

                addRpcToNamespace(&neuronRoboticsDyIO,& neuronRoboticsDyIO__mac_c);
				addRpcToNamespace(&neuronRoboticsDyIO,& neuronRoboticsDyIO__pwr_c);
				addRpcToNamespace(&neuronRoboticsDyIO,& neuronRoboticsDyIO_info_c);

                namespcaedAdded =TRUE;
	}

	return &neuronRoboticsDyIO;//Return pointer to the struct
}
