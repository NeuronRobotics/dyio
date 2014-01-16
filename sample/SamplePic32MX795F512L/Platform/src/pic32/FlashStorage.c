/*
 * FlashStorage.c
 *
 *  Created on: Jul 15, 2010
 *      Author: hephaestus
 */
#include "arch/pic32/BowlerConfig.h"
#include "Bowler/Bowler.h"
FLASH_STORE flash;
BYTE  defMac[]  ={0x74,0xf7,0x26,0x00,0x00,0x00} ;

void FlashLoad(void){
	int i;
	for (i=0;i<FLASHSTORE;i++){
		flash.stream[i]=*((UINT32 *)(StartStoreVirtual+(i*4)));
	}
}

void FlashSync(void){
	int i;
	//println("Erasing Storage page");
	NVMErasePage( (DWORD*) StartStorePhysical);
	//println("Writing new data Storage page");
	for (i=0;i<FLASHSTORE;i++){
		NVMWriteWord((DWORD*)(StartStoreVirtual+(i*4)), flash.stream[i]);
	}
	//println("Storage synced");
}

BYTE FlashSetMac(BYTE * mac){
	FlashLoad();
	if(flash.data.lock==LOCKBYTE){
		return FALSE;
	}
	int i;
	for (i=0;i<6;i++){
		flash.data.mac[i]=mac[i];
	}
	flash.data.lock=LOCKBYTE;
	FlashSync();
	return TRUE;
}

void FlashSetName(char * name){
	FlashLoad();
	int i;
	for (i=0;i<17;i++){
		flash.data.name[i]=name[i];
	}
	FlashSync();
}

void FlashGetMac(BYTE * mac){
	int i;
	FlashLoad();
	if(flash.data.lock == 0xff){
		for (i=0;i<6;i++){
			mac[i]=defMac[i];
		}
		return;
	}
	for (i=0;i<6;i++){
		mac[i]=flash.data.mac[i];
	}
}

void FlashGetName(char * name){
	FlashLoad();
	int i;
	for (i=0;i<17;i++){
		name[i]=flash.data.name[i];
	}
}

void FlashGetBlRev(BYTE * mac){
	int i;
	FlashLoad();
	for (i=0;i<3;i++){
		mac[i]=flash.data.bl[i];
	}
}
void FlashGetFwRev(BYTE * mac){
	int i;
	FlashLoad();
	for (i=0;i<3;i++){
		mac[i]=flash.data.fw[i];
	}
}

BYTE FlashSetFwRev(BYTE * mac){
	//println("Loading fw from flash");
	FlashLoad();
	//println("Loading fw  new data");
	int i;
	BOOL sync=FALSE;
	for (i=0;i<3;i++){
		if(flash.data.fw[i]!=mac[i]){
			flash.data.fw[i]=mac[i];
			sync=TRUE;
		}
	}
	if(sync){
		//println("Syncing fw ");
		FlashSync();
		//println("Syncing fw  done");
	}
	return TRUE;
}

BYTE FlashSetBlRev(BYTE * mac){
	//println("Loading bl flash page");
	FlashLoad();
	//println("Loading bl  new data");
	int i;
	BOOL sync=FALSE;
	for (i=0;i<3;i++){
		if(flash.data.bl[i]!=mac[i]){
			flash.data.bl[i]=mac[i];
			sync=TRUE;
		}
	}
	if(sync){
		//println("Syncing bl ");
		FlashSync();
		//println("Syncing bl  done");
	}
	return TRUE;
}
