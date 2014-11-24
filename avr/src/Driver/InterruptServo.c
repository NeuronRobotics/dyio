#include "UserApp_avr.h"

#define NUM_BLOCKS (NUM_PINS/BLOCK_SIZE)

#define NUM_SERVO (NUM_PINS/NUM_BLOCKS)

#define dataTableSize (BLOCK_SIZE)

#define MIN_SERVO 3


//INTERPOLATE_DATA velocity[dataTableSize];
uint8_t positionTemp[dataTableSize+1];
uint8_t sort[dataTableSize];
uint8_t lastValue=0;
uint8_t sortedIndex = 0;
uint8_t blockIndex = 0;

static ServoState servoStateMachineCurrentState = STARTLOOP;
static uint32_t current=0;
static int j;
//uint8_t TCCR1Btmp=0;

#define CurrentIndex (blockIndex *BLOCK_SIZE )

void runSort(){
    int i=0,k=0,x;
    int current;
    for(k=0;k<dataTableSize;k++){
        sort[k]=dataTableSize;
    }
    for(x=0;x<dataTableSize;x++){
    	if(GetChannelMode(x) == IS_SERVO)
    		positionTemp[x]=getBcsIoDataTable(x + (blockIndex*BLOCK_SIZE))->PIN.currentValue & 0x000000ff;
    	else
    		positionTemp[x] = 0;
    }
    for(x=0;x<dataTableSize;x++){
        current = 256;
        for(i=0;i<dataTableSize;i++){
            int used= false; 
            for(k=0;k<dataTableSize;k++){
                if(sort[k]==i){
                    used=true; 
                }
            }
            if(positionTemp[i]<current && !used){
                sort[x]=i;

                current = positionTemp[i];
            }
        }
    }

}

void printSortedData(){
    int x;

    println_I("Servo State: ");p_int_I(servoStateMachineCurrentState);
    println_I(" block: ");p_int_I(blockIndex);
    println_I(" sort index: ");p_int_I(sortedIndex);
    println_I(" last value: ");p_int_I(lastValue);
    println_I(" time: ");p_fl_I(getMs()/1000.0);
    println_I(" Comp 1A: ");p_int_I(OCR1A);
    println_I(" Comp 1B: ");p_int_I(OCR1B);
    println_I(" TCNT1: ");p_int_I(TCNT1);
    println_I(" TCCR1A: ");p_int_I(TCCR1A);
    println_I(" TCCR1B: ");p_int_I(TCCR1B);
    println_I(" TCCR1C: ");p_int_I(TCCR1C);
    println_I(" TIFR1: ");p_int_I(TIFR1);
    println_I(" TIMSK1: ");p_int_I(TIMSK1);
    println_I(" TIMSK1_ICIE1: ");p_int_I(TIMSK1bits._ICIE1);
    println_I(" TIMSK1_OCIE1A: ");p_int_I(TIMSK1bits._OCIE1A);
    println_I(" TIMSK1_OCIE1B: ");p_int_I(TIMSK1bits._OCIE1B);
    println_I(" TIMSK1_TOIE1: ");p_int_I(TIMSK1bits._TOIE1);


    println_I("Servo Data \r\nRaw data \t[ ");

    for(x=0;x<dataTableSize;x++){
        p_int_I(positionTemp[x]);print_I(" , ");
    }
    print_I(" ] ");

    print_I("\r\nSorted index\t[ ");

    for(x=0;x<dataTableSize;x++){
        p_int_I(sort[x]);print_I(" , ");
    }
    print_I(" ] ");

    print_I("\r\nSorted Data\t[ ");

    for(x=0;x<dataTableSize;x++){
        p_int_I(positionTemp[sort[x]]);print_I(" , ");
    }
    print_I(" ] ");
    print_I("\r\nBlock index\t[ ");

        for(x=0;x<dataTableSize;x++){
            p_int_I(x + (blockIndex*BLOCK_SIZE));print_I(" , ");
        }
        print_I(" ] ");

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
    if(target == 0 || target >= 0x0000ffff  ){
    	println_E("Edge: ");prHEX32(target,ERROR_PRINT);
    	return 1;
    }
    return target & 0x0000ffff;
}

void setServoLoopTimer(uint32_t value){
    OCR1A = calcTimer( value);
    TIMSK1bits._OCIE1A=1;// Pin timer
}

void setServoTimer(uint32_t value){
    OCR1B = calcTimer( value);
    TIMSK1bits._OCIE1B=1;// Pin timer
}

ISR(TIMER1_COMPB_vect){//timer 1B compare interrupt
	servoTimerEvent();
}

ISR(TIMER1_COMPA_vect){//timer 1A compare interrupt
	servoTimerEvent();
}

void stopServos(){
	TIMSK1bits._OCIE1B=0;
}


boolean setUpNextServo(){

    int diff = positionTemp[sort[sortedIndex]] - lastValue;
    lastValue = positionTemp[sort[sortedIndex]];
    if(diff<0 || sortedIndex<0 || sortedIndex>=dataTableSize){
        setPrintLevelErrorPrint();
        println_E("Servo.c: Something is wrong!! Current minus last value is less then 0\r\n");
        setPrintLevelInfoPrint();
        printSortedData();
        while(1);
    }
    if(diff>MIN_SERVO){
        setServoTimer(diff);
        return true; 
    }
    //Fall through for pin shut off
    return false; 
}



void servoTimerEvent()
{
	FlagBusy_IO=1;
	TCCR1Bbits._CS=0;// stop the clock
	current = TCNT1;// store the state
	TIFR1bits._OCF1A=0;// clear the interrupt flag
	TIFR1bits._OCF1B=0;// clear the interrupt flag

        switch(servoStateMachineCurrentState){
            case STARTLOOP:
                for (j=0;j<NUM_SERVO;j++){
                    pinOn(j+ CurrentIndex);
                }

                //1ms delay for all servos
            	setServoTimer(234);// put the 128 value exactly at 1.5ms
                servoStateMachineCurrentState = PRETIME;
                break;
            case PRETIME:
            	servoStateMachineCurrentState = TIME;
                if(setUpNextServo() == true)
                    break;
                    /* no break */
            case TIME:

                while(servoStateMachineCurrentState == TIME){
                	//stopCurrentServo();
                    pinOff(sort[sortedIndex]+ CurrentIndex);
                    sortedIndex++;
                    if(sortedIndex == dataTableSize){
                        servoStateMachineCurrentState = FINISH;
                        //fall through to finish
                    }
                	if(servoStateMachineCurrentState == TIME){
						if(setUpNextServo() == true) {
							//fast stop for channels with the same value
							break;
						}
                	}
                }
                if(servoStateMachineCurrentState == TIME)
                	break;

                //If block is now done, reset the block index and sort
                /* no break */

            case FINISH:
            	 for (j=0;j<NUM_SERVO;j++){
            		 pinOff(j+ CurrentIndex);
				}
            	blockIndex++;
            	if(blockIndex == NUM_BLOCKS){
            		// this resets the block Index
            	    blockIndex=0;
            	}
                lastValue = 0;
                sortedIndex=0;
            	// Interpolate position
            	runLinearInterpolationServo(	CurrentIndex,
            									CurrentIndex+BLOCK_SIZE);
            	// sort values for next loop
				runSort();
				setServoLoopTimer(255*5);
				servoStateMachineCurrentState = STARTLOOP;
				stopServos();
                break;
        }
    	TCNT1 = current; // re-load the state value
    	TCCR1Bbits._CS = 2;//  value CLslk I/O/8 (From prescaler)
    	FlagBusy_IO=0;
}




