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

ServoState servoStateMachineCurrentState = LOW;

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

void setServoTimer(int32_t value){
	int current = TCNT1;
	//uint32_t ivalue =(uint32_t) (value * 2307.0);// scale factor

    if(value<1)
        value = 1;
    if(value>0xffff){
		println_E("Maxed timer to: ");prHEX32(value,ERROR_PRINT);
        value = 0xffff;
    }
    int target = value +current;
    if(target>=0xffff){
    	target -=0xffff;
    }
    if(target>=0xffff){
		println_E("Setting timer to: ");prHEX32(value,ERROR_PRINT);
		print_E(" reg ");prHEX16(target,ERROR_PRINT);
    }
    TIMSK1bits._OCIE1A=0;
    OCR1A = target & 0xffff;
    TIMSK1bits._OCIE1A=1;

}


boolean pinState= false;
ISR(TIMER1_COMPA_vect){//timer 1A compare interrupt

//	servoTimerEvent();

	pinState= pinState?false:true;
	SetDIO(11,pinState?ON:OFF);
	setTimerServoTicks(128+(getBcsIoDataTable(11)->PIN.currentValue&0x000000ff));

	TIFR1bits._OCF1A=0;
}

void stopServos(){
	//TIMSK1bits._OCIE1A=0;
}
void setTimerNextBlockTime(){
	setTimerServoTicks(128);//1ms
    servoStateMachineCurrentState = LOW;
}

void setTimerLowTime(){
    //setServoTimer(300*(18));
	setServoTimer((18i -((3i*NUM_BLOCKS)+1))*2307i);
    servoStateMachineCurrentState = LOW;
    blockIndex=0;
}

void setTimerPreTime(){
	setTimerServoTicks(128);//1ms
    servoStateMachineCurrentState = PRETIME;
}

void setTimerServoTicks(int value){
    setServoTimer(value*9);
    servoStateMachineCurrentState = TIME;
}

#define MIN_SERVO 1


boolean setUpNextServo(){

    int diff = positionTemp[sort[sortedIndex]] - lastValue;
    lastValue = positionTemp[sort[sortedIndex]];
    if(diff<0){
        setPrintLevelErrorPrint();
        println_E("Servo.c: Something is wrong!! Current minus last value is less then 0\r\n");
        setPrintLevelInfoPrint();
        printSortedData();
        while(1);
    }

    if(diff>MIN_SERVO){
        setTimerServoTicks(diff);
        return true; 
    }
    //Fall through for pin shut off
    servoStateMachineCurrentState = TIME;
    return false; 
}

void stopCurrentServo(){
    pinOff(sort[sortedIndex]+ (blockIndex*BLOCK_SIZE));
    sortedIndex++;
    if(sortedIndex == dataTableSize){
        servoStateMachineCurrentState = FINISH;
        //fall through to finish
    }
}

void servoTimerEvent()
{
	uint8_t start;
	uint8_t stop;
        //mPORTDToggleBits(BIT_3);
	//StartCritical();
        stopServos();
        int j;
        switch(servoStateMachineCurrentState){
            case LOW:
            	start=blockIndex*BLOCK_SIZE;
            	stop=(blockIndex*BLOCK_SIZE)+BLOCK_SIZE;
            	runLinearInterpolationServo(start,stop);
                runSort();
                for (j=0;j<NUM_SERVO;j++){
                    pinOn(j+ (blockIndex*BLOCK_SIZE));
                }
                lastValue = 0;
                sortedIndex=0;

                //1ms delay for all servos
                setTimerPreTime();
                return;
            case PRETIME:
                if(setUpNextServo())
                    return;
                    /* no break */
            case TIME:
                stopCurrentServo();
                if(servoStateMachineCurrentState == TIME){
                    if(setUpNextServo() == false) {
                        //fast stop for channels with the same value
                        servoTimerEvent();
                    }
                }
                //If there are still more channels to be turned off after the recoursion, break
                if(servoStateMachineCurrentState != FINISH)
                    return;
                    /* no break */

            case FINISH:
            	blockIndex++;
            	if(blockIndex == NUM_BLOCKS)
            		setTimerLowTime();
            	else{
            		setTimerNextBlockTime();
            	}
                return;
        }
        //EndCritical();
}




