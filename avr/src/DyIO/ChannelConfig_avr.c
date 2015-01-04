/*
 * ChannelConfig.c
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */
#include "UserApp_avr.h"

int32_t GetConfigurationDataTable(uint8_t pin){
	return EEReadValue(pin);
}

void SetNewConfigurationDataTable(uint8_t pin, int32_t value){
	uint8_t mode = GetChannelMode(pin);

	switch(mode){
	case IS_UART_TX		 		:
	case IS_UART_RX	 			:
		ConfigureUART(value);
		break;
	case IS_SPI_MOSI				:
	case IS_SPI_MISO				:
	case IS_SPI_SCK	 			:
		break;
	case IS_DO		 			:
	case IS_PWM	 				:
	case IS_SERVO 				:
	case IS_COUNTER_INPUT_INT	:
	case IS_COUNTER_INPUT_DIR	:
	case IS_COUNTER_INPUT_HOME	:
	case IS_COUNTER_OUTPUT_INT	:
	case IS_COUNTER_OUTPUT_DIR	:
	case IS_COUNTER_OUTPUT_HOME	:
	case IS_DC_MOTOR_VEL			:
	case IS_DC_MOTOR_DIR			:
		EEWriteValue(pin,value);
		break;
	case IS_PPM_IN:
		break;
	}

}

