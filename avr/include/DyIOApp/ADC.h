/*
 * ADC.h
 *
 *  Created on: Feb 11, 2010
 *      Author: hephaestus
 */

#ifndef ADC_H_
#define ADC_H_

uint8_t InitADC(uint8_t pin);
void ClearADC(uint8_t pin);
uint16_t GetADC(uint8_t pin);
#endif /* ADC_H_ */
