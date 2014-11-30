#include "UserApp_avr.h"

#define NUM_BLOCKS (NUM_PINS/BLOCK_SIZE)

//#define NUM_SERVO (NUM_PINS/NUM_BLOCKS)

#define dataTableSize (BLOCK_SIZE)

#define MIN_SERVO 6

typedef struct _InteruptServoData{
	uint8_t positionTemp[12];
	uint8_t blockIndex;
	ServoState servoStateMachineCurrentState;
} InteruptServoData;

InteruptServoData blockData [2];

//INTERPOLATE_DATA velocity[dataTableSize];
//uint8_t positionTemp[dataTableSize+1];
//uint8_t sort[dataTableSize];
//uint8_t lastValue=0;
//uint8_t sortedIndex = 0;
//uint8_t blockIndex = 0;

//static ServoState servoStateMachineCurrentState = STARTLOOP;
static uint32_t current=0;

//uint8_t TCCR1Btmp=0;

//#define CurrentIndex (blockIndex *BLOCK_SIZE )

void startServoLoops(){

	setServoTimer(0, 64);
	setServoTimer(1, 128);
}

void runSort(){
    int block=0,bIndex=0,pin;
    for(bIndex=0;bIndex<12;bIndex++){
    	for(block=0;block<2;block++){
    		pin = bIndex + (block*12);
			if(GetChannelMode(pin) == IS_SERVO)
				blockData[block].positionTemp[bIndex]=getBcsIoDataTable(pin)->PIN.currentValue & 0x000000ff;
			else
				blockData[block].positionTemp[bIndex] = 0;
			blockData[block].blockIndex = 0;
    	}
    }


}

void printSortedData(){
//    int x;

//    println_I("Servo State: ");p_int_I(servoStateMachineCurrentState);
//    println_I(" block: ");p_int_I(blockIndex);
//    println_I(" sort index: ");p_int_I(sortedIndex);
//    println_I(" last value: ");p_int_I(lastValue);
//    println_I(" time: ");p_fl_I(getMs()/1000.0);
//    println_I(" Comp 1A: ");p_int_I(OCR1A);
//    println_I(" Comp 1B: ");p_int_I(OCR1B);
//    println_I(" TCNT1: ");p_int_I(TCNT1);
//    println_I(" TCCR1A: ");p_int_I(TCCR1A);
//    println_I(" TCCR1B: ");p_int_I(TCCR1B);
//    println_I(" TCCR1C: ");p_int_I(TCCR1C);
//    println_I(" TIFR1: ");p_int_I(TIFR1);
//    println_I(" TIMSK1: ");p_int_I(TIMSK1);
//    println_I(" TIMSK1_ICIE1: ");p_int_I(TIMSK1bits._ICIE1);
//    println_I(" TIMSK1_OCIE1A: ");p_int_I(TIMSK1bits._OCIE1A);
//    println_I(" TIMSK1_OCIE1B: ");p_int_I(TIMSK1bits._OCIE1B);
//    println_I(" TIMSK1_TOIE1: ");p_int_I(TIMSK1bits._TOIE1);
//
//
//    println_I("Servo Data \r\nRaw data \t[ ");
//
//    for(x=0;x<dataTableSize;x++){
//        p_int_I(positionTemp[x]);print_I(" , ");
//    }
//    print_I(" ] ");
//
//    print_I("\r\nSorted index\t[ ");
//
//    for(x=0;x<dataTableSize;x++){
//        p_int_I(sort[x]);print_I(" , ");
//    }
//    print_I(" ] ");
//
//    print_I("\r\nSorted Data\t[ ");
//
//    for(x=0;x<dataTableSize;x++){
//        p_int_I(positionTemp[sort[x]]);print_I(" , ");
//    }
//    print_I(" ] ");
//    print_I("\r\nBlock index\t[ ");
//
//        for(x=0;x<dataTableSize;x++){
//            p_int_I(x + (blockIndex*BLOCK_SIZE));print_I(" , ");
//        }
//        print_I(" ] ");

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
//    if(target < 5 || target >= (0x0000ffff-5)  ){
//    	//println_E("Edge: ");prHEX32(target,ERROR_PRINT);
//    	return 5;
//    }
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

ISR(TIMER1_COMPB_vect){//timer 1B compare interrupt
	current = TCNT1;// store the state
	servoTimerEvent(0);
}

ISR(TIMER1_COMPA_vect){//timer 1A compare interrupt
	current = TCNT1;// store the state
	servoTimerEvent(1);
}

void stopServos(){
	TIMSK1bits._OCIE1B=0;
}

//
//boolean setUpNextServo(){
//
//    int diff = positionTemp[sort[sortedIndex]] - lastValue;
//    lastValue = positionTemp[sort[sortedIndex]];
//    if(diff<0 || sortedIndex<0 || sortedIndex>=dataTableSize){
//        setPrintLevelErrorPrint();
//        println_E("Servo.c: Something is wrong!! Current minus last value is less then 0\r\n");
//        setPrintLevelInfoPrint();
//        printSortedData();
//        while(1);
//    }
//    if(diff>MIN_SERVO){
//        setServoTimer(diff);
//        return true;
//    }
//    //Fall through for pin shut off
//    return false;
//}



void servoTimerEvent(int block)
{

	FlagBusy_IO=1;

        switch(blockData[block].servoStateMachineCurrentState){
            case STARTLOOP:
                pinOn( blockData[block].blockIndex + (block*12) );
                //1ms delay for all servos
            	setServoTimer(block,255 + blockData[block].positionTemp[blockData[block].blockIndex]);// put the 128 value exactly at 1.5ms
            	blockData[block].servoStateMachineCurrentState = TIME;
                break;

            case TIME:
				pinOff(blockData[block].blockIndex + (block*12) );
//				blockData[block].servoStateMachineCurrentState = FINISH;

                //If block is now done, reset the block index and sort
                /* no break */
//
//            case FINISH:
            	blockData[block].servoStateMachineCurrentState = STARTLOOP;

            	blockData[block].blockIndex++;
            	if(blockData[block].blockIndex == 12){
            		// this resets the block Index
            		blockData[block].blockIndex=0;
            		if(block == 1){
            			// Interpolate position
            			runLinearInterpolationServo(	0,
            			            					NUM_PINS);
            			// sort values for next loop
            			runSort();
            			startServoLoops();
            		}else{
            			// do not re-start the loops after block 0 ends, is should end first, then block 1 half a ms later
            		}

            	}else{
            		// make the timer loop consistant by subtracting the on time from the off time
            		setServoTimer(block,255 - blockData[block].positionTemp[blockData[block].blockIndex-1] + 128);
            	}
                break;
        }
        if(TCNT1 < current )
        	TCNT1 = current; // re-load the state value

    	FlagBusy_IO=0;
}




