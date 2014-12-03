#include "UserApp_avr.h"

#define NUM_BLOCKS (NUM_PINS/BLOCK_SIZE)

//#define NUM_SERVO (NUM_PINS/NUM_BLOCKS)

#define dataTableSize (BLOCK_SIZE)

#define MIN_SERVO 6
uint8_t blockIndex = 0;
typedef struct _InteruptServoData{
	uint8_t positionTemp[12];

	ServoState servoStateMachineCurrentState;
} InteruptServoData;
InteruptServoData blockData [2];
static uint32_t currentTimer=0;
#define OFFSET (255+15+21)

void startServoLoops(){
	currentTimer = TCNT1;// store the state
	blockData[0].servoStateMachineCurrentState = STARTLOOP;
	blockData[1].servoStateMachineCurrentState = STARTLOOP;
	setServoTimer(0, 32);
	setServoTimer(1, 32+OFFSET);
	blockIndex = 0;
}

void runSort(uint8_t block){
    int bIndex=0,pin;
    for(bIndex=0;bIndex<12;bIndex++){
		pin = bIndex + (block*12);
		if(GetChannelMode(pin) == IS_SERVO)
			blockData[block].positionTemp[bIndex]=getBcsIoDataTable(pin)->PIN.currentValue & 0x000000ff;
		else
			blockData[block].positionTemp[bIndex] = 0;
    }
}

uint32_t calcTimer(uint32_t value){
	if(value<=1)
		value=1;
	value = value * 8;
    if(value>0x0000ffff){
		println_E("Maxed timer to: ");prHEX32(value,ERROR_PRINT);
        value = 0x0000ffff;
    }
    uint32_t target = value +currentTimer;
    if(target>0x0000ffff){
    	target -=(0x0000ffff);
    }
    if(target < 5 ){
    	//println_E("Edge: ");prHEX32(target,ERROR_PRINT);
    	return 5;
    }
    return target & 0x0000ffff;
}


void setServoTimer(uint8_t block, uint32_t value){
	if(block == 0){
		OCR1B = calcTimer( value);
		TIMSK1bits._OCIE1B=1;// Pin timer
	}else{
		OCR1A = calcTimer( value);
		TIMSK1bits._OCIE1A=1;// Pin timer
	}

}

void stopServoTimer(uint8_t block){
	if(block == 0){
		TIMSK1bits._OCIE1B=0;// Pin timer
	}else{
		TIMSK1bits._OCIE1A=0;// Pin timer
	}

}

ISR(TIMER1_COMPB_vect){//timer 1B compare interrupt
	currentTimer = TCNT1;// store the state
	servoTimerEvent(0);
	/*
	 * When an interrupt occurs, the Global Interrupt Enable I-bit is cleared and all interrupts are dis-
	 * abled. The user software can write logic one to the I-bit to enable nested interrupts.
	 */
	EndCritical();
	int after = TCNT1;
	//
	if(currentTimer > after ){
		// roll over detect
		TCNT1 = 0xffff-5;
	}
	if((currentTimer < OCR1B && after > OCR1B) || (currentTimer > OCR1B && after < OCR1B)){
		// OCR1B detect
		TCNT1 = currentTimer - 1;
	}
	if((currentTimer < OCR1A && after > OCR1A)||(currentTimer > OCR1A && after < OCR1A)){
		// OCR1A detect
		TCNT1 = currentTimer - 1;
	}
}

ISR(TIMER1_COMPA_vect){//timer 1A compare interrupt
	currentTimer = TCNT1;// store the state
	servoTimerEvent(1);
	/*
	 * When an interrupt occurs, the Global Interrupt Enable I-bit is cleared and all interrupts are dis-
	 * abled. The user software can write logic one to the I-bit to enable nested interrupts.
	 */
	EndCritical();
	int after = TCNT1;
	//
	if(currentTimer > after ){
		// roll over detect
		TCNT1 = 0xffff-5;
	}
	if((currentTimer < OCR1B && after > OCR1B) || (currentTimer > OCR1B && after < OCR1B)){
		// OCR1B detect
		TCNT1 = currentTimer - 1;
	}
	if((currentTimer < OCR1A && after > OCR1A)||(currentTimer > OCR1A && after < OCR1A)){
		// OCR1A detect
		TCNT1 = currentTimer - 1;
	}
}

void updateServoValues(){
	int block;
	int pin;
	int32_t ip;
	for(block=0;block<2;block++){
		pin = blockIndex + (block*12);
		// Interpolate position
		ip =getInterpolatedPin(pin);
		if(GetChannelMode(blockIndex + (block*12)) == IS_SERVO)
			blockData[block].positionTemp[blockIndex]=ip & 0x000000ff;
		else
			blockData[block].positionTemp[blockIndex] = 0;
	}

}


void servoTimerEvent(int block)
{
	int flag = FlagBusy_IO;
	FlagBusy_IO=1;
	int time;
	switch(blockData[block].servoStateMachineCurrentState){
		case STARTLOOP:
			pinOn( blockIndex + (block*12) );
			//1ms delay for all servos
			setServoTimer(block,OFFSET + blockData[block].positionTemp[blockIndex]);// put the 128 value exactly at 1.5ms
			blockData[block].servoStateMachineCurrentState = TIME;
			break;

		case TIME:
			pinOff(blockIndex + (block*12) );
			stopServoTimer(block);
			//If block is now done, reset the block index and sort
			blockData[block].servoStateMachineCurrentState = FINISH;
			if(	blockData[0].servoStateMachineCurrentState ==FINISH &&
				blockData[1].servoStateMachineCurrentState ==FINISH ){
				time = (255 - blockData[1].positionTemp[blockIndex]);
				updateServoValues();
				blockIndex++;
				if(blockIndex == 12){
					// this resets the block Index
					blockIndex=0;
				}
				blockData[0].servoStateMachineCurrentState = STARTLOOP;
				blockData[1].servoStateMachineCurrentState = STARTLOOP;

				setServoTimer(0, time+64);
				setServoTimer(1, time+64+OFFSET-15);
			}

			break;
		case FINISH:
			//blockData[block].servoStateMachineCurrentState = STARTLOOP;
			break;
	}

	FlagBusy_IO=flag;
}




