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
	uint32_t bufferSize;
	uint8_t * buffer;
	uint32_t readPointer;
	uint32_t writePointer;
	uint32_t byteCount;
	boolean   mutex;
}BYTE_FIFO_STORAGE;




void InitByteFifo(BYTE_FIFO_STORAGE * fifo,uint8_t * buff,uint32_t size);

uint32_t calcByteCount(BYTE_FIFO_STORAGE * fifo);

uint8_t ReadFirstByte(BYTE_FIFO_STORAGE * fifo);

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

uint32_t FifoGetByteCount(BYTE_FIFO_STORAGE * fifo);

uint32_t FifoAddByte(BYTE_FIFO_STORAGE * fifo,uint8_t b, uint8_t * errorCode);

void printFiFoState(BYTE_FIFO_STORAGE * fifo, uint8_t * buffer,Print_Level l);

#define printFiFoState_E(A,B) printFiFoState(A, B,ERROR_PRINT)
#define printFiFoState_W(A,B) printFiFoState(A, B,WARN_PRINT)
#define printFiFoState_I(A,B) printFiFoState(A, B,INFO_PRINT)

uint32_t FifoGetByteStream(BYTE_FIFO_STORAGE * fifo,uint8_t *packet,uint32_t size);

uint32_t FifoReadByteStream(uint8_t *packet,uint32_t size,BYTE_FIFO_STORAGE * fifo);

typedef struct _UINT32_FIFO_STORAGE{
	uint32_t bufferSize;
	uint32_t * buffer;
	uint32_t readPointer;
	uint32_t writePointer;
	uint32_t count;
}UINT32_FIFO_STORAGE;

/**
 * Packet FIFO
 */
typedef struct _PACKET_FIFO_STORAGE{
	uint32_t bufferSize;
	BowlerPacket * buffer;
	uint32_t readPointer;
	uint32_t writePointer;
	uint32_t byteCount;
	boolean   mutex;
}PACKET_FIFO_STORAGE;

void InitPacketFifo(PACKET_FIFO_STORAGE * fifo,BowlerPacket * buff,uint32_t size);

uint32_t FifoAddPacket(PACKET_FIFO_STORAGE * fifo,BowlerPacket * toBeAdded);

uint32_t FifoGetPacketCount(PACKET_FIFO_STORAGE * fifo);

uint32_t FifoGetPacketSpaceAvailible(PACKET_FIFO_STORAGE * fifo);

uint32_t FifoGetPacket(PACKET_FIFO_STORAGE * fifo,BowlerPacket * retrived);




#endif /* FIFO_H_ */
