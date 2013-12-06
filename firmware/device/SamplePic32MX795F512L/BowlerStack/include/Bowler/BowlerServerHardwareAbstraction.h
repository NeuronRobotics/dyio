/**
 * @file BowlerHardwareAbstraction.h
 *
 * Created on: May 27, 2010
 * @author hephaestus
 *
 * This header defines the FIFO's for the bowler server.
 */

#ifndef BOWLERHARDWAREABSTRACTION_H_
#define BOWLERHARDWAREABSTRACTION_H_


/**
 * @Depricated use library function FifoGetByteCount
 *
 * This function extracts the number of bytes stored in the given FIFO.
 *
 * @param fifo This is a pointer to a data struct containing an initialized FIFO
 * Prerequsites:
 *  The fifo must be initialized by calling InitByteFifo with valid data.
 *
 * @return returns the number of bytes in the fifo
 */
UINT16 getNumBytes(BYTE_FIFO_STORAGE * fifo);

/**
 * @Depricated use library function FifoGetByteStream
 *
 * This function will get a stream of this length from the connection.
 * @param buffer this is the data buffer where the data retrieved from the physical connection is stored.
 * @param the number of bytes to retrieve from the physical connection.
 */
UINT16 getStream(BYTE * buffer,UINT16 datalength,BYTE_FIFO_STORAGE * fifo);

/**
 * @Depricated use library FifoAddByte
 *
 * Adds a byte from the physical connection to the fifo storage struct.
 *
 * This function should be called when new data is retrieved from the physical connection.
 */
UINT32 addbyte(BYTE_FIFO_STORAGE * fifo,BYTE b, BYTE * errorCode);

/**
 * This function is used to send data from a buffer to the physical connection.
 *
 * @param buffer this is a pointer to the buffer containing the data to be sent
 * @param dataLength this is the number of bytes to send to the physical connection.
 *
 */
UINT16 putStream(BYTE * buffer,UINT16 datalength);
/**
 * get the time in ms
 * @return This should return a float of milliseconds since the processor started.
 */
float getMs(void);

/**
 * send this char to the print terminal
 *
 * If this feature is not needed, it can be empty
 */
void putCharDebug(char c);
/**
 * Start the scheduler. This should set up any timers needed to access the current time.
 */
void startScheduler(void);


#endif /* BOWLERHARDWAREABSTRACTION_H_ */
