/*
 * AVRInterface.c
 *
 *  Created on: May 23, 2010
 *      Author: acamilo
 */
#include "UserApp.h"

	// acamilo:
	// 		change fuses to f7
	// 		SUT changed to LONG to increase oscilator stabalization time.
	// 		Oscilator drive method changed to FullSwing from Low Power.
	// 		SEE DS section 8.4 (p. 34)
#define AVR_LOW			0xf7
#define AVR_HIGH		0xd1
#define AVR_EXT			0xff
//static uint8_t progmode []						={0xAC,0x53,0x00,0x00};

void getCmd(uint8_t comand, uint8_t addrHigh, uint8_t addrLow, uint8_t data) {
	GetByteSPI(comand);
	GetByteSPI(addrHigh);
	GetByteSPI(addrLow);
	GetByteSPI(data);
}

void writeLowFuse()
{
  getCmd(0xac, 0xa0, 0, AVR_LOW);

  DelayMs(5);
}


void writeHighFuse()
{
  getCmd(0xac, 0xa8, 0,AVR_HIGH);
  DelayMs(5);
}

void PowerCycleAVR(){
	println_I("Power cycling the AVR");
	HoldAVRReset();
//	getCommand(progmode);
//	writeLowFuse();
//	writeHighFuse();
//	writeExtendedFuse();
	ReleaseAVRReset();
}
void HoldAVRReset(void){
	AVR_RST_IO=0;
	println_I("Holding AVR in reset");
	DelayMs(10);
}

void ReleaseAVRReset(void){
	AVR_RST_IO=1;
	UpdateAVRLED();
	DelayMs(30);
	println_I("Release AVR in reset");
}

boolean writeAVRTempFlashPageLowByte(uint8_t data, uint8_t address){
	GetByteSPI(0x40);
	GetByteSPI(0x00);
	GetByteSPI(address);
	uint8_t result = GetByteSPI(data);
	DelayMs(10);
	if (result==address) return true; 
	return false; 
}

boolean writeAVRTempFlashPageHighByte(uint8_t data, uint8_t address){
	GetByteSPI(0x48);
	GetByteSPI(0x00);
	GetByteSPI(address);
	uint8_t result = GetByteSPI(data);
	DelayMs(10);
	if (result==address) return true; 
	return false; 

}



void writeExtendedFuse()
{
  getCmd(0xac, 0xa4, 0, AVR_EXT);
  DelayMs(5);
}
