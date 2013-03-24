/**
 * @file Bcs_IO_AdvancedAsync.c
 *
 * Created on: Mar 18, 2013
 * @author hephaestus
 */


#include "UserApp.h"
#include "Namespace/AsyncManager.h"

#define ADCINIT 0xFFFF


void runAsyncIO();
static BOOL isInit=FALSE;
static AdvancedAsyncData asyncData[NUM_PINS];

#define FASTIO
int currentState [NUM_PINS];
//#define ASYN_RDY(i) ((pushAsyncReady(i)==TRUE)&&(IsAsync(i) == TRUE)&& (GetPIDGroup(i) == NOT_USED_IN_PID))
#define ASYN_RDY(i) ((pushAsyncReady(i)==TRUE)&&(IsAsync(i) == TRUE))
BOOL isAsync[NUM_PINS];

void setAsync(BYTE channel,BOOL async){
	SyncModes();
	BYTE mode = GetChannelMode(channel);
	mode = (async)?mode|0x80:mode;
	DATA[channel].PIN.State = mode;
	SetCoProcMode(channel,mode);
	startAdvancedAsyncDefault(channel);
	setAsyncLocal(channel,async);
}

void setAsyncLocal(BYTE channel,BOOL async){
	isAsync[channel]=async;
}

BOOL IsAsync(BYTE channel){
	if (isAsync[channel]){
		return TRUE;
	}
	BYTE mode=GetChannelMode(channel);
	switch(mode){
	case IS_UART_RX:
	case IS_COUNTER_INPUT_HOME:
	case IS_COUNTER_OUTPUT_HOME:
	case IS_COUNTER_OUTPUT_INT:
	case IS_COUNTER_INPUT_INT:
	case IS_SERVO:
		return TRUE;
	default:
		return FALSE;
	}
}

void printAsyncType(BYTE t){
	switch(t){
	case AUTOSAMP:
		print_I("AUTOSAMP");return;
	case NOTEQUAL:
		print_I("NOTEQUAL");return;
	case DEADBAND:
		print_I("DEADBAND");return;
	case THRESHHOLD:
		print_I("THRESHHOLD");return;
	default:
		print_I("UNKNOWN: "); p_sl_I(t);return;
	}
}
void configAdvancedAsyncNotEqual(BYTE pin,float time){
	asyncData[pin].time.MsTime=getMs();
	asyncData[pin].time.setPoint=time;
	asyncData[pin].type = NOTEQUAL;
}
void configAdvancedAsyncDeadBand(BYTE pin,float time,INT32 deadbandSize){
	asyncData[pin].time.MsTime=getMs();
	asyncData[pin].time.setPoint=time;
	asyncData[pin].type = DEADBAND;
	asyncData[pin].deadBand.val=deadbandSize;
}
void configAdvancedAsyncTreshhold(BYTE pin,float time,INT32 threshholdValue, BYTE edgeType){
	asyncData[pin].time.MsTime=getMs();
	asyncData[pin].time.setPoint=time;
	asyncData[pin].type = THRESHHOLD;
	asyncData[pin].threshhold.val=threshholdValue;
	asyncData[pin].threshhold.edge=edgeType;
}
void configAdvancedAsyncAutoSample(BYTE pin,float time){
	asyncData[pin].time.MsTime=getMs();
	asyncData[pin].time.setPoint=time;
	asyncData[pin].type = AUTOSAMP;
}

void configAdvancedAsync(BowlerPacket * Packet){
	INT32_UNION val;
	INT32_UNION time;
	BYTE pin = Packet->use.data[0];
	BYTE type = Packet->use.data[1];
	time.byte.FB= Packet->use.data[2];
	time.byte.TB= Packet->use.data[3];
	time.byte.SB= Packet->use.data[4];
	time.byte.LB= Packet->use.data[5];
	switch(type){
	case AUTOSAMP:
		configAdvancedAsyncAutoSample(pin,time.Val);
		break;
	case NOTEQUAL:
		configAdvancedAsyncNotEqual(pin,time.Val);
		break;
	case DEADBAND:
		val.byte.FB= Packet->use.data[6];
		val.byte.TB= Packet->use.data[7];
		val.byte.SB= Packet->use.data[8];
		val.byte.LB= Packet->use.data[9];
		configAdvancedAsyncDeadBand(pin,time.Val,val.Val);
		break;
	case THRESHHOLD:
		val.byte.FB= Packet->use.data[6];
		val.byte.TB= Packet->use.data[7];
		val.byte.SB= Packet->use.data[8];
		val.byte.LB= Packet->use.data[9];
		configAdvancedAsyncTreshhold(pin,time.Val,val.Val,Packet->use.data[10]);
		break;
	default:
		ERR(Packet,45,0);
		break;
	}
	setAsync(Packet->use.data[0],TRUE);
	READY(Packet,45,0);
}


void startAdvancedAsyncDefault(BYTE pin){
	//println_I("Starting advanced async on channel: ");p_sl_I(pin);
	asyncData[pin].currentVal=1;
	asyncData[pin].previousVal=1;
	asyncData[pin].time.MsTime=getMs();
	asyncData[pin].time.setPoint=100;
	asyncData[pin].type = NOTEQUAL;
	switch(GetChannelMode(pin)){
	case IS_DI:
	case IS_COUNTER_INPUT_HOME:
	case IS_COUNTER_OUTPUT_HOME:
	case IS_SERVO:
		asyncData[pin].time.setPoint=5;
		break;
	case IS_ANALOG_IN:
		asyncData[pin].currentVal=ADCINIT;
		asyncData[pin].previousVal=ADCINIT;
		asyncData[pin].type = DEADBAND;
		asyncData[pin].deadBand.val=10;
//		asyncData[pin].type = THRESHHOLD;
//		asyncData[pin].threshhold.val=512;
//		asyncData[pin].threshhold.edge=ASYN_RISING;
		break;
	}
	println_I("Async Type set to: ");printAsyncType(asyncData[pin].type);
}

void initAdvancedAsync(){
	if(isInit == TRUE)
		return;
	isInit=TRUE;
	println_I("Initializing Advanced Async");
	int i;
	for (i=0;i<NUM_PINS;i++){
		startAdvancedAsyncDefault(i);
	}
}


void SetValFromAsync(int pin, int value){
	asyncData[pin].currentVal=value;
}

int GetValFromAsync(int pin, int value){
	return asyncData[pin].currentVal;
}

int GetDigitalValFromAsync(BYTE pin){
	initAdvancedAsync();
	if(GetChannelMode(pin)==IS_DI || GetChannelMode(pin)==IS_COUNTER_INPUT_HOME || GetChannelMode(pin)==IS_COUNTER_OUTPUT_HOME || GetChannelMode(pin)==IS_SERVO){
		return asyncData[pin].currentVal;
	}
	return 1;
}

int GetAnalogValFromAsync(BYTE pin){
	initAdvancedAsync();
	if(pin<8||pin>15){
		println_E("###Invalid ADC pin! ");
		p_sl_I(pin);
		return 0;
	}
	if(GetChannelMode(pin)==IS_ANALOG_IN){
		if(asyncData[pin].currentVal==ADCINIT)
			SetValFromAsync( pin, GetADC(pin));
		return asyncData[pin].currentVal;
	}
	println_I("Pin not in analog mode: ");
	printMode(GetChannelMode(pin),INFO_PRINT);
	return 0;
}

BOOL pushAsyncReady( BYTE pin){
	initAdvancedAsync();
	INT32 last;
	INT32 aval;
	INT32 db;
	int i=pin;
	if(GetChannelMode(i)==IS_COUNTER_INPUT_INT || GetChannelMode(i)==IS_COUNTER_OUTPUT_INT){
		asyncData[i].currentVal = GetCounterByChannel(i);
	}
	if(GetChannelMode(i)==IS_ANALOG_IN){
		asyncData[i].currentVal = GetAnalogValFromAsync(i);
	}
	if(RunEvery(&asyncData[pin].time) !=0){
		//println_I("Time to do something");
		switch(asyncData[pin].type&0x0F){
		case AUTOSAMP:
			//println_I("Auto samp");
			asyncData[pin].previousVal = asyncData[pin].currentVal;
			return TRUE;
		case NOTEQUAL:
			//
			if(asyncData[pin].currentVal != asyncData[pin].previousVal){
				//println_I("not equ");
				asyncData[pin].previousVal = asyncData[pin].currentVal;
				return TRUE;
			}
			break;
		case DEADBAND:
			aval = asyncData[pin].currentVal;
			last = asyncData[pin].previousVal;
			db = asyncData[pin].deadBand.val;
			if (	( 	( last >(aval+db)) ||
						( last <(aval-db)) ) &&
					(aval >=db)
					){
				//println_I("deadband");
				asyncData[pin].previousVal=aval;
				return TRUE;
			}
			break;
		case THRESHHOLD:
			//println_I("treshhold");
			aval = asyncData[pin].currentVal;
			last = asyncData[pin].previousVal;
			db = asyncData[pin].threshhold.val;
			asyncData[pin].previousVal = asyncData[pin].currentVal;
			if(asyncData[pin].threshhold.edge == ASYN_RISING || asyncData[pin].threshhold.edge == ASYN_BOTH){
				if(last<= db && aval>db){

					return TRUE;
				}
			}
			if(asyncData[pin].threshhold.edge == ASYN_FALLING|| asyncData[pin].threshhold.edge == ASYN_BOTH){
				if(last> db && aval<=db){
					return TRUE;
				}
			}
			break;
		default:
			print_I("\nNo type defined!! chan: ");p_sl_I(pin);print_I(" mode: ");printMode(GetChannelMode(pin),INFO_PRINT);print_I(" type: ");printAsyncType(asyncData[pin].type);
			startAdvancedAsyncDefault(pin);
			break;
		}
	}else{

	}
	return FALSE;
}


void runAsyncIO(){
	Print_Level l = getPrintLevel();
	setPrintLevelInfoPrint();
	initAdvancedAsync();
	int i;
	BOOL update=FALSE;
	for(i=0;i<NUM_PINS;i++){
			switch(GetChannelMode(i)){
			case IS_DI:
			case IS_COUNTER_INPUT_HOME:
			case IS_COUNTER_OUTPUT_HOME:
			case IS_SERVO:
				//println_I("Pushing digital chan: ");p_sl_I(i);print_I(" value:");p_ul_I(asyncData[i].currentVal);
				currentState [i] = GetDigitalValFromAsync(i);
				if(ASYN_RDY(i)){
#if defined(FASTIO)
					update=TRUE;
#else
					PushDIval(i,GetDigitalValFromAsync(i));
#endif
				}
				break;
			case IS_ANALOG_IN:
				//println_I("Pushing analog chan: ");p_sl_I(i);print_I(" value:");p_ul_I(asyncData[i].currentVal);
				currentState [i] = GetAnalogValFromAsync(i);
				if(ASYN_RDY(i)){
#if defined(FASTIO)
					update=TRUE;
#else
					PushADCval(i,GetAnalogValFromAsync(i));
#endif
				}
				break;
			case IS_COUNTER_OUTPUT_INT:
			case IS_COUNTER_INPUT_INT:
				//println_I("Pushing counter chan: ");p_sl_I(i);print_I(" value:");p_sl_I(asyncData[i].currentVal);
				currentState [i] = GetCounterByChannel(i);
				if(ASYN_RDY(i)){
#if defined(FASTIO)
					update=TRUE;
#else
					PushCounterChange(i,GetCounterByChannel(i));
#endif
				}
				break;

			}
	}

	setPrintLevel(l);
#if defined(FASTIO)
	if(update){
		//println_I("Pushing async");
		PushAllAsync();
	}
#endif

}

void initCounterAsync(BYTE chan,INT32 val){
	println_I("Setting up Counter Async chan: ");
	p_sl_I(chan);
	print_I(" to val: ");
	p_sl_I(val);
	asyncData[getCounterIntChannnel(chan)].currentVal=val;
	asyncData[getCounterIntChannnel(chan)].previousVal=val;
}


void populateGACV(BowlerPacket * Packet){
	INT32_UNION s;
	LoadCorePacket(Packet);
	Packet->use.head.Method=BOWLER_POST;
	Packet->use.head.RPC=GetRPCValue("gacv");
	Packet->use.head.DataLegnth=(NUM_PINS*4)+4;
	Packet->use.head.MessageID=37;
	int i;
	for(i=0;i<NUM_PINS;i++){
		s.Val= currentState[i];
		Packet->use.data[(i*4)+0]=s.byte.FB;
		Packet->use.data[(i*4)+1]=s.byte.TB;
		Packet->use.data[(i*4)+2]=s.byte.SB;
		Packet->use.data[(i*4)+3]=s.byte.LB;
	}
}
