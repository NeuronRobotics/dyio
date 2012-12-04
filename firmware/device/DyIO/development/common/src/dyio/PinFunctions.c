#include "DyIO/DyIO_def.h"

DATA_STRUCT DATA;

void InitPinFunction(void){
	int i;
	for (i=0;i<NUM_PINS;i++){
		DATA.FUNCTION[i].HAS_ANALOG_IN=FALSE;
		DATA.FUNCTION[i].HAS_PWM=FALSE;
		DATA.FUNCTION[i].HAS_UART=FALSE;
		DATA.FUNCTION[i].HAS_SPI=FALSE;
		DATA.FUNCTION[i].HAS_COUNTER_INPUT= FALSE;
		DATA.FUNCTION[i].HAS_COUNTER_OUTPUT= FALSE;
		DATA.FUNCTION[i].HAS_DC_MOTOR = FALSE;
	}
	DATA.FUNCTION[0].HAS_SPI=TRUE;
	DATA.FUNCTION[1].HAS_SPI=TRUE;
	DATA.FUNCTION[2].HAS_SPI=TRUE;


	DATA.FUNCTION[4].HAS_PWM = TRUE;
	DATA.FUNCTION[5].HAS_PWM = TRUE;
	DATA.FUNCTION[6].HAS_PWM = TRUE;
	DATA.FUNCTION[7].HAS_PWM = TRUE;

	DATA.FUNCTION[4].HAS_DC_MOTOR = TRUE;
	DATA.FUNCTION[5].HAS_DC_MOTOR = TRUE;
	DATA.FUNCTION[6].HAS_DC_MOTOR = TRUE;
	DATA.FUNCTION[7].HAS_DC_MOTOR = TRUE;

	DATA.FUNCTION[8].HAS_DC_MOTOR = TRUE;
	DATA.FUNCTION[9].HAS_DC_MOTOR = TRUE;
	DATA.FUNCTION[10].HAS_DC_MOTOR = TRUE;
	DATA.FUNCTION[11].HAS_DC_MOTOR = TRUE;

	DATA.FUNCTION[8].HAS_ANALOG_IN = TRUE;
	DATA.FUNCTION[9].HAS_ANALOG_IN = TRUE;
	DATA.FUNCTION[10].HAS_ANALOG_IN = TRUE;
	DATA.FUNCTION[11].HAS_ANALOG_IN = TRUE;

	DATA.FUNCTION[12].HAS_ANALOG_IN = TRUE;
	DATA.FUNCTION[13].HAS_ANALOG_IN = TRUE;
	DATA.FUNCTION[14].HAS_ANALOG_IN = TRUE;
	DATA.FUNCTION[15].HAS_ANALOG_IN = TRUE;

	DATA.FUNCTION[16].HAS_UART =TRUE;
	DATA.FUNCTION[17].HAS_UART =TRUE;

	//Home buttons
	DATA.FUNCTION[0].HAS_COUNTER_INPUT = TRUE;
	DATA.FUNCTION[1].HAS_COUNTER_INPUT = TRUE;
	DATA.FUNCTION[2].HAS_COUNTER_INPUT = TRUE;
	DATA.FUNCTION[3].HAS_COUNTER_INPUT = TRUE;

	DATA.FUNCTION[0].HAS_COUNTER_OUTPUT = TRUE;
	DATA.FUNCTION[1].HAS_COUNTER_OUTPUT = TRUE;
	DATA.FUNCTION[2].HAS_COUNTER_OUTPUT = TRUE;
	DATA.FUNCTION[3].HAS_COUNTER_OUTPUT = TRUE;
	//Interuptibles

	DATA.FUNCTION[17].HAS_COUNTER_INPUT = TRUE;
	DATA.FUNCTION[19].HAS_COUNTER_INPUT = TRUE;
	DATA.FUNCTION[21].HAS_COUNTER_INPUT = TRUE;
	DATA.FUNCTION[23].HAS_COUNTER_INPUT = TRUE;

	//Direction
	DATA.FUNCTION[16].HAS_COUNTER_INPUT = TRUE;
	DATA.FUNCTION[18].HAS_COUNTER_INPUT = TRUE;
	DATA.FUNCTION[20].HAS_COUNTER_INPUT = TRUE;
	DATA.FUNCTION[22].HAS_COUNTER_INPUT = TRUE;

	//Interuptibles
	DATA.FUNCTION[17].HAS_COUNTER_OUTPUT = TRUE;
	DATA.FUNCTION[19].HAS_COUNTER_OUTPUT = TRUE;
	DATA.FUNCTION[21].HAS_COUNTER_OUTPUT = TRUE;
	DATA.FUNCTION[23].HAS_COUNTER_OUTPUT = TRUE;

	//Direction
	DATA.FUNCTION[16].HAS_COUNTER_OUTPUT = TRUE;
	DATA.FUNCTION[18].HAS_COUNTER_OUTPUT = TRUE;
	DATA.FUNCTION[20].HAS_COUNTER_OUTPUT = TRUE;
	DATA.FUNCTION[22].HAS_COUNTER_OUTPUT = TRUE;
}
static BowlerPacketMini mini;
BOOL pinHasFunction(BYTE pin, BYTE function){
	mini.use.data[0] = pin;
	getFunctionList((BowlerPacket *)&mini);
	int i;
	for(i=0;i<mini.use.head.DataLegnth-4;i++){
		if(function == mini.use.data[i]){
			return TRUE;
		}
	}
	return FALSE;
}

void getFunctionList(BowlerPacket * Packet){
	int chan = Packet->use.data[0];

	int index =0;
	Packet->use.data[index++]=IS_DI;
	Packet->use.data[index++]=IS_DO;
	Packet->use.data[index++]=IS_SERVO;

	if(chan == 16){
		Packet->use.data[index++]=IS_UART_TX	;
	}
	if(chan == 17){
		Packet->use.data[index++]=IS_UART_RX	;
	}

	if(chan == 23){
		Packet->use.data[index++]=IS_PPM_IN	;
	}
	if(chan == 0){
			Packet->use.data[index++]=IS_SPI_SCK	;
			Packet->use.data[index++]=IS_COUNTER_INPUT_HOME	;
			Packet->use.data[index++]=IS_COUNTER_OUTPUT_HOME	;
		}
	if(chan == 1){
				Packet->use.data[index++]=IS_SPI_MISO		;
				Packet->use.data[index++]=IS_COUNTER_INPUT_HOME		;
				Packet->use.data[index++]=IS_COUNTER_OUTPUT_HOME		;
			}
	if(chan == 2){
				Packet->use.data[index++]=IS_SPI_MOSI		;
				Packet->use.data[index++]=IS_COUNTER_INPUT_HOME	;
				Packet->use.data[index++]=IS_COUNTER_OUTPUT_HOME		;
			}
	if(chan == 3){
				Packet->use.data[index++]=IS_COUNTER_INPUT_HOME	;
				Packet->use.data[index++]=IS_COUNTER_OUTPUT_HOME		;
			}

	switch(chan){
	case 8:
	case 9:
	case 10:
	case 11:
		Packet->use.data[index++]=IS_DC_MOTOR_DIR;
	case 12:
	case 13:
	case 14:
	case 15:
		Packet->use.data[index++]=IS_ANALOG_IN;
		break;
	}
	switch(chan){
		case 4:
		case 5:
		case 6:
		case 7:
			Packet->use.data[index++]=IS_PWM;
			Packet->use.data[index++]=IS_DC_MOTOR_VEL;
			break;
		}
	switch(chan){
		case 23:
		case 21:
		case 19:
		case 17:
			Packet->use.data[index++]=IS_COUNTER_INPUT_INT;
			Packet->use.data[index++]=IS_COUNTER_OUTPUT_INT;
			break;
		}
	switch(chan){
		case 22:
		case 20:
		case 18:
		case 16:
			Packet->use.data[index++]=IS_COUNTER_INPUT_DIR;
			Packet->use.data[index++]=IS_COUNTER_OUTPUT_DIR;
			break;
		}
	Packet->use.head.DataLegnth=4+index;

}
