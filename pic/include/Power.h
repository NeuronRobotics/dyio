/*
 * Power.h
 *
 *  Created on: Feb 6, 2010
 *      Author: hephaestus
 */

#ifndef POWER_H_
#define POWER_H_

#define RAW_POWER 1
#define REGULATED 0

uint16_t GetRailVoltage(void);
uint8_t GetSwitchPosition(uint8_t chan);
/**
 * Sets the current brown out mode
 */
void setBrownOutDetect(boolean b);
/**
 * gets the current brown out mode
 */
boolean getBrownOutDetect();
boolean getPowerOverRide();

#endif /* POWER_H_ */
