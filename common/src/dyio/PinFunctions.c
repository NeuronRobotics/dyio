#include "DyIO/DyIO_def.h"
#include "Namespace/Namespace_bcs_io.h"
#include "Namespace/Namespace_bcs_io_setmode.h"



DATA_STRUCT DyioPinFunctionData[NUM_PINS];

void InitPinFunction(void){
	int i;
	for (i=0;i<NUM_PINS;i++){
		DyioPinFunctionData[i].FUNCTION.HAS_ANALOG_IN=false; 
		DyioPinFunctionData[i].FUNCTION.HAS_PWM=false; 
		DyioPinFunctionData[i].FUNCTION.HAS_UART_T=false; 
		DyioPinFunctionData[i].FUNCTION.HAS_UART_R=false; 
		DyioPinFunctionData[i].FUNCTION.HAS_SPI_C=false; 
		DyioPinFunctionData[i].FUNCTION.HAS_SPI_I=false; 
		DyioPinFunctionData[i].FUNCTION.HAS_SPI_O=false; 
		DyioPinFunctionData[i].FUNCTION. HAS_COUNTER_INPUT_I = false; 
		DyioPinFunctionData[i].FUNCTION.HAS_COUNTER_OUTPUT_I = false; 
		DyioPinFunctionData[i].FUNCTION. HAS_COUNTER_INPUT_D = false; 
		DyioPinFunctionData[i].FUNCTION.HAS_COUNTER_OUTPUT_D = false; 
		DyioPinFunctionData[i].FUNCTION. HAS_COUNTER_INPUT_H = false; 
		DyioPinFunctionData[i].FUNCTION.HAS_COUNTER_OUTPUT_H = false; 
		DyioPinFunctionData[i].FUNCTION.HAS_DC_MOTOR = false; 
		DyioPinFunctionData[i].FUNCTION.HAS_PPM=false; 
	}
	DyioPinFunctionData[0].FUNCTION.HAS_SPI_C=true; 
	DyioPinFunctionData[1].FUNCTION.HAS_SPI_I=true; 
	DyioPinFunctionData[2].FUNCTION.HAS_SPI_O=true; 


	DyioPinFunctionData[4].FUNCTION.HAS_PWM = true; 
	DyioPinFunctionData[5].FUNCTION.HAS_PWM = true; 
	DyioPinFunctionData[6].FUNCTION.HAS_PWM = true; 
	DyioPinFunctionData[7].FUNCTION.HAS_PWM = true; 

	DyioPinFunctionData[4].FUNCTION.HAS_DC_MOTOR = true; 
	DyioPinFunctionData[5].FUNCTION.HAS_DC_MOTOR = true; 
	DyioPinFunctionData[6].FUNCTION.HAS_DC_MOTOR = true; 
	DyioPinFunctionData[7].FUNCTION.HAS_DC_MOTOR = true; 

	DyioPinFunctionData[8].FUNCTION.HAS_DC_MOTOR = true; 
	DyioPinFunctionData[9].FUNCTION.HAS_DC_MOTOR = true; 
	DyioPinFunctionData[10].FUNCTION.HAS_DC_MOTOR = true; 
	DyioPinFunctionData[11].FUNCTION.HAS_DC_MOTOR = true; 

	DyioPinFunctionData[8].FUNCTION.HAS_ANALOG_IN = true; 
	DyioPinFunctionData[9].FUNCTION.HAS_ANALOG_IN = true; 
	DyioPinFunctionData[10].FUNCTION.HAS_ANALOG_IN = true; 
	DyioPinFunctionData[11].FUNCTION.HAS_ANALOG_IN = true; 

	DyioPinFunctionData[12].FUNCTION.HAS_ANALOG_IN = true; 
	DyioPinFunctionData[13].FUNCTION.HAS_ANALOG_IN = true; 
	DyioPinFunctionData[14].FUNCTION.HAS_ANALOG_IN = true; 
	DyioPinFunctionData[15].FUNCTION.HAS_ANALOG_IN = true; 

	DyioPinFunctionData[16].FUNCTION.HAS_UART_T =true; 
	DyioPinFunctionData[17].FUNCTION.HAS_UART_R =true; 

	//Home buttons
	DyioPinFunctionData[0].FUNCTION.HAS_COUNTER_INPUT_H = true; 
	DyioPinFunctionData[1].FUNCTION.HAS_COUNTER_INPUT_H = true; 
	DyioPinFunctionData[2].FUNCTION.HAS_COUNTER_INPUT_H = true; 
	DyioPinFunctionData[3].FUNCTION.HAS_COUNTER_INPUT_H = true; 

	DyioPinFunctionData[0].FUNCTION.HAS_COUNTER_OUTPUT_H = true; 
	DyioPinFunctionData[1].FUNCTION.HAS_COUNTER_OUTPUT_H = true; 
	DyioPinFunctionData[2].FUNCTION.HAS_COUNTER_OUTPUT_H = true; 
	DyioPinFunctionData[3].FUNCTION.HAS_COUNTER_OUTPUT_H = true; 
	//Interuptibles

	DyioPinFunctionData[17].FUNCTION.HAS_COUNTER_INPUT_I = true; 
	DyioPinFunctionData[19].FUNCTION.HAS_COUNTER_INPUT_I = true; 
	DyioPinFunctionData[21].FUNCTION.HAS_COUNTER_INPUT_I = true; 
	DyioPinFunctionData[23].FUNCTION.HAS_COUNTER_INPUT_I = true; 

	//Direction
	DyioPinFunctionData[16].FUNCTION.HAS_COUNTER_INPUT_D = true; 
	DyioPinFunctionData[18].FUNCTION.HAS_COUNTER_INPUT_D = true; 
	DyioPinFunctionData[20].FUNCTION.HAS_COUNTER_INPUT_D = true; 
	DyioPinFunctionData[22].FUNCTION.HAS_COUNTER_INPUT_D = true; 

	//Interuptibles
	DyioPinFunctionData[17].FUNCTION.HAS_COUNTER_OUTPUT_I = true; 
	DyioPinFunctionData[19].FUNCTION.HAS_COUNTER_OUTPUT_I = true; 
	DyioPinFunctionData[21].FUNCTION.HAS_COUNTER_OUTPUT_I = true; 
	DyioPinFunctionData[23].FUNCTION.HAS_COUNTER_OUTPUT_I = true; 

	//Direction
	DyioPinFunctionData[16].FUNCTION.HAS_COUNTER_OUTPUT_D = true; 
	DyioPinFunctionData[18].FUNCTION.HAS_COUNTER_OUTPUT_D = true; 
	DyioPinFunctionData[20].FUNCTION.HAS_COUNTER_OUTPUT_D = true; 
	DyioPinFunctionData[22].FUNCTION.HAS_COUNTER_OUTPUT_D = true; 

	DyioPinFunctionData[23].FUNCTION.HAS_PPM = true; 

	InitilizeBcsIo(	NUM_PINS,
					DyioPinFunctionData,
					&SetChanelValueHW,
					&GetChanelValueHW,
					&SetAllChanelValueHW,
					&GetAllChanelValueHW,
					&ConfigureChannelHW,
					&SetStreamHW,
					&GetStreamHW
				);
	InitilizeBcsIoSetmode(&setMode);
}
