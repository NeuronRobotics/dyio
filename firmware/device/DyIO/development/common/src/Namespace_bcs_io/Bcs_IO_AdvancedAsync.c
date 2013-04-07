/**
 * @file Bcs_IO_AdvancedAsync.c
 *
 * Created on: Mar 18, 2013
 * @author hephaestus
 */


#include "Bowler/Bowler.h"
#include "Namespace/AsyncManager.h"
#include "Namespace/Namespace_bcs_io.h"

#define ADCINIT 0xFFFF
#define FASTIO

static BOOL isInit=FALSE;

void initAdvancedAsync(){
	if(isInit == TRUE)
		return;
	isInit=TRUE;
	//println_I((const char*)"Initializing Advanced Async");
	int i;
	for (i=0;i<GetNumberOfIOChannels();i++){
		startAdvancedAsyncDefault(i);
	}
}

void setAsync(BYTE channel,BOOL async){
	BYTE mode = GetChannelMode(channel);
	mode = (async)?mode|0x80:mode;
	getBcsIoDataTable()[channel].PIN.currentChannelMode = mode;
	startAdvancedAsyncDefault(channel);
	setAsyncLocal(channel,async);
}

void setAsyncLocal(BYTE channel,BOOL async){
	getBcsIoDataTable()[channel].asyncData.enabled=async;
}

BOOL IsAsync(BYTE channel){
	if (getBcsIoDataTable()[channel].asyncData.enabled){
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
		print_I((const char*)"AUTOSAMP");return;
	case NOTEQUAL:
		print_I((const char*)"NOTEQUAL");return;
	case DEADBAND:
		print_I((const char*)"DEADBAND");return;
	case THRESHHOLD:
		print_I((const char*)"THRESHHOLD");return;
	default:
		print_I((const char*)"UNKNOWN: "); p_sl_I(t);return;
	}
}
void configAdvancedAsyncNotEqual(BYTE pin,float time){
	getBcsIoDataTable()[pin].asyncData.time.MsTime=getMs();
	getBcsIoDataTable()[pin].asyncData.time.setPoint=time;
	getBcsIoDataTable()[pin].asyncData.type = NOTEQUAL;
}
void configAdvancedAsyncDeadBand(BYTE pin,float time,INT32 deadbandSize){
	getBcsIoDataTable()[pin].asyncData.time.MsTime=getMs();
	getBcsIoDataTable()[pin].asyncData.time.setPoint=time;
	getBcsIoDataTable()[pin].asyncData.type = DEADBAND;
	getBcsIoDataTable()[pin].asyncData.deadBand.val=deadbandSize;
}
void configAdvancedAsyncTreshhold(BYTE pin,float time,INT32 threshholdValue, BYTE edgeType){
	getBcsIoDataTable()[pin].asyncData.time.MsTime=getMs();
	getBcsIoDataTable()[pin].asyncData.time.setPoint=time;
	getBcsIoDataTable()[pin].asyncData.type = THRESHHOLD;
	getBcsIoDataTable()[pin].asyncData.threshhold.val=threshholdValue;
	getBcsIoDataTable()[pin].asyncData.threshhold.edge=edgeType;
}
void configAdvancedAsyncAutoSample(BYTE pin,float time){
	getBcsIoDataTable()[pin].asyncData.time.MsTime=getMs();
	getBcsIoDataTable()[pin].asyncData.time.setPoint=time;
	getBcsIoDataTable()[pin].asyncData.type = AUTOSAMP;
}

BOOL configAdvancedAsync(BowlerPacket * Packet){
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
	return TRUE;
}


void startAdvancedAsyncDefault(BYTE pin){
	//println_I("Starting advanced async on channel: ");p_sl_I(pin);
	getBcsIoDataTable()[pin].asyncData.currentVal=1;
	getBcsIoDataTable()[pin].asyncData.previousVal=1;
	getBcsIoDataTable()[pin].asyncData.time.MsTime=getMs();
	getBcsIoDataTable()[pin].asyncData.time.setPoint=10;
	getBcsIoDataTable()[pin].asyncData.type = NOTEQUAL;
	switch(GetChannelMode(pin)){
	case IS_DI:
	case IS_COUNTER_INPUT_HOME:
	case IS_COUNTER_OUTPUT_HOME:
	case IS_SERVO:
		getBcsIoDataTable()[pin].asyncData.time.setPoint=5;
		break;
	case IS_ANALOG_IN:
		getBcsIoDataTable()[pin].asyncData.currentVal=ADCINIT;
		getBcsIoDataTable()[pin].asyncData.previousVal=ADCINIT;
		getBcsIoDataTable()[pin].asyncData.type = DEADBAND;
		getBcsIoDataTable()[pin].asyncData.deadBand.val=10;
//		getBcsIoDataTable()[pin].asyncData.type = THRESHHOLD;
//		getBcsIoDataTable()[pin].asyncData.threshhold.val=512;
//		getBcsIoDataTable()[pin].asyncData.threshhold.edge=ASYN_RISING;
		break;
	}
	//println_I((const char*)"Async Type set to: ");printAsyncType(getBcsIoDataTable()[pin].asyncData.type); print_I((const char*)"on pin# ");p_ul_I(pin);
}




void SetValFromAsync(int pin, int value){
	getBcsIoDataTable()[pin].asyncData.currentVal=value;
}

int GetValFromAsync(int pin){
	return getBcsIoDataTable()[pin].asyncData.currentVal;
}

int GetDigitalValFromAsync(BYTE pin){
	initAdvancedAsync();
	if(GetChannelMode(pin)==IS_DI || GetChannelMode(pin)==IS_COUNTER_INPUT_HOME || GetChannelMode(pin)==IS_COUNTER_OUTPUT_HOME ){
		return getBcsIoDataTable()[pin].asyncData.currentVal;
	}
	return 1;
}

//int GetAnalogValFromAsync(BYTE pin){
//	initAdvancedAsync();
//	if(pin<8||pin>15){
//		println_E("###Invalid ADC pin! ");
//		p_sl_I(pin);
//		return 0;
//	}
//	if(GetChannelMode(pin)==IS_ANALOG_IN){
//		return getBcsIoDataTable()[pin].asyncData.currentVal;
//	}
//	println_I("Pin not in analog mode: ");
//	//printMode(GetChannelMode(pin),INFO_PRINT);
//	return 0;
//}

BOOL pushAsyncReady( BYTE pin){
	initAdvancedAsync();
	INT32 last;
	INT32 aval;
	INT32 db;
	//int i=pin;

	if(RunEvery(&getBcsIoDataTable()[pin].asyncData.time) !=0){
		//println_I("Time to do something");
		switch(getBcsIoDataTable()[pin].asyncData.type&0x0F){
		case AUTOSAMP:
			//println_I("Auto samp");
			getBcsIoDataTable()[pin].asyncData.previousVal = getBcsIoDataTable()[pin].asyncData.currentVal;
			return TRUE;
		case NOTEQUAL:
			//
			if(getBcsIoDataTable()[pin].asyncData.currentVal != getBcsIoDataTable()[pin].asyncData.previousVal){
				//println_I("not equ");
				getBcsIoDataTable()[pin].asyncData.previousVal = getBcsIoDataTable()[pin].asyncData.currentVal;
				return TRUE;
			}
			break;
		case DEADBAND:
			aval = getBcsIoDataTable()[pin].asyncData.currentVal;
			last = getBcsIoDataTable()[pin].asyncData.previousVal;
			db = getBcsIoDataTable()[pin].asyncData.deadBand.val;
			if (	( 	( last >(aval+db)) ||
						( last <(aval-db)) ) &&
					(aval >=db)
					){
				//println_I("deadband");
				getBcsIoDataTable()[pin].asyncData.previousVal=aval;
				return TRUE;
			}
			break;
		case THRESHHOLD:
			//println_I("treshhold");
			aval = getBcsIoDataTable()[pin].asyncData.currentVal;
			last = getBcsIoDataTable()[pin].asyncData.previousVal;
			db = getBcsIoDataTable()[pin].asyncData.threshhold.val;
			getBcsIoDataTable()[pin].asyncData.previousVal = getBcsIoDataTable()[pin].asyncData.currentVal;
			if(getBcsIoDataTable()[pin].asyncData.threshhold.edge == ASYN_RISING || getBcsIoDataTable()[pin].asyncData.threshhold.edge == ASYN_BOTH){
				if(last<= db && aval>db){

					return TRUE;
				}
			}
			if(getBcsIoDataTable()[pin].asyncData.threshhold.edge == ASYN_FALLING|| getBcsIoDataTable()[pin].asyncData.threshhold.edge == ASYN_BOTH){
				if(last> db && aval<=db){
					return TRUE;
				}
			}
			break;
		default:
			//print_I("\nNo type defined!! chan: ");p_sl_I(pin);print_I(" mode: ");printMode(GetChannelMode(pin),INFO_PRINT);print_I(" type: ");printAsyncType(getBcsIoDataTable()[pin].asyncData.type);
			startAdvancedAsyncDefault(pin);
			break;
		}
	}else{

	}
	return FALSE;
}

void populateGACV(BowlerPacket * Packet){
	INT32_UNION s;
	LoadCorePacket(Packet);
	Packet->use.head.Method=BOWLER_POST;
	Packet->use.head.RPC=GetRPCValue("gacv");
	Packet->use.head.DataLegnth=(GetNumberOfIOChannels()*4)+4;
	Packet->use.head.MessageID=37;
	int i;
	for(i=0;i<GetNumberOfIOChannels();i++){
		s.Val= getBcsIoDataTable()[i].PIN.currentValue;
		Packet->use.data[(i*4)+0]=s.byte.FB;
		Packet->use.data[(i*4)+1]=s.byte.TB;
		Packet->use.data[(i*4)+2]=s.byte.SB;
		Packet->use.data[(i*4)+3]=s.byte.LB;
	}
}


//void runAsyncIO(){
//	Print_Level l = getPrintLevel();
//	//setPrintLevelInfoPrint();
//	initAdvancedAsync();
//	int i;
//	BOOL update=FALSE;
//	for(i=0;i<GetNumberOfIOChannels();i++){
//#if defined(FASTIO)
//			if(ASYN_RDY(i)){
//				update=TRUE;
//			}
//#else
//			switch(GetChannelMode(i)){
//
//			case IS_DI:
//			case IS_COUNTER_INPUT_HOME:
//			case IS_COUNTER_OUTPUT_HOME:
//			case IS_SERVO:
//				//println_I("Pushing digital chan: ");p_sl_I(i);print_I(" value:");p_ul_I(getBcsIoDataTable()[i].asyncData.currentVal);
//				//currentState [i] = GetDigitalValFromAsync(i);
//				if(ASYN_RDY(i)){
//					PushDIval(i,GetDigitalValFromAsync(i));
//				}
//				break;
//			case IS_ANALOG_IN:
//				//println_I("Pushing analog chan: ");p_sl_I(i);print_I(" value:");p_ul_I(getBcsIoDataTable()[i].asyncData.currentVal);
//				//currentState [i] = GetAnalogValFromAsync(i);
//				if(ASYN_RDY(i)){
//					PushADCval(i,GetAnalogValFromAsync(i));
//				}
//				break;
//			case IS_COUNTER_OUTPUT_INT:
//			case IS_COUNTER_INPUT_INT:
//				//println_I("Pushing counter chan: ");p_sl_I(i);print_I(" value:");p_sl_I(getBcsIoDataTable()[i].asyncData.currentVal);
//				//currentState [i] = GetCounterByChannel(i);
//				if(ASYN_RDY(i)){
//					PushCounterChange(i,GetCounterByChannel(i));
//
//				}
//				break;
//#endif
//			}
//	}
//
//	setPrintLevel(l);
//#if defined(FASTIO)
//	if(update){
//		//println_I("Pushing async");
//		PushAllAsync();
//	}
//#endif
//
//}

//void initCounterAsync(BYTE chan,INT32 val){
//	println_I("Setting up Counter Async chan: ");
//	p_sl_I(chan);
//	print_I(" to val: ");
//	p_sl_I(val);
//	getBcsIoDataTable()[getCounterIntChannnel(chan)].asyncData.currentVal=val;
//	getBcsIoDataTable()[getCounterIntChannnel(chan)].asyncData.previousVal=val;
//}



