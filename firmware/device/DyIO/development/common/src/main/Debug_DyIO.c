
#include "DyIO/Debug_DyIO.h"
#include "Bowler/Bowler.h"

void printMode(BYTE mode){
	#if !defined(__AVR_ATmega324P__)
		switch(mode&0x7f){
		case NO_CHANGE:
			print_E("NO_CHANGE");
			break;
		case HIGH_IMPEDANCE:
			print_E("HIGH_IMPEDANCE");
			break;
		case IS_DI:
			print_E("IS_DI");
			break;
		case IS_DO:
			print_E("IS_DO");
			break;
		case IS_ANALOG_IN:
			print_E("IS_ANALOG_IN");
			break;
		case IS_ANALOG_OUT:
			print_E("IS_ANALOG_OUT");
			break;
		case IS_PWM:
			print_E("PWM");
			break;
		case IS_SERVO:
			print_E("SERVO");
			break;
		case IS_UART_TX:
			print_E("UART_TX");
			break;
		case IS_UART_RX:
			print_E("UART_RX");
			break;
		case IS_SPI_MOSI:
			print_E("SPI_MOSI");
			break;
		case IS_SPI_MISO:
			print_E("SPI_MISO");
			break;
		case IS_SPI_SCK:
			print_E("SPI_SCK");
			break;
//		case IS_SPI_SS:
//			print_E("SPI_SS");
//			break;
		case IS_COUNTER_INPUT_INT:
			print_E("COUNTER_INPUT_INT");
			break;
		case IS_COUNTER_INPUT_DIR:
			print_E("COUNTER_INPUT_DIR");
			break;
		case IS_COUNTER_INPUT_HOME:
			print_E("COUNTER_INPUT_HOME");
			break;
		case IS_COUNTER_OUTPUT_INT:
			print_E("COUNTER_OUTPUT_INT");
			break;
		case IS_COUNTER_OUTPUT_DIR:
			print_E("COUNTER_OUTPUT_DIR");
			break;
		case IS_COUNTER_OUTPUT_HOME:
			print_E("COUNTER_OUTPUT_HOME");
			break;
		case IS_DC_MOTOR_DIR:
			print_E("IS_DC_MOTOR_DIR");
			break;
		case IS_DC_MOTOR_VEL:
			print_E("IS_DC_MOTOR_VEL");
			break;
		case IS_PPM_IN:
			print_E("IS_PPM_IN");
			break;
		default:
			print_E("UNKNOWN");
			p_ul_E(mode);
		}
	#else
	p_sl_I(mode);
	#endif
}
