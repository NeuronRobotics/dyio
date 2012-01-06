/*
 * AVRInterface.c
 *
 *  Created on: May 23, 2010
 *      Author: acamilo
 */
#include "main.h"

BYTE cmd[4];

BYTE avrFlashSize;
BOOL firstPage=TRUE;
UINT32 firstPageBase=0;

#define ATMEGA324P 0x95
#define ATMEGA644P 0x96

union page_buff{
	UINT16 words[100];
	BYTE   bytes[200];
} page;

void getCmd(BYTE comand, BYTE addrHigh, BYTE addrLow, BYTE data) {
	cmd[0] = GetByteSPI(comand);
	cmd[1] = GetByteSPI(addrHigh);
	cmd[2] = GetByteSPI(addrLow);
	cmd[3] = GetByteSPI(data);
}

static BYTE progmode []						={0xAC,0x53,0x00,0x00};
static BYTE readVendorCode []				={0x30,0x00,0x00,0x00};
static BYTE readPartFamilyandFlashSize []	={0x30,0x00,0x01,0x00};
static BYTE readPartNumber []				={0x30,0x00,0x02,0x00};
static BYTE eraseChip []					={0xAC,0x80,0x00,0x00};

#define BytesAtATime 2

//static float pageTime;
static BOOL programing=FALSE;
static BOOL initialized=FALSE;

BYTE getCommand(BYTE * b);

BYTE readByte(UINT16 address);
void writeAVRPageToFlash(UINT16 address);
void writeAVRTempFlashPage(UINT16 addr, UINT16 value);
BOOL writeWord(UINT16 data,UINT16 address);
UINT16 readWord(UINT16 address);



void eraseAVR(void){
	getCommand(eraseChip);
	DelayMs(20);
	writeLowFuse();
	writeHighFuse();
	writeExtendedFuse();
}



void avrSPIProg(BowlerPacket * Packet){
	if (programing==FALSE){
		programing=TRUE;
		//programMode();
	}
	//BYTE data,set;
	UINT32 i,numWords;
	UINT32_UNION baseAddress;
	baseAddress.byte.FB=Packet->use.data[1];
	baseAddress.byte.TB=Packet->use.data[2];
	baseAddress.byte.SB=Packet->use.data[3];
	baseAddress.byte.LB=Packet->use.data[4];
	numWords = (Packet->use.head.DataLegnth-4-1-4);
	for (i=0;i<numWords;i++){
		page.bytes[i]=Packet->use.data[5+i];
	}
	for (;i<128;i++){
		//Pad the end with junk data in case there aren't the right number of bytes
		page.bytes[i]=0xff;
	}
	for (i=0; i<64; i++ ){
		if(avrFlashSize==ATMEGA324P)
			writeAVRTempFlashPage(i,page.words[i]);
		else if (avrFlashSize==ATMEGA644P){
			if(firstPage)
				writeAVRTempFlashPage(i,page.words[i]);
			else
				writeAVRTempFlashPage(i+64,page.words[i]);

		}
	}
	if(avrFlashSize==ATMEGA324P)
		writeAVRPageToFlash(baseAddress.Val);
	else if (avrFlashSize==ATMEGA644P){
		if(firstPage){
			firstPage=FALSE;
			firstPageBase=baseAddress.Val;
		}else{
			firstPage=TRUE;
			writeAVRPageToFlash(firstPageBase);
		}
	}
}

BYTE avrID[]={0,0,0};
BYTE getVendorCode(void){
#if defined(DYIO)
	if(avrID[0]!=0x1E)
		avrID[0]= getCommand(readVendorCode);
	return avrID[0];
#else
	return 0x1E;
#endif
}
void GetAVRid(BYTE * buffer){
	//printfDEBUG("AVR getting ID");
	//InitUINT32Fifo(&storeAddr,privateAddr,sizeof(privateAddr));
	programMode();
	avrID[0]= getCommand(readVendorCode);
	buffer[0]=GetHighNib(avrID[0]);
	buffer[1]=GetLowNib(avrID[0]);

	avrID[1] = getCommand(readPartFamilyandFlashSize);
	avrFlashSize=avrID[1];
	buffer[2]=GetHighNib(avrID[1]);
	buffer[3]=GetLowNib(avrID[1]);

	avrID[2] = getCommand(readPartNumber);
	buffer[4]=GetHighNib(avrID[2]);
	buffer[5]=GetLowNib(avrID[2]);
	buffer[6]=0;
}

void programMode(void){
	HoldAVRReset();
	getCommand(progmode);
	DelayMs(20);
}

BYTE getCommand(BYTE * b){
	DelayMs(15);
	int i;
	BYTE back;
	for (i=0;i<4;i++){
		 back=GetByteSPI(b[i]);
	}
	DelayMs(15);
	return back;
}

void HoldAVRReset(void){
	AVR_RST_IO=0;
	DelayMs(5);
}

void ReleaseAVRReset(void){
	AVR_RST_IO=1;
	//DelayMs(70);
}

void writeAVRTempFlashPage(UINT16 addr, UINT16 value)
{
  UINT16_UNION val;
  val.Val=value;
  getCmd(0x40, 0, addr, val.byte.LB);
  getCmd(0x48, 0, addr, val.byte.SB);
}

void writeAVRPageToFlash(UINT16 address){
	//UINT32 i,offset;
	//BYTE data,set;
	UINT16_UNION addr;
	addr.Val=address>>1;
	getCmd(0x4c,addr.byte.SB,addr.byte.LB,0x00);
	//printfDEBUG("AVR Writing page to:");
	//printfDEBUG_UL(address);
	DelayMs(30);
}

UINT16 readWord(UINT16 address){
	UINT16 low,high;
	UINT16_UNION addr;
	addr.Val=address;
	getCmd(0x20, addr.byte.SB, addr.byte.LB, 0x00);
	low=cmd[3];
	getCmd(0x28, addr.byte.SB, addr.byte.SB, 0x00);
	high=cmd[3];
	return (high<<8)|low;
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


void writeExtendedFuse()
{
  getCmd(0xac, 0xa4, 0, AVR_EXT);
  DelayMs(5);
}


BYTE readLowFuse(void)
{
  getCmd(0x50, 0x00, 0, 0);
  return cmd[3];
}


BYTE readExtFuse(void)
{
  getCmd(0x50, 0x08, 0, 0);
  return cmd[3];
}


BYTE readHighFuse(void)
{
  getCmd(0x58, 0x08, 0, 0);
  return cmd[3];
}


void InitSPI(void){
	if(initialized)
		return;
	initialized=TRUE;
	//printfDEBUG("Initializing SPI interface");
	mPORTGOpenDrainOpen(BIT_6);// Clock is output
	mPORTGOpenDrainOpen(BIT_8);// Data Out is an output
	OpenSPI2(SPI_MODE8_ON|ENABLE_SDO_PIN|SLAVE_ENABLE_OFF|SPI_CKE_ON|MASTER_ENABLE_ON|SEC_PRESCAL_8_1|PRI_PRESCAL_64_1, SPI_ENABLE);
}

void StopSPI(void){
	CloseSPI2();
	_RG6=1;
	_RG8=1;
	ReleaseAVRReset();
}

BYTE GetByteSPI(BYTE b){
	InitSPI();
	putcSPI2(b);	// Start sending
	return getcSPI2();
}


