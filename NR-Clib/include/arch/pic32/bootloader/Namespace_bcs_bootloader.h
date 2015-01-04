/* 
 * File:   Namespace_bcs_bootloader.h
 * Author: hephaestus
 *
 * Created on September 17, 2014, 7:26 PM
 */

#ifndef NAMESPACE_BCS_BOOTLOADER_H
#define	NAMESPACE_BCS_BOOTLOADER_H
#include "BLdefines.h"
#include "Prototypes.h"
#ifdef	__cplusplus
extern "C" {
#endif

NAMESPACE_LIST * get_bcsBootloaderNamespace();
boolean getBootloaderResetFlag();
void callBootloaderReset();

BYTE getVendorCode(void);
#define BLID			0x64696c62 // 'blid'  Boot loader ID
#define PROG			0x676f7270 // 'prog'  Program a section of flash
#define ERFL			0x6c667265 // 'erfl'  Erase flash
#define REST			0x74736572 // 'rest'  Reset device
#define _REV                    0x7665725f // '_rev'  Get the revision number

#ifdef	__cplusplus
}
#endif

#endif	/* NAMESPACE_BCS_BOOTLOADER_H */

