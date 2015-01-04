/*
 * ADC.h
 *
 *  Created on: Feb 12, 2010
 *      Author: hephaestus
 */

#ifndef ADC_H_
#define ADC_H_

void InitADC(void);
boolean isLocked(void);
boolean isActive(void);
float GetRawVoltage(void);
float GetRawVoltagePostFuse(void);
uint8_t GetRawVoltageCode(uint8_t bank);
float GetRail0Voltage(void);
float GetRail1Voltage(void);

#endif /* ADC_H_ */
