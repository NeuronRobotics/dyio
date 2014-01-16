#include "UserApp.h"

static BYTE privateSerialRX[BOWLER_PacketSize];
static BYTE privateSerialTX[BOWLER_PacketSize];
static BYTE_FIFO_STORAGE storeRx;
static BYTE_FIFO_STORAGE storeTx;
static BowlerPacket dataTableSync;

void InitializeDyIODataTableManager(){
	InitByteFifo(&storeRx,privateSerialRX,BOWLER_PacketSize);
	InitByteFifo(&storeTx,privateSerialTX,BOWLER_PacketSize);

}
RUN_EVERY printData = {0,10000};
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

void SetNewConfigurationDataTable(BYTE pin, INT32 value){

}

BOOL LoadSerialTxData(BYTE numValues,BYTE * data){
	int i;
	BYTE err;
	for(i=0;i<numValues;i++){
		FifoAddByte(&storeTx,data[i],&err);
	}
	return TRUE;
}

BYTE GetSerialRxData(BYTE * data){
	int i;
	BYTE err;
	BYTE numValues = FifoGetByteCount(&storeRx);
	if(numValues>0)
		numValues = FifoGetByteStream(&storeRx,data,numValues);
	return numValues;
}
