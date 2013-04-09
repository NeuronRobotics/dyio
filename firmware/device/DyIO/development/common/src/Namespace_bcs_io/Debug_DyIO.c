
#include "Bowler/Bowler.h"
#include "Namespace/Namespace_bcs_io.h"

int maxNumCharsInModes=0;
const char *  printModeStrings[]={
		"NO_CHANGE",
		"HIGH_IMPEDANCE",
		"IS_DI",
		"IS_DO",
		"IS_ANALOG_IN",
		"IS_ANALOG_OUT",
		"PWM",
		"SERVO",
		"UART_TX",
		"UART_RX",
		"SPI_MOSI",
		"SPI_MISO",
		"SPI_SCK",
		"SPI_SS",
		"COUNTER_INPUT_INT",
		"COUNTER_INPUT_DIR",
		"COUNTER_INPUT_HOME",
		"COUNTER_OUTPUT_INT",
		"COUNTER_OUTPUT_DIR",
		"COUNTER_OUTPUT_HOME",
		"IS_DC_MOTOR_DIR",
		"IS_DC_MOTOR_VEL",
		"IS_PPM_IN"
};


void printMode(BYTE mode, Print_Level l){
	mode = mode & 0x7f;
	int i=0;
	if(maxNumCharsInModes==0){
		for(i=0;i<IO_MODE_MAX;i++){
			int len = strlen(printModeStrings[i]);
			if (len>maxNumCharsInModes)
				maxNumCharsInModes = len;
		}
	}
	if(mode>0 && mode<IO_MODE_MAX	){
		print(printModeStrings[mode],l);
		int spaces = maxNumCharsInModes - strlen(printModeStrings[mode]);
		if (spaces>0){
			for (i=0;i<spaces;i++){
				putCharDebug(' ');
			}
		}
	}else{
		print("UNKNOWN #",l);
		p_ul(mode,l);
	}

}