/**
 * @file AbstractPID.c
 *
 * Created on: Apr 9, 2010
 * @author Kevin Harrington
 */


#include "Bowler/AbstractPID.h"
#include "Bowler/Debug.h"
#include "Bowler/Defines.h"
//#include "ReplicatorHeader.h"

void FixPacket(BowlerPacket * Packet);
//float lastPacketTime[16];
//INT32 lastPacketVal[16];

int number_of_pid_groups = 0;
AbsPID * pidGroups;
float (*getPosition)(int);
void (*setOutput)(int, float);
int (*resetPosition)(int,int);
void (*onPidConfigure)(int);
void (*MathCalculationPosition)(AbsPID * ,float );
void (*MathCalculationVelocity)(AbsPID * ,float );
PidLimitEvent* (*checkPIDLimitEvents)(BYTE group);


PD_VEL * velData;
//static BowlerPacket packetTemp;

float getMs();

void updatePidAsync();
void pidReset(BYTE chan,INT32 val);
float pidResetNoStop(BYTE chan,INT32 val);
void pushAllPIDPositions(BowlerPacket *Packet,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet));
void LoadCorePacket(BowlerPacket * Packet);

AbsPID * getPidGroupDataTable(){
	return pidGroups;
}

BOOL isPidEnabled(BYTE i){
    return pidGroups[i].Enabled;
}

void SetPIDEnabled(BYTE index, BOOL enabled){
    pidGroups[index].Enabled=enabled;
}

void SetControllerMath( void (*math)(AbsPID * ,float )){
	if(math !=0)
		MathCalculationPosition=math;
	else
		MathCalculationPosition=&RunAbstractPIDCalc;
}

void InitilizePidController(AbsPID * groups,PD_VEL * vel,int numberOfGroups,
							float (*getPositionPtr)(int),
							void (*setOutputPtr)(int,float),
							int (*resetPositionPtr)(int,int),
							void (*onPidConfigurePtr)(int),
							PidLimitEvent* (*checkPIDLimitEventsPtr)(BYTE group)){
	if(groups ==0||
		vel==0||
		getPositionPtr==0||
		setOutputPtr==0||
		resetPositionPtr==0||
		checkPIDLimitEventsPtr==0||
		onPidConfigurePtr==0){
		//println("Null pointer exception in PID Configure",ERROR_PRINT);
		while(1);
	}
	pidGroups = groups;
	number_of_pid_groups = numberOfGroups;
	getPosition=getPositionPtr;
	setOutput=setOutputPtr;
	resetPosition=resetPositionPtr;
	onPidConfigure=onPidConfigurePtr;
	checkPIDLimitEvents=checkPIDLimitEventsPtr;
	velData=vel;
	SetControllerMath(&RunAbstractPIDCalc);
        int i;

        for(i=0;i<numberOfGroups;i++){
            int enabled = pidGroups[i].Enabled;
            pidReset(i,0);
            pidGroups[i].Enabled = enabled ;
        }
}






void updatePidAsync(BowlerPacket *Packet,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){
	int i;
	int update = FALSE;
	for (i=0;i<number_of_pid_groups;i++){
		if(pidGroups[i].Async){
			if(pidGroups[i].CurrentState != pidGroups[i].lastPushedValue){
				update = TRUE;
			}
		}
	}
	if(update){
		pushAllPIDPositions(Packet,pidAsyncCallbackPtr);
	}
}

void pushAllPIDPositions(BowlerPacket *Packet,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){
	//float time = getMs();
//	for(i=0;i<number_of_pid_groups;i++){
//		pushPID(i,pidGroups[i].CurrentState, time);
//	}
        INT32_UNION PID_Temp;
        LoadCorePacket(Packet);
        Packet->use.head.DataLegnth=5;
        Packet->use.head.RPC = GetRPCValue("apid");
        int i;
        for(i=0;i<number_of_pid_groups;i++){
                PID_Temp.Val=pidGroups[i].CurrentState;
                Packet->use.data[0+(i*4)]=PID_Temp.byte.FB;
                Packet->use.data[1+(i*4)]=PID_Temp.byte.TB;
                Packet->use.data[2+(i*4)]=PID_Temp.byte.SB;
                Packet->use.data[3+(i*4)]=PID_Temp.byte.LB;
                Packet->use.head.DataLegnth+=4;
        }
        Packet->use.head.Method=BOWLER_ASYN;
        FixPacket(Packet);
		if(pidAsyncCallbackPtr!=NULL)
			pidAsyncCallbackPtr(Packet);
}



void pushPIDLimitEvent(BowlerPacket *Packet,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet),PidLimitEvent * event){
	if(event->type == NO_LIMIT){
		return;
	}
	event->latchTickError=0;
	if(event->type == INDEXEVENT){
		if(pidGroups[event->group].useIndexLatch){
			event->latchTickError = event->value-getPosition(event->group);
			event->value = pidGroups[event->group].IndexLatchValue;
			if(pidGroups[event->group].stopOnIndex){
				pidReset(event->group,event->value);
			}else{
				event->value = pidResetNoStop(event->group,event->value);
			}
		}
	}else{
        //println_I("ABSTRACTPID: End stop limit, setting new PID setpoint");
		event->value=GetPIDPosition(event->group);
		event->latchTickError=0;
		event->time = getMs();
		SetPID(event->group,event->value);
	}

	pidGroups[event->group].lastPushedValue=event->value;

	LoadCorePacket(Packet);
	Packet->use.head.MessageID = 0;
	Packet->use.head.Method=BOWLER_ASYN;
	Packet->use.head.RPC = GetRPCValue("pidl");

	Packet->use.data[0]=event->group;
	Packet->use.data[1]=event->type;
	INT32_UNION tmp;
	tmp.Val=event->value;
	Packet->use.data[2]=tmp.byte.FB;
	Packet->use.data[3]=tmp.byte.TB;
	Packet->use.data[4]=tmp.byte.SB;
	Packet->use.data[5]=tmp.byte.LB;
	tmp.Val=event->time;
	Packet->use.data[6]=tmp.byte.FB;
	Packet->use.data[7]=tmp.byte.TB;
	Packet->use.data[8]=tmp.byte.SB;
	Packet->use.data[9]=tmp.byte.LB;

	tmp.Val=event->latchTickError;
	Packet->use.data[10]=tmp.byte.FB;
	Packet->use.data[11]=tmp.byte.TB;
	Packet->use.data[12]=tmp.byte.SB;
	Packet->use.data[13]=tmp.byte.LB;

	Packet->use.head.DataLegnth = 4+1+1+(4*3);

	event->type = NO_LIMIT;
	FixPacket(Packet);
	if(pidAsyncCallbackPtr!=NULL)
		pidAsyncCallbackPtr(Packet);
}

void pushPID(BowlerPacket *Packet,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet),BYTE chan, INT32 value, float time){
	LoadCorePacket(Packet);
	Packet->use.head.Method=BOWLER_ASYN;
	Packet->use.head.MessageID = 0;
	Packet->use.head.RPC = GetRPCValue("_pid");
	Packet->use.head.DataLegnth = 4+1+4+4+4;
	Packet->use.data[0]=chan;
	INT32_UNION tmp;
	tmp.Val=value;
	Packet->use.data[1]=tmp.byte.FB;
	Packet->use.data[2]=tmp.byte.TB;
	Packet->use.data[3]=tmp.byte.SB;
	Packet->use.data[4]=tmp.byte.LB;
	tmp.Val=time;
	Packet->use.data[5]=tmp.byte.FB;
	Packet->use.data[6]=tmp.byte.TB;
	Packet->use.data[7]=tmp.byte.SB;
	Packet->use.data[8]=tmp.byte.LB;

	float diffTime = time-pidGroups[chan].lastPushedValue;
	float diffVal  = value -pidGroups[chan].lastPushedTime;

	tmp.Val = (INT32) (diffVal/diffTime);
	Packet->use.data[9]=tmp.byte.FB;
	Packet->use.data[10]=tmp.byte.TB;
	Packet->use.data[11]=tmp.byte.SB;
	Packet->use.data[12]=tmp.byte.LB;

	
    FixPacket(Packet);
    if(pidAsyncCallbackPtr !=NULL){
    	if(pidAsyncCallbackPtr(Packet)){
            pidGroups[chan].lastPushedValue =value;
            pidGroups[chan].lastPushedTime=time;
        }
    }
}


void RunPDVel(BYTE chan){
	if(velData[chan].enabled==TRUE){
		pidGroups[chan].CurrentState = getPosition(chan);
		float currentTime = getMs();
		float timeMsDiff =  (currentTime -velData[chan].lastTime);
		float timeDiff =  timeMsDiff/1000;
		int posDiff=pidGroups[chan].CurrentState -velData[chan].lastPosition;
		float currentVelocity = posDiff/timeDiff;
		//float velocityDiff = currentVelocity-velData[chan].lastVelocity;
		float velocityDiff=0;
		float proportional =  currentVelocity-velData[chan].unitsPerSeCond;
		float set = (velData[chan].currentOutputVel+(proportional*velData[chan].K.P)+(velocityDiff*velData[chan].K.D))/-10;
		velData[chan].currentOutputVel+=set;

		if (velData[chan].currentOutputVel>100)
			velData[chan].currentOutputVel=100;
		if(velData[chan].currentOutputVel<-100)
			velData[chan].currentOutputVel=-100;

//		println("Velocity set=",INFO_PRINT);p_fl(velData[chan].unitsPerSeCond,INFO_PRINT);print(" ticks/seCond",INFO_PRINT);
//		println("Velocity position diff=",INFO_PRINT);p_int(posDiff,INFO_PRINT);print(" ticks",INFO_PRINT);
//		println("Velocity time diff=",INFO_PRINT);p_fl(timeDiff,INFO_PRINT);print(" seConds",INFO_PRINT);
//		println("Velocity time diff=",INFO_PRINT);p_fl(timeMsDiff,INFO_PRINT);print(" ms",INFO_PRINT);
//		println("Velocity current=",INFO_PRINT);p_fl(currentVelocity,INFO_PRINT);print(" ticks/seCond",INFO_PRINT);
//		println("Velocity offset=",INFO_PRINT);p_fl(set,INFO_PRINT);print("\n",INFO_PRINT);
//		println("Velocity set=",INFO_PRINT);p_fl(velData[chan].currentOutputVel,INFO_PRINT);print("\n",INFO_PRINT);

		pidGroups[chan].Output=velData[chan].currentOutputVel;

		setOutput(chan,pidGroups[chan].Output);

		//cleanup
		velData[chan].lastPosition=pidGroups[chan].CurrentState;
		velData[chan].lastVelocity=currentVelocity;
		velData[chan].lastTime=currentTime;
	}
}

void StartPDVel(BYTE chan,INT32 unitsPerSeCond,float ms){

        if(ms<.1){
            println_I("Starting Velocity");
            velData[chan].enabled=TRUE;
            pidGroups[chan].Enabled=FALSE;
            velData[chan].lastPosition=GetPIDPosition(chan);
            velData[chan].lastTime=getMs();
            velData[chan].unitsPerSeCond=unitsPerSeCond;
            velData[chan].currentOutputVel =0;
        }else{
            println_I("Starting Velocity Timed");
            float seConds = ms/1000;
            INT32 dist = (INT32)unitsPerSeCond*(INT32)seConds;
            INT32 delt = ((INT32) (GetPIDPosition(chan))-dist);
            SetPIDTimed(chan, delt, ms);
        }
	

}

void GetConfigPDVelocity(BowlerPacket * Packet){
	BYTE chan = Packet->use.data[0];
	INT32_UNION PID_K;
	PID_K.Val=velData[chan].K.P*100;
	Packet->use.data[1]=PID_K.byte.FB;//=Packet->use.data[4];
	Packet->use.data[2]=PID_K.byte.TB;//Packet->use.data[5];
	Packet->use.data[3]=PID_K.byte.SB;//Packet->use.data[6];
	Packet->use.data[4]=PID_K.byte.LB;//Packet->use.data[7];

	PID_K.Val=velData[chan].K.D*100;
	Packet->use.data[5]=PID_K.byte.FB;//Packet->use.data[8];
	Packet->use.data[6]=PID_K.byte.TB;//Packet->use.data[9];
	Packet->use.data[7]=PID_K.byte.SB;//Packet->use.data[10];
	Packet->use.data[8]=PID_K.byte.LB;//Packet->use.data[11];


	Packet->use.head.DataLegnth=4+9;
	Packet->use.head.Method=BOWLER_POST;

}

BYTE ConfigPDVelovity(BowlerPacket * Packet){
	BYTE chan = Packet->use.data[0];

	float KP=0;
	float KD=0;
	INT32_UNION PID_K;

	PID_K.byte.FB=Packet->use.data[1];
	PID_K.byte.TB=Packet->use.data[2];
	PID_K.byte.SB=Packet->use.data[3];
	PID_K.byte.LB=Packet->use.data[4];
	KP=(float)PID_K.Val;

	PID_K.byte.FB=Packet->use.data[5];
	PID_K.byte.TB=Packet->use.data[6];
	PID_K.byte.SB=Packet->use.data[7];
	PID_K.byte.LB=Packet->use.data[8];
	KD=(float)PID_K.Val;



	velData[chan].K.P=KP/100;
	velData[chan].K.D=KD/100;


	onPidConfigure(chan);

	return TRUE;
}


void GetConfigPID(BowlerPacket * Packet){
	BYTE chan = Packet->use.data[0];
	Packet->use.data[1]=pidGroups[chan].Enabled;//  = ((Packet->use.data[1]==0)?0:1);
	Packet->use.data[2]=pidGroups[chan].Polarity;// = ((Packet->use.data[2]==0)?0:1);
	Packet->use.data[3]=pidGroups[chan].Async;//= ((Packet->use.data[3]==0)?0:1);

	INT32_UNION PID_K;
	PID_K.Val=pidGroups[chan].K.P*100;
	Packet->use.data[4]=PID_K.byte.FB;//=Packet->use.data[4];
	Packet->use.data[5]=PID_K.byte.TB;//Packet->use.data[5];
	Packet->use.data[6]=PID_K.byte.SB;//Packet->use.data[6];
	Packet->use.data[7]=PID_K.byte.LB;//Packet->use.data[7];

	PID_K.Val=pidGroups[chan].K.I*100;
	Packet->use.data[8]=PID_K.byte.FB;//Packet->use.data[8];
	Packet->use.data[9]=PID_K.byte.TB;//Packet->use.data[9];
	Packet->use.data[10]=PID_K.byte.SB;//Packet->use.data[10];
	Packet->use.data[11]=PID_K.byte.LB;//Packet->use.data[11];

	PID_K.Val=pidGroups[chan].K.D*100;
	Packet->use.data[12]=PID_K.byte.FB;//Packet->use.data[12];
	Packet->use.data[13]=PID_K.byte.TB;//Packet->use.data[13];
	Packet->use.data[14]=PID_K.byte.SB;//Packet->use.data[14];
	Packet->use.data[15]=PID_K.byte.LB;//Packet->use.data[15];

	PID_K.Val=pidGroups[chan].IndexLatchValue;
	Packet->use.data[16]=PID_K.byte.FB;//Packet->use.data[12];
	Packet->use.data[17]=PID_K.byte.TB;//Packet->use.data[13];
	Packet->use.data[18]=PID_K.byte.SB;//Packet->use.data[14];
	Packet->use.data[19]=PID_K.byte.LB;//Packet->use.data[15]
	//latching data
	Packet->use.data[20]=pidGroups[chan].useIndexLatch;//
	Packet->use.data[21]=pidGroups[chan].stopOnIndex;//


	Packet->use.head.DataLegnth=4+22;
	Packet->use.head.Method=BOWLER_POST;

}

BYTE ConfigPID(BowlerPacket * Packet){
	BYTE chan = Packet->use.data[0];

	pidGroups[chan].Polarity = ((Packet->use.data[2]==0)?0:1);
	pidGroups[chan].Async    = ((Packet->use.data[3]==0)?0:1);


	float KP=0;
	float KI=0;
	float KD=0;
	INT32_UNION PID_K;

	PID_K.byte.FB=Packet->use.data[4];
	PID_K.byte.TB=Packet->use.data[5];
	PID_K.byte.SB=Packet->use.data[6];
	PID_K.byte.LB=Packet->use.data[7];
	KP=(float)PID_K.Val;

	PID_K.byte.FB=Packet->use.data[8];
	PID_K.byte.TB=Packet->use.data[9];
	PID_K.byte.SB=Packet->use.data[10];
	PID_K.byte.LB=Packet->use.data[11];
	KI=(float)PID_K.Val;

	PID_K.byte.FB=Packet->use.data[12];
	PID_K.byte.TB=Packet->use.data[13];
	PID_K.byte.SB=Packet->use.data[14];
	PID_K.byte.LB=Packet->use.data[15];
	KD=(float)PID_K.Val;

	if(Packet->use.head.DataLegnth>(4+16)){
		PID_K.byte.FB=Packet->use.data[16];
		PID_K.byte.TB=Packet->use.data[17];
		PID_K.byte.SB=Packet->use.data[18];
		PID_K.byte.LB=Packet->use.data[19];

		pidGroups[chan].useIndexLatch= Packet->use.data[20];
		pidGroups[chan].stopOnIndex = Packet->use.data[21];
	}else{
		PID_K.Val=0;
		pidGroups[chan].useIndexLatch= TRUE;
		pidGroups[chan].stopOnIndex = TRUE;
	}
	pidGroups[chan].IndexLatchValue=(float)PID_K.Val;


	pidGroups[chan].K.P=KP/100;
	pidGroups[chan].K.I=KI/100;
	pidGroups[chan].K.D=KD/100;
	//println("Resetting PID channel from Config:",INFO_PRINT);printBowlerPacketDEBUG(Packet,INFO_PRINT);
	//println("From Config Current setpoint:",INFO_PRINT);p_fl(pidGroups[chan].SetPoint,INFO_PRINT);
	//pidReset(chan, pidGroups[chan].SetPoint);

	//pidGroups[chan].Enabled=TRUE;//Ensures output enabled to stop motors
	//pidGroups[chan].Output=0;
	//setOutput(chan,pidGroups[chan].Output);


	//velData[chan].enabled=FALSE;

	onPidConfigure(chan);

	pidGroups[chan].Enabled  = ((Packet->use.data[1]==0)?0:1);
//	if(local_groups[chan].Enabled)
//		fail();
	return TRUE;
}


BYTE ZeroPID(BYTE chan){
	//println("Resetting PID channel from zeroPID:",INFO_PRINT);
	pidReset(chan,0);
	return TRUE;
}

BYTE ClearPID(BYTE chan){
	if (chan>=number_of_pid_groups)
		return FALSE;
	pidGroups[chan].Enabled=FALSE;
	return TRUE;
}

BYTE SetPIDTimed(BYTE chan,INT32 val,float ms){
	//println_I("@#@# PID channel Set chan=");p_int_I(chan);print_I(" setpoint=");p_int_I(val);print_I(" time=");p_fl_I(ms);
	if (chan>=number_of_pid_groups)
		return FALSE;
	if(ms<.01)
		ms=0;
	//local_groups[chan].Enabled=TRUE;
	pidGroups[chan].interpolate.set=(float)val;
	pidGroups[chan].interpolate.setTime=ms;
	pidGroups[chan].interpolate.start=pidGroups[chan].SetPoint;
	pidGroups[chan].interpolate.startTime=getMs();
	if(ms==0)
		pidGroups[chan].SetPoint=(float)val;
	//pidGroups[chan].Enabled=TRUE;
        pidGroups[chan].Async = TRUE;
	velData[chan].enabled=FALSE;
	InitAbsPIDWithPosition(&pidGroups[chan],pidGroups[chan].K.P,pidGroups[chan].K.I,pidGroups[chan].K.D, getMs(),val);
	return TRUE;
}
BYTE SetPID(BYTE chan,INT32 val){
	SetPIDTimed(chan, val,0);
	return TRUE;
}

int GetPIDPosition(BYTE chan){
	if (chan>=number_of_pid_groups)
		return 0;
	//pidGroups[chan].CurrentState=(int)getPosition(chan);
	return pidGroups[chan].CurrentState;
}

/**
 * END PD velocity code
 */

static INT32_UNION PID_Temp;
static float time;
static int val,chan;
int zone = 66;
BOOL processPIDGet(BowlerPacket * Packet){
	int i;
	switch (Packet->use.head.RPC){
	case APID:
		Packet->use.head.DataLegnth=5;
		Packet->use.data[0]=number_of_pid_groups;
		for(i=0;i<number_of_pid_groups;i++){
			PID_Temp.Val=GetPIDPosition(i);
			Packet->use.data[1+(i*4)]=PID_Temp.byte.FB;
			Packet->use.data[2+(i*4)]=PID_Temp.byte.TB;
			Packet->use.data[3+(i*4)]=PID_Temp.byte.SB;
			Packet->use.data[4+(i*4)]=PID_Temp.byte.LB;
			Packet->use.head.DataLegnth+=4;
		}
		Packet->use.head.Method=BOWLER_POST;
		break;
	case _PID:
		PID_Temp.Val=GetPIDPosition(Packet->use.data[0]);
		Packet->use.data[1]=PID_Temp.byte.FB;
		Packet->use.data[2]=PID_Temp.byte.TB;
		Packet->use.data[3]=PID_Temp.byte.SB;
		Packet->use.data[4]=PID_Temp.byte.LB;
		Packet->use.head.DataLegnth=4+1+4;
		Packet->use.head.Method=BOWLER_POST;
		break;
	case CPID:
		GetConfigPID(Packet);
		break;
	case CPDV:
		GetConfigPDVelocity(Packet);
		break;
	case GPDC:
		PID_Temp.Val=number_of_pid_groups;
		Packet->use.data[0]=PID_Temp.byte.FB;
		Packet->use.data[1]=PID_Temp.byte.TB;
		Packet->use.data[2]=PID_Temp.byte.SB;
		Packet->use.data[3]=PID_Temp.byte.LB;
		Packet->use.head.DataLegnth=4+4;
		Packet->use.head.Method=BOWLER_POST;
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL processPIDPost(BowlerPacket * Packet){
	switch (Packet->use.head.RPC){
	case APID:
		PID_Temp.byte.FB=Packet->use.data[0];
		PID_Temp.byte.TB=Packet->use.data[1];
		PID_Temp.byte.SB=Packet->use.data[2];
		PID_Temp.byte.LB=Packet->use.data[3];
		time = (float)PID_Temp.Val;
		BYTE i=0;
		for(i=0;i<Packet->use.data[4];i++){
			PID_Temp.byte.FB=Packet->use.data[5+(i*4)];
			PID_Temp.byte.TB=Packet->use.data[6+(i*4)];
			PID_Temp.byte.SB=Packet->use.data[7+(i*4)];
			PID_Temp.byte.LB=Packet->use.data[8+(i*4)];
			val=PID_Temp.Val;
			SetPIDTimed(i,val,time);
		}
		READY(Packet,zone,3);
		break;
	case _VPD:
		chan = Packet->use.data[0];
		PID_Temp.byte.FB=Packet->use.data[1];
		PID_Temp.byte.TB=Packet->use.data[2];
		PID_Temp.byte.SB=Packet->use.data[3];
		PID_Temp.byte.LB=Packet->use.data[4];
		val = PID_Temp.Val;
		PID_Temp.byte.FB=Packet->use.data[5];
		PID_Temp.byte.TB=Packet->use.data[6];
		PID_Temp.byte.SB=Packet->use.data[7];
		PID_Temp.byte.LB=Packet->use.data[8];
		time=PID_Temp.Val;

		StartPDVel(chan,val,time);

		READY(Packet,zone,4);
		break;
	case _PID:
		chan = Packet->use.data[0];
		PID_Temp.byte.FB=Packet->use.data[1];
		PID_Temp.byte.TB=Packet->use.data[2];
		PID_Temp.byte.SB=Packet->use.data[3];
		PID_Temp.byte.LB=Packet->use.data[4];
		val = PID_Temp.Val;
		PID_Temp.byte.FB=Packet->use.data[5];
		PID_Temp.byte.TB=Packet->use.data[6];
		PID_Temp.byte.SB=Packet->use.data[7];
		PID_Temp.byte.LB=Packet->use.data[8];
		time=PID_Temp.Val;
		SetPIDTimed(chan,val,time);
		READY(Packet,zone,5);
		break;
	case RPID:
		chan = Packet->use.data[0];
		PID_Temp.byte.FB=Packet->use.data[1];
		PID_Temp.byte.TB=Packet->use.data[2];
		PID_Temp.byte.SB=Packet->use.data[3];
		PID_Temp.byte.LB=Packet->use.data[4];
		println("Resetting PID channel from packet:",INFO_PRINT);printBowlerPacketDEBUG(Packet,INFO_PRINT);
		pidReset(chan, PID_Temp.Val);
		READY(Packet,zone,6);
		break;
        default:
		return FALSE;
	}
	return TRUE;
}
BOOL processPIDCrit(BowlerPacket * Packet){
	BYTE i=0;
	switch (Packet->use.head.RPC){
	case KPID:
		for(i=0;i<number_of_pid_groups;i++){
			pidGroups[i].Enabled = TRUE;
			setOutput(i,0.0);
			pidGroups[i].Enabled = FALSE;
			velData[i].enabled=FALSE;
			pidGroups[i].Output=0.0;
		}
		READY(Packet,zone,0);
		break;
	case CPID:
		if(ConfigPID(Packet)){
			READY(Packet,zone,1);
		}else
			ERR(Packet,zone,1);
		break;
	case CPDV:
		if(ConfigPDVelovity(Packet)){
			READY(Packet,zone,1);
		}else
			ERR(Packet,zone,1);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
/**
 * Handle a PID packet.
 * @return True if the packet was processed, False if it was not  PID packet
 */
BOOL ProcessPIDPacket(BowlerPacket * Packet){
	switch(Packet->use.head.Method){
	case BOWLER_GET:
		return processPIDGet(Packet);
	case BOWLER_POST:
		return processPIDPost(Packet);
	case BOWLER_CRIT:
		return processPIDCrit(Packet);
	default:
		return FALSE;
	}
}

float pidResetNoStop(BYTE chan,INT32 val){
	float value = (float)resetPosition(chan,val);
	//println("From pidReset 1 Current setpoint:");p_fl(local_groups[chan].SetPoint); print(" Target value:");p_fl(value);
	float time = getMs();
	pidGroups[chan].channel=chan;
	pidGroups[chan].lastPushedValue=value;
	InitAbsPIDWithPosition(&pidGroups[chan],pidGroups[chan].K.P,pidGroups[chan].K.I,pidGroups[chan].K.D, time,value );
	velData[chan].lastPosition=val;
	velData[chan].lastTime=time;
	return value;
}

void pidReset(BYTE chan,INT32 val){
	float value = pidResetNoStop(chan,val);
	pidGroups[chan].interpolate.set=value;
	pidGroups[chan].interpolate.setTime=0;
	pidGroups[chan].interpolate.start=value;
	pidGroups[chan].interpolate.startTime=time;
	pidGroups[chan].SetPoint=value;
	pidGroups[chan].Enabled=TRUE;//Ensures output enabled to stop motors
	pidGroups[chan].Output=0.0;
	setOutput(chan,pidGroups[chan].Output);
	velData[chan].enabled=FALSE;
}






void InitAbsPID(AbsPID * state,float KP,float KI,float KD,float time){
	InitAbsPIDWithPosition(state,KP, KI, KD,time,0);
}

void setPIDConstants(int group,float p,float i,float d){
    pidGroups[group].K.P=p;
    pidGroups[group].K.I=i;
    pidGroups[group].K.D=d;
}

/**
 * RunAbstractPIDCalc
 * @param state A pointer to the AbsPID struct to run the calculations on
 * @param CurrentTime a float of the time it is called in MS for use by the PID calculation
 */
void InitAbsPIDWithPosition(AbsPID * state,float KP,float KI,float KD,float time,float currentPosition){
	state->K.P=KP;
	state->K.I=KI;
	state->K.D=KD;
	//state->integralCircularBufferIndex = 0;
	state->integralTotal = 0.0;
        state->integralSize  = 10.0;
	state->SetPoint = currentPosition;
        state->interpolate.set=state->SetPoint;
	state->PreviousError=0;
	state->Output=0.0;
	state->PreviousTime=time;
}

void RunVel(void){
	BYTE i;
	for (i=0;i<number_of_pid_groups;i++){
		if(!pidGroups[i].Enabled){
			RunPDVel(i);
		}
	}
}

BOOL isPIDInterpolating(int index){
    return pidGroups[index].interpolate.setTime != 0;
}

BOOL isPIDArrivedAtSetpoint(int index, float plusOrMinus){
    return bound( pidGroups[index].SetPoint,
                    pidGroups[index].CurrentState,
                    plusOrMinus,
                    plusOrMinus);
}

void RunPIDControl(){
    	int i;
	for (i=0;i<number_of_pid_groups;i++){
            if(pidGroups[i].Enabled){
                pidGroups[i].CurrentState = getPosition(i);
                pidGroups[i].SetPoint = interpolate((INTERPOLATE_DATA *)&pidGroups[i].interpolate,getMs());
                MathCalculationPosition(& pidGroups[i],getMs());
                setOutput(i,pidGroups[i].Output);
            }

	}
}
void RunPIDComs(BowlerPacket *Packet,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){
    int i;
	for (i=0;i<number_of_pid_groups;i++){
            pushPIDLimitEvent(Packet,pidAsyncCallbackPtr,checkPIDLimitEvents(i));
	}
	updatePidAsync(Packet,pidAsyncCallbackPtr);
}

void RunPID(BowlerPacket *Packet,BOOL (*pidAsyncCallbackPtr)(BowlerPacket *Packet)){
    RunPIDControl();
    RunPIDComs(Packet,pidAsyncCallbackPtr);
}

/**
 * InitAbsPID
 * @param state A pointer to the AbsPID the initialize
 * @param KP the Proportional Constant
 * @param KI the Integral Constant
 * @param KD the Derivative Constant
 * @param time the starting time
 */

void RunAbstractPIDCalc(AbsPID * state,float CurrentTime){
	float error;
	float derivative;
	//calculate set error
	error = state->SetPoint- state->CurrentState;

	//remove the value that is INTEGRALSIZE cycles old from the integral calculation to avoid overflow
	//state->integralTotal -= state->IntegralCircularBuffer[state->integralCircularBufferIndex];
	//add the latest value to the integral
	state->integralTotal =  (error*(1.0/state->integralSize)) +
                                (state->integralTotal*((state->integralSize-1.0)/state->integralSize));
	
        //This section clears the integral buffer when the zero is crossed
        if((state->PreviousError>=0 && error<0)||
            (state->PreviousError<0 && error>=0)    ){
            
        }


        //calculate the derivative
        derivative = (error-state->PreviousError);// / ((CurrentTime-state->PreviousTime));
        state->PreviousError=error;
	 
	//do the PID calculation
	state->Output = (   (state->K.P*error) +
                            (state->K.D*derivative) +
                            (state->K.I*state->integralTotal)
                        );

        if(!state->Polarity)
            state->Output *=-1.0;
	//Store the current time for next iterations previous time
	state->PreviousTime=CurrentTime;

}


