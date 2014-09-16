/*
 * FlashStorage.h
 *
 *  Created on: Jul 15, 2010
 *      Author: hephaestus
 */

#ifndef FLASHSTORAGE_H_
#define FLASHSTORAGE_H_

#define FLASH_PAGE_SIZE 				0x1000
#define BootloaderStartStorePhysical        0x1D009000//End of the bootloader page
#define VirtualAddress                      (0x80000000)
#define DefaultStartStorePhysical            0x1D01F000//end of the chip

#define LOCKBYTE					37

#define FLASHSTORE					20

typedef struct _dataPayload{
		BYTE   mac [6];
		char   name[17];
		BYTE   lock;
		BYTE   blSet;
		BYTE   fwSet;
		BYTE   bl[3];
		BYTE   fw[3];
	}dataPayload;

typedef union __attribute__((__packed__)) _FLASH
{
	UINT32 stream[sizeof(dataPayload)];
	dataPayload data;
} FLASH_STORE;

BYTE FlashSetMac(BYTE * mac);
void FlashSetName(char * name);
void FlashGetMac(BYTE * mac);
void FlashGetName(char * name);

BYTE FlashSetBlRev(BYTE * mac);
void FlashGetBlRev(BYTE * mac);
BYTE FlashSetFwRev(BYTE * mac);
void FlashGetFwRev(BYTE * mac);

void FlashSwitchMemoryToBootloader();

#endif /* FLASHSTORAGE_H_ */
