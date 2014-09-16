/**
 * @file DCMotorDriver.h
 *
 *  Created on: Sep 9, 2010
 * @author Kevin Harrington
 */

#ifndef DCMOTORDRIVER_H_
#define DCMOTORDRIVER_H_

boolean InitDCMotor(uint8_t pin);
void ClearDCMotor(uint8_t pin);
uint8_t GetDCMotor(uint8_t pin);
void SetDCMotor(uint8_t pin,uint8_t vel);

#endif /* DCMOTORDRIVER_H_ */
