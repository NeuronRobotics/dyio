#include "UserApp.h"

static uint8_t privateSerialRX[20];
static uint8_t privateSerialTX[20];
static BYTE_FIFO_STORAGE storeRx;
static BYTE_FIFO_STORAGE storeTx;
//BowlerPacket dataTableSync;

boolean brownOutDetect = false;

boolean changedBrownOutDetect = false;

boolean getPowerOverRide(){
	return getBrownOutDetect();
}


boolean getBrownOutDetect(){
	return brownOutDetect;
}

void setBrownOutDetect(boolean b){
	if(brownOutDetect == b)
		return;
	brownOutDetect = b;
	changedBrownOutDetect = true;
	println_W("powerOverRide: ");p_int_W(b);
}

void InitializeDyIODataTableManager(){
	InitByteFifo(&storeRx,privateSerialRX,BOWLER_PacketSize);
	InitByteFifo(&storeTx,privateSerialTX,BOWLER_PacketSize);

}
//RunEveryData printData = {0,10000};
void SyncDataTable(){
	uint8_t err;
	PushCoProcAsync();
	float start = getMs();
	SetAllCoProcMode();
	SetAllCoProcValues();
	DownstreamPowerChange();
	SyncSPIData();
	if(changedBrownOutDetect == true){
		setEEBrownOutDetect(brownOutDetect);
		changedBrownOutDetect = false;
	}
	if( FifoGetByteCount(&storeTx)>0){
		println_E("Stub push serial here: ");
		while(FifoGetByteCount(&storeTx)>0){
			p_int_E(FifoGetByte(&storeTx,&err));
			print_E(" , ");
		}
	}
	if(GetChannelMode(16) == IS_UART_RX && getBcsIoDataTable(16)->PIN.currentValue > 0){
		println_E("Stub pull serial here: ");

	}
    SyncConfigurations();
	float end = getMs() - start;
	if(end > 60){
		println_W("Long Sync time = ");
		p_fl_W(end);
	}

}

boolean LoadSerialTxData(uint8_t numValues,uint8_t * data){
	int i;
	uint8_t err;
	for(i=0;i<numValues;i++){
		FifoAddByte(&storeTx,data[i],&err);
	}
	return true; 
}

uint8_t GetSerialRxData(uint8_t * data){
	//int i;
	//uint8_t err;
	uint8_t numValues = FifoGetByteCount(&storeRx);
	if(numValues>0)
		numValues = FifoGetByteStream(&storeRx,data,numValues);
	return numValues;
}
