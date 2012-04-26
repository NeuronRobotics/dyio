
#include "DyIO/Debug_DyIO.h"
#include "Bowler/Bowler.h"

void printMode(BYTE mode, Print_Level l){
	#if !defined(__AVR_ATmega324P__)
		switch(mode&0x7f){
		case NO_CHANGE:
			print("NO_CHANGE",l);
			break;
		case HIGH_IMPEDANCE:
			print("HIGH_IMPEDANCE",l);
			break;
		case IS_DI:
			print("IS_DI",l);
			break;
		case IS_DO:
			print("IS_DO",l);
			break;
		case IS_ANALOG_IN:
			print("IS_ANALOG_IN",l);
			break;
		case IS_ANALOG_OUT:
			print("IS_ANALOG_OUT",l);
			break;
		case IS_PWM:
			print("PWM",l);
			break;
		case IS_SERVO:
			print("SERVO",l);
			break;
		case IS_UART_TX:
			print("UART_TX",l);
			break;
		case IS_UART_RX:
			print("UART_RX",l);
			break;
		case IS_SPI_MOSI:
			print("SPI_MOSI",l);
			break;
		case IS_SPI_MISO:
			print("SPI_MISO",l);
			break;
		case IS_SPI_SCK:
			print("SPI_SCK",l);
			break;
//		case IS_SPI_SS:
//			print("SPI_SS",l);
//			break;
		case IS_COUNTER_INPUT_INT:
			print("COUNTER_INPUT_INT",l);
			break;
		case IS_COUNTER_INPUT_DIR:
			print("COUNTER_INPUT_DIR",l);
			break;
		case IS_COUNTER_INPUT_HOME:
			print("COUNTER_INPUT_HOME",l);
			break;
		case IS_COUNTER_OUTPUT_INT:
			print("COUNTER_OUTPUT_INT",l);
			break;
		case IS_COUNTER_OUTPUT_DIR:
			print("COUNTER_OUTPUT_DIR",l);
			break;
		case IS_COUNTER_OUTPUT_HOME:
			print("COUNTER_OUTPUT_HOME",l);
			break;
		case IS_DC_MOTOR_DIR:
			print("IS_DC_MOTOR_DIR",l);
			break;
		case IS_DC_MOTOR_VEL:
			print("IS_DC_MOTOR_VEL",l);
			break;
		case IS_PPM_IN:
			print("IS_PPM_IN",l);
			break;
		default:
			print("UNKNOWN",l);
			p_ul(mode,l);
		}
	#else
	p_sl_I(mode);
	#endif
}
