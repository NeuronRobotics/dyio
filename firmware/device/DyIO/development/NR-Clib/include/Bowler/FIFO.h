/**
 * @file FIFO.h
 *
 * Created on: May 27, 2010
 * @author hephaestus
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "Bowler_Struct_Def.h"


#define FIFO_OK 			0
#define FIFO_FAILED_TO_SET	1
#define FIFO_FAILED_TO_GET	2
#define FIFO_OVERFLOW		3
#define FIFO_UNDERFLOW		4

typedef struct _BYTE_FIFO_STORAGE{
	UINT32 bufferSize;
	BYTE * buffer;
	UINT32 readPointer;
	UINT32 writePointer;
	UINT32 byteCount;
	BOOL   mutex;
}BYTE_FIFO_STORAGE;




void InitByteFifo(BYTE_FIFO_STORAGE * fifo,BYTE * buff,UINT32 size);

UINT32 calcByteCount(BYTE_FIFO_STORAGE * fifo);

BYTE ReadFirstByte(BYTE_FIFO_STORAGE * fifo);

/**
 *
 * This function extracts the number of bytes stored in the given FIFO.
 *
 * @param fifo This is a pointer to a data struct containing an initialized FIFO
 * Prerequsites:
 *  The fifo must be initialized by calling InitByteFifo with valid data.
 *
 * @return returns the number of bytes in the fifo
 */

UINT32 FifoGetByteCount(BYTE_FIFO_STORAGE * fifo);

UINT32 FifoAddByte(BYTE_FIFO_STORAGE * fifo,BYTE b, BYTE * errorCode);

void printFiFoState(BYTE_FIFO_STORAGE * fifo, BYTE * buffer,Print_Level l);

#define printFiFoState_E(A,B) printFiFoState(A, B,ERROR_PRINT)
#define printFiFoState_W(A,B) printFiFoState(A, B,WARN_PRINT)
#define printFiFoState_I(A,B) printFiFoState(A, B,INFO_PRINT)

UINT32 FifoGetByteStream(BYTE_FIFO_STORAGE * fifo,BYTE *packet,UINT32 size);

UINT32 FifoReadByteStream(BYTE *packet,UINT32 size,BYTE_FIFO_STORAGE * fifo);

typedef struct _UINT32_FIFO_STORAGE{
	UINT32 bufferSize;
	UINT32 * buffer;
	UINT32 readPointer;
	UINT32 writePointer;
	UINT32 count;
}UINT32_FIFO_STORAGE;

/**
 * Packet FIFO
 */
typedef struct _PACKET_FIFO_STORAGE{
	UINT32 bufferSize;
	BowlerPacket * buffer;
	UINT32 readPointer;
	UINT32 writePointer;
	UINT32 byteCount;
	BOOL   mutex;
}PACKET_FIFO_STORAGE;

void InitPacketFifo(PACKET_FIFO_STORAGE * fifo,BowlerPacket * buff,UINT32 size);

UINT32 FifoAddPacket(PACKET_FIFO_STORAGE * fifo,BowlerPacket * toBeAdded);

UINT32 FifoGetPacketCount(PACKET_FIFO_STORAGE * fifo);

UINT32 FifoGetPacketSpaceAvailible(PACKET_FIFO_STORAGE * fifo);

UINT32 FifoGetPacket(PACKET_FIFO_STORAGE * fifo,BowlerPacket * retrived);




#endif /* FIFO_H_ */
