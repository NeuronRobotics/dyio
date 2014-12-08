/*
 * PIC_IO.h
 *
 *  Created on: Mar 5, 2010
 *      Author: hephaestus
 */

#ifndef PIC_IO_H_
#define PIC_IO_H_

uint8_t SetCoProcMode(uint8_t PIN,uint8_t mode);
uint8_t SetCoProConfiguration(uint8_t pin,int32_t mode);
uint8_t GetCoProConfigurations();
void SyncConfigurations();
uint8_t SetAllCoProcMode();

#define SetChannelValueCoProc( PIN, state) setDataTableCurrentValue(PIN, state)

void _SetChannelValueCoProc(uint8_t PIN, uint8_t state);

uint8_t GetChannelValueCoProc(uint8_t PIN);
uint16_t GetADC(uint8_t PIN);
boolean GetSerialStream(BowlerPacket * packet);
boolean Get16Async(uint16_t * data);
boolean Get8Async(uint16_t * data);
void CheckRev(void);
void SyncModes(void);

#endif /* PIC_IO_H_ */
