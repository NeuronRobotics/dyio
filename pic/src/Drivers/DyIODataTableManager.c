#include "UserApp.h"

static uint8_t privateSerialRX[BOWLER_PacketSize];
static uint8_t privateSerialTX[BOWLER_PacketSize];
static BYTE_FIFO_STORAGE storeRx;
static BYTE_FIFO_STORAGE storeTx;
//static BowlerPacket dataTableSync;

void InitializeDyIODataTableManager(){
	InitByteFifo(&storeRx,privateSerialRX,BOWLER_PacketSize);
	InitByteFifo(&storeTx,privateSerialTX,BOWLER_PacketSize);

}
RunEveryData printData = {0,10000};
void SyncDataTable(){
	PushCoProcAsync();
	SetAllCoProcMode();
	SetAllCoProcValues();
	DownstreamPowerChange();
	if(RunEvery(&printData)>0){
//		println_I("Data Table:");
//		printValues();
//		printModes();
		//printConfigurations();
		//printAsync();
	}

}

void SetNewConfigurationDataTable(uint8_t pin, int32_t value){

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
