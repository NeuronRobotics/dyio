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
static uint32_t current=0;
#define OFFSET (255-1)

void startServoLoops(){
	current = TCNT1;// store the state
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
	value = value *9;
    if(value>0x0000ffff){
		println_E("Maxed timer to: ");prHEX32(value,ERROR_PRINT);
        value = 0x0000ffff;
    }
    uint32_t target = value +current;
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
	current = TCNT1;// store the state
	servoTimerEvent(0);
	TCNT1 = current; // re-load the state value
}

ISR(TIMER1_COMPA_vect){//timer 1A compare interrupt
	current = TCNT1;// store the state
	servoTimerEvent(1);
    TCNT1 = current; // re-load the state value
}



void servoTimerEvent(int block)
{

	FlagBusy_IO=1;
	int time;
        switch(blockData[block].servoStateMachineCurrentState){
            case STARTLOOP:
                pinOn( blockIndex + (block*12) );
                //1ms delay for all servos
            	setServoTimer(block,255 + blockData[block].positionTemp[blockIndex]);// put the 128 value exactly at 1.5ms
            	blockData[block].servoStateMachineCurrentState = TIME;
                break;

            case TIME:
				pinOff(blockIndex + (block*12) );
				stopServoTimer(block);
                //If block is now done, reset the block index and sort
        		// make the timer loop consistant by subtracting the on time from the off time
        		//setServoTimer(block,(255 - blockData[block].positionTemp[blockData[block].blockIndex]) + 32);
        		blockData[block].servoStateMachineCurrentState = FINISH;
        		if(	blockData[0].servoStateMachineCurrentState ==FINISH &&
					blockData[1].servoStateMachineCurrentState ==FINISH ){
        			time = (255 - blockData[1].positionTemp[blockIndex]);
        			blockIndex++;
					if(blockIndex == 12){
						blockData[block].servoStateMachineCurrentState = FINISH;
						// this resets the block Index
						blockIndex=0;
						// Interpolate position
						runLinearInterpolationServo(	0,
														NUM_PINS);
						// sort values for next loop
						runSort(0);
						runSort(1);
					}
        			blockData[0].servoStateMachineCurrentState = STARTLOOP;
        			blockData[1].servoStateMachineCurrentState = STARTLOOP;

        			setServoTimer(0, time+32);
        			setServoTimer(1, time+32+OFFSET);
				}

                break;
            case FINISH:
            	//blockData[block].servoStateMachineCurrentState = STARTLOOP;
            	break;
        }

    	FlagBusy_IO=0;
}




