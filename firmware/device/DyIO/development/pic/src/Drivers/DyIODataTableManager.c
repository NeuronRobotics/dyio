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

void SyncDataTable(){

}

BOOL LoadSerialTxData(BYTE numValues,INT32 * data){
	int i;
	BYTE err;
	for(i=0;i<numValues;i++){
		FifoAddByte(&storeTx,data[i],&err);
	}
	return TRUE;
}

