/*
 * SPI.h
 *
 *  Created on: Apr 4, 2010
 *      Author: hephaestus
 */

#ifndef SPI_H_
#define SPI_H_
#define  SCK_TRIS			(_TRISG6)
#define  SDI_TRIS			(_TRISG7)
#define  SDO_TRIS			(_TRISG8)
void InitSPIDyIO(void);
void StopDyIOSPI(uint8_t mode);
boolean isSPI(uint8_t mode);
uint8_t GetByteSPIDyIO(uint8_t b);
void SyncSPIData();
void SendPacketToSPIFromArray(uint8_t numBytes,uint8_t * data);

boolean LoadSPITxData(uint8_t numValues,uint8_t * data);
uint8_t GetSPIRxData(uint8_t * data);

#endif /* SPI_H_ */
