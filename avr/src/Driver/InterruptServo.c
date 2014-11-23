#include "UserApp_avr.h"

#define SERVO_BOUND 		0

#define NUM_BLOCKS (NUM_PINS/BLOCK_SIZE)

#define NUM_SERVO (NUM_PINS/NUM_BLOCKS)

#define dataTableSize (NUM_SERVO)



//INTERPOLATE_DATA velocity[dataTableSize];
uint8_t positionTemp[dataTableSize];
uint8_t sort[dataTableSize];
uint8_t lastValue=0;
uint8_t sortedIndex = 0;
uint8_t blockIndex = 0;

ServoState servoStateMachineCurrentState = STARTLOOP;
uint32_t current=0;
uint8_t TCCR1Btmp=0;

void runSort(){
    int i=0,k=0,x;
    int current;
    for(k=0;k<dataTableSize;k++){
        sort[k]=dataTableSize;
    }
    for(x=0;x<dataTableSize;x++){
        positionTemp[x]=getBcsIoDataTable(x + (blockIndex*BLOCK_SIZE))->PIN.currentValue & 0x000000ff;
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
    print_I("Servo Data \r\n[ ");

    for(x=0;x<dataTableSize;x++){
        p_int_I(positionTemp[x]);print_I(" , ");
    }
    print_I(" ] ");

    print_I("\r\nS[ ");

    for(x=0;x<dataTableSize;x++){
        p_int_I(sort[x]);print_I(" , ");
    }
    print_I(" ] ");

    print_I("\r\nP[ ");

    for(x=0;x<dataTableSize;x++){
        p_int_I(positionTemp[sort[x]]);print_I(" , ");
    }
    print_I(" ] ");
    print_I("\r\nI[ ");

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
    return target & 0x0000ffff;
}

void setServoLoopTimer(uint32_t value){
    OCR1B = calcTimer( value);
    TIMSK1bits._OCIE1B=1;// Pin timer
}

void setServoTimer(uint32_t value){
    OCR1A = calcTimer( value);
    TIMSK1bits._OCIE1A=1;// Pin timer
}

ISR(TIMER1_COMPB_vect){//timer 1B compare interrupt
	FlagBusy_IO=1;
	current = TCNT1;// store the state
	TIFR1bits._OCF1B=0;// clear the interrupt flag
	TCCR1Btmp =TCCR1B;
	TCCR1Bbits._CS=0;// stop the clock

	servoStateMachineCurrentState = STARTLOOP;
	servoTimerEvent();
	setServoLoopTimer(255*8);
	//EndCritical();

	TCCR1B = TCCR1Btmp; // re-start the clock
	TCNT1 = current; // re-load the state value
	FlagBusy_IO=0;
}

ISR(TIMER1_COMPA_vect){//timer 1A compare interrupt
	FlagBusy_IO=1;
	current = TCNT1;// store the state
	TIFR1bits._OCF1A=0;// clear the interrupt flag
	TCCR1Btmp =TCCR1B;
	TCCR1Bbits._CS=0;// stop the clock

	servoTimerEvent();

	//EndCritical();
	TCCR1B = TCCR1Btmp; // re-start the clock
	TCNT1 = current; // re-load the state value
	FlagBusy_IO=0;
}

void stopServos(){
	TIMSK1bits._OCIE1A=0;
}



#define MIN_SERVO 1


boolean setUpNextServo(){

    int diff = positionTemp[sort[sortedIndex]] - lastValue;
    lastValue = positionTemp[sort[sortedIndex]];
//    if(diff<0){
//        setPrintLevelErrorPrint();
//        println_E("Servo.c: Something is wrong!! Current minus last value is less then 0\r\n");
//        setPrintLevelInfoPrint();
//        printSortedData();
//        while(1);
//    }
    servoStateMachineCurrentState = TIME;
    if(diff>MIN_SERVO){
        //setTimerServoTicks(diff);
        setServoTimer(diff);
        return true; 
    }
    //Fall through for pin shut off
    return false; 
}

void stopCurrentServo(){
//    pinOff(sort[sortedIndex]+ (blockIndex*BLOCK_SIZE));
//    sortedIndex++;
//    if(sortedIndex == dataTableSize){
//        servoStateMachineCurrentState = FINISH;
//        //fall through to finish
//    }
}

void servoTimerEvent()
{
//	uint8_t start;
//	uint8_t stop;
        int j;
        switch(servoStateMachineCurrentState){
            case STARTLOOP:
                for (j=0;j<NUM_SERVO;j++){
                    pinOn(j+ (blockIndex*BLOCK_SIZE));
                }

                lastValue = 0;
                sortedIndex=0;

                //1ms delay for all servos
            	setServoTimer(255);//1ms
                servoStateMachineCurrentState = PRETIME;
                return;
            case PRETIME:
                if(setUpNextServo())
                    return;
                    /* no break */
            case TIME:

                while(servoStateMachineCurrentState == TIME){
                	//stopCurrentServo();
                    pinOff(sort[sortedIndex]+ (blockIndex*BLOCK_SIZE));
                    sortedIndex++;
                    if(sortedIndex == dataTableSize){
                        servoStateMachineCurrentState = FINISH;
                        //fall through to finish
                    }
                	if(servoStateMachineCurrentState == TIME){
						if(setUpNextServo() == true) {
							//fast stop for channels with the same value
							return;
						}
                	}
                }

                //If there are still more channels to be turned off after the stops, break
                if(servoStateMachineCurrentState != FINISH)
                    return;
                    /* no break */

            case FINISH:
            	blockIndex++;
            	if(blockIndex == NUM_BLOCKS){
            		// this resets the block Index
            	    blockIndex=0;
            	}
            	stopServos();

            	// Interpolate position
            	runLinearInterpolationServo(	blockIndex*BLOCK_SIZE,
												(blockIndex*BLOCK_SIZE)+BLOCK_SIZE);
            	// sort values for next loop
				runSort();
                return;
        }
        //
}




