/*
 * SPI.c
 *
 *  Created on: Apr 4, 2010
 *      Author: hephaestus
 */
#include "UserApp.h"


static uint8_t privateSerialRX[20];
static uint8_t privateSerialTX[20];
static BYTE_FIFO_STORAGE storeRx;
static BYTE_FIFO_STORAGE storeTx;
static BYTE SSPin=0;
static boolean HardwareInitialized=false;

void InitSPIDyIO(void){
	if(HardwareInitialized == true)
		return;
	HardwareInitialized = true;
	println_W("Initializing the SPI perpheral");
	mPORTGOpenDrainOpen(BIT_6);// Clock is output
	mPORTGOpenDrainOpen(BIT_8);// Data Out is an output
	SPI_SCK_IO=1;
	SPI_SDO_IO=1;
	OpenSPI2(SPI_MODE8_ON|ENABLE_SDO_PIN|SLAVE_ENABLE_OFF|SPI_CKE_ON|MASTER_ENABLE_ON|SEC_PRESCAL_8_1|PRI_PRESCAL_64_1, SPI_ENABLE);
	SetCoProcMode(0,IS_SPI_SCK);
	SetCoProcMode(1,IS_SPI_MISO);
	SetCoProcMode(2,IS_SPI_MOSI);
	InitByteFifo(&storeRx,privateSerialRX,sizeof(privateSerialRX));
	InitByteFifo(&storeTx,privateSerialTX,sizeof(privateSerialTX));
}

boolean LoadSPITxData(uint8_t numValues,uint8_t * data){
	int i;
	uint8_t err;
	SSPin = data[0];
	for(i=0;i<numValues;i++){
		FifoAddByte(&storeTx,data[i+1],&err);
	}
	return true;
}

uint8_t GetSPIRxData(uint8_t * data){
	//int i;
	//uint8_t err;
	uint8_t numValues = FifoGetByteCount(&storeRx);
	if(numValues>0)
		numValues = FifoGetByteStream(&storeRx,data,numValues);
	return numValues;
}

void StopDyIOSPI(uint8_t pin){
	if (isSPI(GetChannelMode(pin))){
		CloseSPI2();
		_RG6=1;
		_RG8=1;
		SDI_TRIS=INPUT;
		SDO_TRIS=INPUT;
		SCK_TRIS=INPUT;
		println_I("Clearing up SPI perpheral");
		SetCoProcMode(0,IS_DI);
		SetCoProcMode(1,IS_DI);
		SetCoProcMode(2,IS_DI);
		HardwareInitialized = false;
	}
}
boolean isSPI(uint8_t mode){
	switch(mode){
	case IS_SPI_MOSI:
	case IS_SPI_MISO:
	case IS_SPI_SCK:
		return true; 
	}
	return false; 
}

uint8_t GetByteSPIDyIO(uint8_t b){
	//InitSPIDyIO();
	putcSPI2(b);	// Start sending
	return getcSPI2();
}

void SyncSPIData(){
	if(SSPin<3 || FifoGetByteCount(&storeTx)==0){
		return;
	}
	println_W("SPI Sync");
	if(!SetCoProcMode(SSPin,IS_DO))
		SetChannelValueCoProc(SSPin,1);
	SetChannelValueCoProc(SSPin,0);
	uint8_t i,err;
	while(FifoGetByteCount(&storeTx)>0){

		FifoAddByte(&storeRx,GetByteSPIDyIO(FifoGetByte(&storeTx,&err)),&err) ;
	}
	SetChannelValueCoProc(SSPin,1);
	SSPin=0;
}


//void SendPacketToSPI(BowlerPacket * Packet){
//	if(!isSPI(GetChannelMode(Packet->use.data[0]))){
//		println_I("channel is not SPI");
//		return;
//	}
//	SendPacketToSPIFromArray(Packet->use.head.DataLegnth-6,Packet->use.data+1);
//}
