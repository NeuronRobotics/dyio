/*
 * AVR_IO.h
 *
 *  Created on: Feb 11, 2010
 *      Author: hephaestus
 */

#ifndef AVR_IO_H_
#define AVR_IO_H_

void SetPinTris(uint8_t PIN,uint8_t state);
void SetDIO(uint8_t PIN,uint8_t state);
uint8_t GetDIO(uint8_t PIN);

#endif /* AVR_IO_H_ */
