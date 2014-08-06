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

BOOL isInit=FALSE;

void initAdvancedAsync(){
	if(isInit == TRUE){
		//println_W("All ready initialized advanced async");
		return;
	}
	println_W("Initializing advanced async");
	isInit=TRUE;
	int i;
	for (i=0;i<GetNumberOfIOChannels();i++){
		startAdvancedAsyncDefault(i);
	}
}

void setAsync(BYTE pin,BOOL async){
	BYTE mode = GetChannelMode(pin);
	getBcsIoDataTable(pin)->PIN.currentChannelMode = mode;
	setAsyncLocal(pin,async);
	startAdvancedAsyncDefault(pin);
}

void setAsyncLocal(BYTE channel,BOOL async){
	getBcsIoDataTable(channel)->PIN.asyncDataenabled=async;
}

BOOL IsAsync(BYTE channel){
	if (getBcsIoDataTable(channel)->PIN.asyncDataenabled){
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
		print_I("UNKNOWN: "); p_int_I(t);return;
	}
}
void configAdvancedAsyncNotEqual(BYTE pin,float time){
	getBcsIoDataTable(pin)->PIN.asyncDataTime.MsTime=getMs();
	getBcsIoDataTable(pin)->PIN.asyncDataTime.setPoint=time;
	getBcsIoDataTable(pin)->PIN.asyncDataType = NOTEQUAL;
}
void configAdvancedAsyncDeadBand(BYTE pin,float time,INT32 deadbandSize){
	getBcsIoDataTable(pin)->PIN.asyncDataTime.MsTime=getMs();
	getBcsIoDataTable(pin)->PIN.asyncDataTime.setPoint=time;
	getBcsIoDataTable(pin)->PIN.asyncDataType = DEADBAND;
	getBcsIoDataTable(pin)->PIN.asyncDatadeadBandval=deadbandSize;
}
void configAdvancedAsyncTreshhold(BYTE pin,float time,INT32 threshholdValue, BYTE edgeType){
	getBcsIoDataTable(pin)->PIN.asyncDataTime.MsTime=getMs();
	getBcsIoDataTable(pin)->PIN.asyncDataTime.setPoint=time;
	getBcsIoDataTable(pin)->PIN.asyncDataType = THRESHHOLD;
	getBcsIoDataTable(pin)->PIN.asyncDatathreshholdval=threshholdValue;
	getBcsIoDataTable(pin)->PIN.asyncDatathreshholdedge=edgeType;
}
void configAdvancedAsyncAutoSample(BYTE pin,float time){
	getBcsIoDataTable(pin)->PIN.asyncDataTime.MsTime=getMs();
	getBcsIoDataTable(pin)->PIN.asyncDataTime.setPoint=time;
	getBcsIoDataTable(pin)->PIN.asyncDataType = AUTOSAMP;
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
	println_I("Starting advanced async on channel: ");p_int_I(pin);
	getBcsIoDataTable(pin)->PIN.asyncDataCurrentVal=1;
	getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal=1;
	getBcsIoDataTable(pin)->PIN.asyncDataTime.MsTime=getMs();
	getBcsIoDataTable(pin)->PIN.asyncDataTime.setPoint=10;
	getBcsIoDataTable(pin)->PIN.asyncDataType = NOTEQUAL;
	print_W(" Mode 0x");prHEX8(GetChannelMode(pin),WARN_PRINT);
	switch(GetChannelMode(pin)){
	case IS_DI:
	case IS_COUNTER_INPUT_HOME:
	case IS_COUNTER_OUTPUT_HOME:
	case IS_SERVO:
		getBcsIoDataTable(pin)->PIN.asyncDataTime.setPoint=5;
		break;
	case IS_ANALOG_IN:
		getBcsIoDataTable(pin)->PIN.asyncDataCurrentVal=ADCINIT;
		getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal=ADCINIT;
		getBcsIoDataTable(pin)->PIN.asyncDataType = DEADBAND;
		getBcsIoDataTable(pin)->PIN.asyncDatadeadBandval=10;
		break;
	}

	//RunEvery(getPinsScheduler( pin));
	println_I("Async OK");
}




void SetValFromAsync(int pin, int value){
	getBcsIoDataTable(pin)->PIN.asyncDataCurrentVal=value;
}

int GetValFromAsync(int pin){
	return getBcsIoDataTable(pin)->PIN.asyncDataCurrentVal;
}

int GetDigitalValFromAsync(BYTE pin){
	initAdvancedAsync();
	if(GetChannelMode(pin)==IS_DI || GetChannelMode(pin)==IS_COUNTER_INPUT_HOME || GetChannelMode(pin)==IS_COUNTER_OUTPUT_HOME ){
		return getBcsIoDataTable(pin)->PIN.asyncDataCurrentVal;
	}
	return 1;
}


BOOL pushAsyncReady( BYTE pin){
	if(!IsAsync(pin)){
		println_I("No asyinc on pin ");p_int_I(pin);print_I(" Mode 0x");prHEX8(GetChannelMode(pin),INFO_PRINT);
		return FALSE;
	}
	println_I("Has async ");p_int_I(pin);print_I(" Mode 0x");prHEX8(GetChannelMode(pin),INFO_PRINT);
	initAdvancedAsync();
	INT32 last;
	INT32 aval;
	INT32 db;
	//int i=pin;
	EndCritical();
	RunEveryData * tRef=getPinsScheduler( pin);
	println_I("Checking timer \nMsTime: ");p_fl_I(tRef->MsTime);
	print_I(" \nSetpoint: ");p_fl_I(tRef->setPoint);
	print_I(" \nCurrentTime: ");p_fl_I(getMs());
	float timeout = RunEvery(tRef);
	print_I(" \nTimeout: ");p_fl_I(timeout);
	if(timeout !=0){
		println_I("Time to do something");
		switch(getBcsIoDataTable(pin)->PIN.asyncDataType&0x0F){
		case AUTOSAMP:
			println_I("Auto samp ");p_int_I(pin);
			getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal = getBcsIoDataTable(pin)->PIN.asyncDataCurrentVal;

			return TRUE;
		case NOTEQUAL:
			//
			if(getBcsIoDataTable(pin)->PIN.asyncDataCurrentVal != getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal){
				println_I("not equ ");p_int_I(pin);
				printfDEBUG_BYTE('\t',INFO_PRINT);
				p_int_I(getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal);
				printfDEBUG_BYTE('\t',INFO_PRINT);
				p_int_I(getBcsIoDataTable(pin)->PIN.asyncDataCurrentVal);
				getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal = getBcsIoDataTable(pin)->PIN.asyncDataCurrentVal;
				return TRUE;
			}
			break;
		case DEADBAND:
			aval = getBcsIoDataTable(pin)->PIN.asyncDataCurrentVal;
			last = getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal;
			db = getBcsIoDataTable(pin)->PIN.asyncDatadeadBandval;
			if (	( 	( last >(aval+db)) ||
						( last <(aval-db)) ) &&
					(aval >=db)
					){
				println_I("deadband");p_int_I(pin);
				getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal=aval;
				return TRUE;
			}
			break;
		case THRESHHOLD:
			println_I("treshhold");p_int_I(pin);
			aval = getBcsIoDataTable(pin)->PIN.asyncDataCurrentVal;
			last = getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal;
			db = getBcsIoDataTable(pin)->PIN.asyncDatathreshholdval;
			getBcsIoDataTable(pin)->PIN.asyncDataPreviousVal = getBcsIoDataTable(pin)->PIN.asyncDataCurrentVal;
			if(getBcsIoDataTable(pin)->PIN.asyncDatathreshholdedge == ASYN_RISING || getBcsIoDataTable(pin)->PIN.asyncDatathreshholdedge == ASYN_BOTH){
				if(last<= db && aval>db){

					return TRUE;
				}
			}
			if(getBcsIoDataTable(pin)->PIN.asyncDatathreshholdedge == ASYN_FALLING|| getBcsIoDataTable(pin)->PIN.asyncDatathreshholdedge == ASYN_BOTH){
				if(last> db && aval<=db){
					return TRUE;
				}
			}
			break;
		default:
			print_I("\nNo type defined!! chan: ");p_int_I(pin);print_I(" mode: ");printMode(GetChannelMode(pin),INFO_PRINT);print_I(" type: ");printAsyncType(getBcsIoDataTable(pin)->PIN.asyncDataType);
			startAdvancedAsyncDefault(pin);
			break;
		}
	}else{
		println_I("Nothing to do, returning");
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
		s.Val= getBcsIoDataTable(i)->PIN.asyncDataCurrentVal;
		Packet->use.data[(i*4)+0]=s.byte.FB;
		Packet->use.data[(i*4)+1]=s.byte.TB;
		Packet->use.data[(i*4)+2]=s.byte.SB;
		Packet->use.data[(i*4)+3]=s.byte.LB;
	}
}


