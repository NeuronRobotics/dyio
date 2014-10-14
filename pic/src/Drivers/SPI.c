/*
 * SPI.c
 *
 *  Created on: Apr 4, 2010
 *      Author: hephaestus
 */
#include "UserApp.h"


void InitSPIDyIO(void){
	println_I("Initializing the SPI perpheral");
	mPORTGOpenDrainOpen(BIT_6);// Clock is output
	mPORTGOpenDrainOpen(BIT_8);// Data Out is an output
	SPI_SCK_IO=1;
	SPI_SDO_IO=1;
	OpenSPI2(SPI_MODE8_ON|ENABLE_SDO_PIN|SLAVE_ENABLE_OFF|SPI_CKE_ON|MASTER_ENABLE_ON|SEC_PRESCAL_8_1|PRI_PRESCAL_64_1, SPI_ENABLE);
	println_I("Setting up SPI perpheral");
	SetCoProcMode(0,IS_SPI_SCK);
	SetCoProcMode(1,IS_SPI_MISO);
	SetCoProcMode(2,IS_SPI_MOSI);
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
	InitSPIDyIO();
	putcSPI2(b);	// Start sending
	return getcSPI2();
}

void SendPacketToSPIFromArray(uint8_t numBytes,uint8_t * data){
	uint8_t ss = data[0];
	if(ss<3){
		println_I("invalid SS pin");
		return;
	}
	if(!SetCoProcMode(ss,IS_DO))
		SetChannelValueCoProc(ss,1);
	SetChannelValueCoProc(ss,0);
	uint8_t i;
	for (i=0;i<numBytes;i++){
		data[i+1]=GetByteSPIDyIO(data[i+1]);
	}
	SetChannelValueCoProc(ss,1);
}


void SendPacketToSPI(BowlerPacket * Packet){
	if(!isSPI(GetChannelMode(Packet->use.data[0]))){
		println_I("channel is not SPI");
		return;
	}
	SendPacketToSPIFromArray(Packet->use.head.DataLegnth-6,Packet->use.data+1);
}
