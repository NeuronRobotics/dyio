#include "DyIO/DyIO_def.h"
#include "Namespace/Namespace_bcs_io.h"

DATA_STRUCT DATA[NUM_PINS];

void InitPinFunction(void){
	int i;
	for (i=0;i<NUM_PINS;i++){
		DATA[i].FUNCTION.HAS_ANALOG_IN=FALSE;
		DATA[i].FUNCTION.HAS_PWM=FALSE;
		DATA[i].FUNCTION.HAS_UART=FALSE;
		DATA[i].FUNCTION.HAS_SPI=FALSE;
		DATA[i].FUNCTION.HAS_COUNTER_INPUT= FALSE;
		DATA[i].FUNCTION.HAS_COUNTER_OUTPUT= FALSE;
		DATA[i].FUNCTION.HAS_DC_MOTOR = FALSE;
	}
	DATA[0].FUNCTION.HAS_SPI=TRUE;
	DATA[1].FUNCTION.HAS_SPI=TRUE;
	DATA[2].FUNCTION.HAS_SPI=TRUE;


	DATA[4].FUNCTION.HAS_PWM = TRUE;
	DATA[5].FUNCTION.HAS_PWM = TRUE;
	DATA[6].FUNCTION.HAS_PWM = TRUE;
	DATA[7].FUNCTION.HAS_PWM = TRUE;

	DATA[4].FUNCTION.HAS_DC_MOTOR = TRUE;
	DATA[5].FUNCTION.HAS_DC_MOTOR = TRUE;
	DATA[6].FUNCTION.HAS_DC_MOTOR = TRUE;
	DATA[7].FUNCTION.HAS_DC_MOTOR = TRUE;

	DATA[8].FUNCTION.HAS_DC_MOTOR = TRUE;
	DATA[9].FUNCTION.HAS_DC_MOTOR = TRUE;
	DATA[10].FUNCTION.HAS_DC_MOTOR = TRUE;
	DATA[11].FUNCTION.HAS_DC_MOTOR = TRUE;

	DATA[8].FUNCTION.HAS_ANALOG_IN = TRUE;
	DATA[9].FUNCTION.HAS_ANALOG_IN = TRUE;
	DATA[10].FUNCTION.HAS_ANALOG_IN = TRUE;
	DATA[11].FUNCTION.HAS_ANALOG_IN = TRUE;

	DATA[12].FUNCTION.HAS_ANALOG_IN = TRUE;
	DATA[13].FUNCTION.HAS_ANALOG_IN = TRUE;
	DATA[14].FUNCTION.HAS_ANALOG_IN = TRUE;
	DATA[15].FUNCTION.HAS_ANALOG_IN = TRUE;

	DATA[16].FUNCTION.HAS_UART =TRUE;
	DATA[17].FUNCTION.HAS_UART =TRUE;

	//Home buttons
	DATA[0].FUNCTION.HAS_COUNTER_INPUT = TRUE;
	DATA[1].FUNCTION.HAS_COUNTER_INPUT = TRUE;
	DATA[2].FUNCTION.HAS_COUNTER_INPUT = TRUE;
	DATA[3].FUNCTION.HAS_COUNTER_INPUT = TRUE;

	DATA[0].FUNCTION.HAS_COUNTER_OUTPUT = TRUE;
	DATA[1].FUNCTION.HAS_COUNTER_OUTPUT = TRUE;
	DATA[2].FUNCTION.HAS_COUNTER_OUTPUT = TRUE;
	DATA[3].FUNCTION.HAS_COUNTER_OUTPUT = TRUE;
	//Interuptibles

	DATA[17].FUNCTION.HAS_COUNTER_INPUT = TRUE;
	DATA[19].FUNCTION.HAS_COUNTER_INPUT = TRUE;
	DATA[21].FUNCTION.HAS_COUNTER_INPUT = TRUE;
	DATA[23].FUNCTION.HAS_COUNTER_INPUT = TRUE;

	//Direction
	DATA[16].FUNCTION.HAS_COUNTER_INPUT = TRUE;
	DATA[18].FUNCTION.HAS_COUNTER_INPUT = TRUE;
	DATA[20].FUNCTION.HAS_COUNTER_INPUT = TRUE;
	DATA[22].FUNCTION.HAS_COUNTER_INPUT = TRUE;

	//Interuptibles
	DATA[17].FUNCTION.HAS_COUNTER_OUTPUT = TRUE;
	DATA[19].FUNCTION.HAS_COUNTER_OUTPUT = TRUE;
	DATA[21].FUNCTION.HAS_COUNTER_OUTPUT = TRUE;
	DATA[23].FUNCTION.HAS_COUNTER_OUTPUT = TRUE;

	//Direction
	DATA[16].FUNCTION.HAS_COUNTER_OUTPUT = TRUE;
	DATA[18].FUNCTION.HAS_COUNTER_OUTPUT = TRUE;
	DATA[20].FUNCTION.HAS_COUNTER_OUTPUT = TRUE;
	DATA[22].FUNCTION.HAS_COUNTER_OUTPUT = TRUE;
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
