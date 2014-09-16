/*
 * EEPROM.h
 *
 *  Created on: Feb 17, 2010
 *      Author: hephaestus
 */

#ifndef EEPROM_H_
#define EEPROM_H_
#include <avr/eeprom.h>
void EEInitMAC(void);
boolean ProvisionMAC(uint8_t * m);

void EEWriteMode(uint8_t pin,uint8_t mode);
void EEWriteValue(uint16_t pin,uint8_t value);
uint8_t EEReadValue(uint16_t pin);
uint8_t EEReadMode(uint8_t pin);

uint32_t EEReadBaud(void);
void EEWriteBaud(uint32_t val);
void EEWriteData(uint16_t addr,uint8_t data);
uint8_t EEReadData(uint16_t addr);

#endif /* EEPROM_H_ */
