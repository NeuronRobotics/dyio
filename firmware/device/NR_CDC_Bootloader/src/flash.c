/*
 * flash.c
 *
 *  Created on: May 30, 2010
 *      Author: hephaestus
 */
#include "main.h"

void writeLine(BowlerPacket * Packet){
	//printfDEBUG("Writing Line:");
	UINT32 i,offset,numWords;
	UINT32_UNION baseAddress,dataWord;
	baseAddress.byte.FB=Packet->use.data[1];
	baseAddress.byte.TB=Packet->use.data[2];
	baseAddress.byte.SB=Packet->use.data[3];
	baseAddress.byte.LB=Packet->use.data[4];
	numWords = (Packet->use.head.DataLegnth-4-1-4)/4;
	//printfDEBUG_UL(baseAddress.Val);
	for (i=0;i<numWords;i++){
		offset = 4+1+(i*4);
		dataWord.byte.FB=Packet->use.data[3 + offset];
		dataWord.byte.TB=Packet->use.data[2 + offset];
		dataWord.byte.SB=Packet->use.data[1 + offset];
		dataWord.byte.LB=Packet->use.data[0 + offset];
		writeWordFlash(baseAddress.Val+(i*4),dataWord.Val);
	}
}

void writeWordFlash(DWORD address,DWORD data){
	extern BOOL resetFlag;
	if (address >= StartAppVectPhysical && (address < EndAppVectPhysical)){
		NVMWriteWord((DWORD*)address, data);
		if ((*(int *)(address|0x80000000)) != data){
			//printfDEBUG("##Write FAILED!!");
			eraseFlash();
			resetFlag = TRUE;
		}
	}

}

void eraseFlash(void){
	int temp;
	DWORD address = StartAppVectPhysical;
	//DWORD erAddr;
	DWORD size =EndAppVectPhysical-StartAppVectPhysical;
	for( temp = 0; temp < (size/FLASH_PAGE_SIZE); temp++ ){
		if (address <(EndAppVectPhysical-FLASH_PAGE_SIZE)){
			//printfDEBUG("Erasing page at address:");
			//printfDEBUG_UL(address);
			NVMErasePage( (DWORD*) address );
		}
		address +=FLASH_PAGE_SIZE;
	}
}

