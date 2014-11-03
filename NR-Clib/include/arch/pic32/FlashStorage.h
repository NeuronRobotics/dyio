/*
 * FlashStorage.h
 *
 *  Created on: Jul 15, 2010
 *      Author: hephaestus
 */

#ifndef FLASHSTORAGE_H_
#define FLASHSTORAGE_H_

#define FLASH_PAGE_SIZE 				0x1000
#define BootloaderStartStorePhysical        0x1D01F000///End of the bootloader page
#define VirtualAddress                      (0x80000000)
#define DefaultStartStorePhysical           BootloaderStartStorePhysical//end of the chip

//#define StartAppVectVirtual (BootloaderStartStorePhysical | VirtualAddress)

#define LOCKBYTE					37



typedef struct __attribute__((__packed__)) _FLASH_STORE{
		uint8_t   mac [6];
		uint8_t   name[20];
		uint8_t   lock;
		uint8_t   blSet;
		uint8_t   fwSet;
		uint8_t   bl[3];
		uint8_t   fw[4];
	}FlashStorageStruct;
#define FLASHSTORE			sizeof(FlashStorageStruct)
uint8_t FlashSetMac(uint8_t * mac);
void FlashSetName(char * name);
void FlashGetMac(uint8_t * mac);
void FlashGetName(char * name);

uint8_t FlashSetBlRev(uint8_t * mac);
void FlashGetBlRev(uint8_t * mac);
uint8_t FlashSetFwRev(uint8_t * mac);
void FlashGetFwRev(uint8_t * mac);

void FlashSwitchMemoryToBootloader();
void enableFlashStorage(boolean enabled);

#endif /* FLASHSTORAGE_H_ */
