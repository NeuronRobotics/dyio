/**
 * @file FIFO.c
 *
 * Created on: May 27, 2010
 * @author hephaestus
 */

#include "Bowler/Bowler.h"
void clearByteFifo(BYTE_FIFO_STORAGE * fifo);
//static UINT32 i;
//const char * fifoinit = "Initializing FIFO, Buffer Size: ";
//const char * error = "@##ERROR fifo is overflown! Size, buffer: ";

void printFiFoState(BYTE_FIFO_STORAGE * fifo, BYTE * buffer,Print_Level l){
	int i;
	print("\nFifo state: \tBytes:",l);
	p_int(calcByteCount(fifo),l);

	FifoReadByteStream(	buffer,
						calcByteCount(fifo)+1,
						fifo);
	print("\tData [ ",l);
	for(i=0;i<calcByteCount(fifo);i++){
		p_int(buffer[i],l);print(" ",l);
	}
	print(" ]\n",l);
}

BOOL lockFifo(BYTE_FIFO_STORAGE * fifo){
//	if(fifo->mutex != FALSE){
//		return FALSE;
//	}
//	fifo->mutex=TRUE;
	StartCritical();
	return TRUE;
}
BOOL unLockFifo(BYTE_FIFO_STORAGE * fifo){
	//fifo->mutex=FALSE;
	EndCritical();
	return TRUE;
}
void InitByteFifo(BYTE_FIFO_STORAGE * fifo,BYTE * buff,UINT32 size){
	if(fifo == 0 ||  buff == 0){
		println("@#@#FIFO FAILED TO INITIALIZE",ERROR_PRINT);p_int(size,ERROR_PRINT);
	}
	fifo->buffer=buff;
	fifo->bufferSize=size;
	fifo->readPointer=0;
	fifo->writePointer=0;
	//fifo->byteCount=0;
	fifo->mutex=FALSE;
	clearByteFifo(fifo);
	//println(fifoinit);p_int(size);
}
void clearByteFifo(BYTE_FIFO_STORAGE * fifo){
	//StartCritical();
	int i;
	for (i=0;i < fifo->bufferSize;i++){
		fifo->buffer[i]=0;
	}
	//EndCritical();
}

BYTE ReadFirstByte(BYTE_FIFO_STORAGE * fifo){
	return fifo->buffer[fifo->readPointer];
}

UINT32 calcByteCount(BYTE_FIFO_STORAGE * fifo){
	int w =fifo->writePointer;
	int r = fifo->readPointer;
	if(w>r){
		fifo->byteCount= w-r;
	}else if(w==r){
		fifo->byteCount= 0;
	}else{
		fifo->byteCount= (w+fifo->bufferSize)-r;
	}
	return fifo->byteCount;
}

UINT32 FifoGetByteCount(BYTE_FIFO_STORAGE * fifo){
	return calcByteCount(fifo);

}

UINT32 FifoAddByte(BYTE_FIFO_STORAGE * fifo,BYTE b, BYTE * errorCode){
	if(calcByteCount(fifo) >= (fifo->bufferSize-2)){
		//println(error);p_int(fifo->bufferSize);print(",");p_int(fifo->byteCount);
		errorCode[0]=FIFO_OVERFLOW;
		return 0;
	}
	if(lockFifo(fifo)==FALSE){
		errorCode[0]=FIFO_FAILED_TO_SET;
		//return 0;
	}
	fifo->buffer[fifo->writePointer]=b;
	fifo->writePointer++;
	if (fifo->writePointer == fifo->bufferSize){
		fifo->writePointer=0;
	}
	//fifo->byteCount++;
	calcByteCount(fifo);
	errorCode[0]=FIFO_OK;
	unLockFifo(fifo);
	return (calcByteCount(fifo)<=fifo->bufferSize);
}

BYTE getByte(BYTE_FIFO_STORAGE * fifo, BYTE * errorCode){
	if(lockFifo(fifo)==FALSE){
		errorCode[0]=FIFO_FAILED_TO_GET;
		return 0;
	}
	BYTE b = fifo->buffer[fifo->readPointer];
	fifo->readPointer++;
	if (fifo->readPointer==fifo->bufferSize){
		fifo->readPointer=0;
	}
	errorCode[0]=FIFO_OK;
	calcByteCount(fifo);
	unLockFifo(fifo);
	return b;
}

UINT32 FifoGetByteStream(BYTE_FIFO_STORAGE * fifo,BYTE *packet,UINT32 size){
	BYTE err;
	int i;
	int count = calcByteCount(fifo);
	if(size>count)
		size = count;
	for (i=0;i<size;i++){
		if(count > 0){
			BYTE b;
			do{
				b = getByte(fifo,&err);
			}while(err != FIFO_OK);
			packet[i] = b;
		}else{
			packet[i]=0;
		}
	}
	return i;
}

UINT32 FifoReadByteStream(BYTE *packet,UINT32 size,BYTE_FIFO_STORAGE * fifo){
	UINT32 read=fifo->readPointer;
	UINT32  count = calcByteCount(fifo);
	int i;
	if(size>count)
		size = count;
	for (i=0;i<size;i++){
		if(count > 0){
			packet[i] = fifo->buffer[read];
			read++;
			if (read==fifo->bufferSize){
				read=0;
			}
		}else{
			packet[i]=0;
		}
	}
	return i;
}


void InitPacketFifo(PACKET_FIFO_STORAGE * fifo,BowlerPacket * buff,UINT32 size){
    	if(fifo == 0 ||  buff == 0){
		println("@#@#FIFO FAILED TO INITIALIZE",ERROR_PRINT);p_int(size,ERROR_PRINT);
	}
	fifo->buffer=buff;
	fifo->bufferSize=size;
	fifo->readPointer=0;
	fifo->writePointer=0;
	//fifo->byteCount=0;
	fifo->mutex=FALSE;
}

UINT32 FifoAddPacket(PACKET_FIFO_STORAGE * fifo,BowlerPacket * toBeAdded){
    	if(FifoGetPacketCount(fifo) >= (fifo->bufferSize)){
		println_E("Packet FIFO overflow");p_int_E(fifo->bufferSize);print_E(",");p_int_E(fifo->byteCount);
		return 0;
	}
	StartCritical();

        copyPacket(toBeAdded,&fifo->buffer[fifo->writePointer]);

	fifo->writePointer++;
	if (fifo->writePointer == fifo->bufferSize){
		fifo->writePointer=0;
	}
	//fifo->byteCount++;
	FifoGetPacketCount(fifo);
        
        EndCritical();
	return (FifoGetPacketCount(fifo)<=fifo->bufferSize);
}

UINT32 FifoGetPacketCount(PACKET_FIFO_STORAGE * fifo){
	int w =fifo->writePointer;
	int r = fifo->readPointer;
	if(w>r){
		fifo->byteCount= w-r;
	}else if(w==r){
		fifo->byteCount= 0;
	}else{
		fifo->byteCount= (w+fifo->bufferSize)-r;
	}
	return fifo->byteCount;
}

UINT32 FifoGetPacketSpaceAvailible(PACKET_FIFO_STORAGE * fifo){
        return fifo->bufferSize - FifoGetPacketCount(fifo)-1;
}

UINT32 FifoGetPacket(PACKET_FIFO_STORAGE * fifo,BowlerPacket * retrived){
        StartCritical();

        if(FifoGetPacketCount(fifo)>0)
            copyPacket(&fifo->buffer[fifo->readPointer],retrived);
        else
            return FALSE;
	fifo->readPointer++;
	if (fifo->readPointer==fifo->bufferSize){
		fifo->readPointer=0;
	}

	FifoGetPacketCount(fifo);
	EndCritical();
	return TRUE;
}
