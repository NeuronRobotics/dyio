
#ifndef MAIN_H
#define MAIN_H
#include "Bowler/Bowler.h"
#include "BLdefines.h"
#include "Prototypes.h"
#include "Core.h"
BYTE getVendorCode(void);
#define BLID			0x64696c62 // 'blid'  Boot loader ID
#define PROG			0x676f7270 // 'prog'  Program a section of flash
#define ERFL			0x6c667265 // 'erfl'  Erase flash
#define REST			0x74736572 // 'rest'  Reset device

#endif //MAIN_H
