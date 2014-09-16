/*
 * Push.h
 *
 *  Created on: Sep 24, 2010
 *      Author: hephaestus
 */

#ifndef PUSH_H_
#define PUSH_H_
void PushSerial(void);
void PushAllAdcVal();
void PushAllDiVal();
void PushADCval(uint8_t pin,uint16_t val);
void PushDIval(uint8_t pin,uint8_t val);



#endif /* PUSH_H_ */
