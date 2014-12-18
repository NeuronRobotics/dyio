/*
 * Abstract_bcs_io.c
 *
 *  Created on: Mar 21, 2013
 *      Author: hephaestus
 */

#include "Bowler/Bowler.h"
#include "Namespace/Namespace_bcs_io.h"


  int NumberOfIOChannels = 0;
  DATA_STRUCT * dataPtr = NULL;

boolean(*setChanelValueHWPtr)(uint8_t  , uint8_t, int32_t *, float);
boolean(*getChanelValueHWPtr)(uint8_t  , uint8_t*, int32_t *);
boolean(*setStreamHWPtr)(uint8_t  , uint8_t, uint8_t *);
boolean(*getStreamHWPtr)(uint8_t  , uint8_t*, uint8_t *);
boolean(*setAllChanelValueHWPtr)(int32_t *, float);
boolean(*getAllChanelValueHWPtr)(int32_t *);
boolean(*configChannelHWPtr)(uint8_t  , uint8_t, int32_t *);

void InitilizeBcsIo(int numPins,
					DATA_STRUCT * dataPtrLocal,
					boolean (*setChanelValueHWPtrLocal)(uint8_t,uint8_t,int32_t *,float),
					boolean (*getChanelValueHWPtrLocal)(uint8_t,uint8_t*,int32_t *),
					boolean (*setAllChanelValueHWPtrLocal)(int32_t *,float),
					boolean (*getAllChanelValueHWPtrLocal)(int32_t *),
					boolean (*configChannelHWPtrLocal)(uint8_t,uint8_t,int32_t *),
					boolean(*setStreamHWPtrLocal)(uint8_t  , uint8_t, uint8_t *),
					boolean(*getStreamHWPtrLocal)(uint8_t  , uint8_t*, uint8_t *)
) {
    if (numPins < 1
            ) {
        setPrintLevelErrorPrint();
        //println_E("Failed IO sanity check: failed initialization channels #");
        p_int_E(numPins);
        //println_E("Failed IO sanity check: failed initialization channels #");p_int_E(numPins);
        //FAIL sanity check
        while (1);
    }
    if (
            dataPtrLocal == NULL
            ) {
        setPrintLevelErrorPrint();
//#if !defined(__AVR_ATmega644P__) && !defined(__AVR_ATmega644PA__) && !defined(__AVR_ATmega324P__)
//        println_E("Failed IO sanity check: failed initialization dataPtrLocal");
//#endif
        //println_E("Failed IO sanity check: failed initialization dataPtrLocal");
        //FAIL sanity check
        while (1);
    }
    if (
            setChanelValueHWPtrLocal == NULL
            ) {
        setPrintLevelErrorPrint();
//#if !defined(__AVR_ATmega644P__) && !defined(__AVR_ATmega644PA__) && !defined(__AVR_ATmega324P__)
//        println_E("Failed IO sanity check: failed initialization setChanelValueHWPtrLocal");
//#endif
        //println_E("Failed IO sanity check: failed initialization setChanelValueHWPtrLocal");
        //FAIL sanity check
        while (1);
    }
    if (
            getChanelValueHWPtrLocal == NULL
            ) {
        setPrintLevelErrorPrint();
//#if !defined(__AVR_ATmega644P__) && !defined(__AVR_ATmega644PA__) && !defined(__AVR_ATmega324P__)
//        println_E("Failed IO sanity check: failed initialization getChanelValueHWPtrLocal");
//#endif
        //println_E("Failed IO sanity check: failed initialization getChanelValueHWPtrLocal");
        //FAIL sanity check
        while (1);
    }
    if (
            setAllChanelValueHWPtrLocal == NULL
            ) {
        setPrintLevelErrorPrint();
//#if !defined(__AVR_ATmega644P__) && !defined(__AVR_ATmega644PA__) && !defined(__AVR_ATmega324P__)
//        println_E("Failed IO sanity check: failed initialization setAllChanelValueHWPtrLocal");
//#endif
        //println_E("Failed IO sanity check: failed initialization setAllChanelValueHWPtrLocal");
        //FAIL sanity check
        while (1);
    }
    if (
            getAllChanelValueHWPtrLocal == NULL
            ) {
        setPrintLevelErrorPrint();
//#if !defined(__AVR_ATmega644P__) && !defined(__AVR_ATmega644PA__) && !defined(__AVR_ATmega324P__)
//        println_E("Failed IO sanity check: failed initialization getAllChanelValueHWPtrLocal");
//#endif
        //println_E("Failed IO sanity check: failed initialization getAllChanelValueHWPtrLocal");
        //FAIL sanity check
        while (1);
    }
    if (
            configChannelHWPtrLocal == NULL
            ) {
        setPrintLevelErrorPrint();
//#if !defined(__AVR_ATmega644P__) && !defined(__AVR_ATmega644PA__) && !defined(__AVR_ATmega324P__)
//        println_E("Failed IO sanity check: failed initialization configChannelHWPtrLocal");
//#endif
        //println_E("Failed IO sanity check: failed initialization configChannelHWPtrLocal");
        //FAIL sanity check
        while (1);

    }

    NumberOfIOChannels = numPins;
    dataPtr = dataPtrLocal;
    setChanelValueHWPtr = setChanelValueHWPtrLocal;
    getChanelValueHWPtr = getChanelValueHWPtrLocal;
    setAllChanelValueHWPtr = setAllChanelValueHWPtrLocal;
    getAllChanelValueHWPtr = getAllChanelValueHWPtrLocal;
    configChannelHWPtr = configChannelHWPtrLocal;
    setStreamHWPtr=setStreamHWPtrLocal;
    getStreamHWPtr=getStreamHWPtrLocal;
}

int GetNumberOfIOChannels() {
    return NumberOfIOChannels;
}

void _SetChannelMode(uint8_t pin,uint8_t mode ) {
    if (pin < 0 || pin > GetNumberOfIOChannels()) {
        return ;
    }
    //print_nnl("Set Channel Mode ",ERROR_PRINT);printMode(mode,ERROR_PRINT);
    getBcsIoDataTable(pin)->PIN.currentChannelMode = mode;
}

uint8_t GetChannelMode(uint8_t pin) {
    if (pin < 0 || pin > GetNumberOfIOChannels()) {
        return 0xff;
    }
    return getBcsIoDataTable(pin)->PIN.currentChannelMode;
}

RunEveryData * getPinsScheduler(int pin) {
    return & dataPtr[pin].asyncDataTimer;
}

DATA_STRUCT * getBcsIoDataTable(int pin) {
    if (dataPtr == NULL) {
        setPrintLevelErrorPrint();
//#if !defined(__AVR_ATmega644P__) && !defined(__AVR_ATmega644PA__) && !defined(__AVR_ATmega324P__)
//        println_E("Failed IO sanity check: no data table");
//#endif
        //println_E("Failed IO sanity check: no data table");
        //FAIL sanity check
        while (1);
    }
    return &dataPtr[pin];
}

boolean GetChannelModeFromPacket(BowlerPacket * Packet) {
    Packet->use.data[1] = GetChannelMode(Packet->use.data[0]);
    Packet->use.head.DataLegnth = 6;
    Packet->use.head.Method = BOWLER_POST;
    FixPacket(Packet);
    //printBowlerPacketDEBUG(Packet,WARN_PRINT);
    return true;
}

boolean GetAllChannelModeFromPacket(BowlerPacket * Packet) {
    int i;
    Packet->use.head.Method = BOWLER_POST;
    Packet->use.head.RPC=GetRPCValue("gacm");
    Packet->use.data[0] = GetNumberOfIOChannels();
    for (i = 0; i < GetNumberOfIOChannels(); i++) {
        Packet->use.data[1 + i] = GetChannelMode(i);
    }
    Packet->use.head.DataLegnth = 4 + GetNumberOfIOChannels()+1;
    FixPacket(Packet);
    //printBowlerPacketDEBUG(Packet,WARN_PRINT);
    return true;
}

boolean GetAsyncFromPacket(BowlerPacket * Packet) {
    Packet->use.head.Method = BOWLER_POST;
    Packet->use.data[1] = IsAsync(Packet->use.data[0]);
    Packet->use.head.DataLegnth = 4 + 2;
    FixPacket(Packet);
    return true;
}

boolean SetAsyncFromPacket(BowlerPacket * Packet) {
    Packet->use.head.Method = BOWLER_POST;
    setAsync(Packet->use.data[0], Packet->use.data[1]);
    Packet->use.head.DataLegnth = 4;
    FixPacket(Packet);
    return true;
}

boolean GetIOChannelCountFromPacket(BowlerPacket * Packet) {
    Packet->use.head.Method = BOWLER_POST;
    Packet->use.data[0] = 0;
    Packet->use.data[1] = 0;
    Packet->use.data[2] = 0;
    Packet->use.data[3] = GetNumberOfIOChannels();
    Packet->use.head.RPC= GetRPCValue("gchc");
    Packet->use.head.DataLegnth = 4 + 4;
    FixPacket(Packet);
    return true;
}
boolean GetChanelStreamFromPacket(BowlerPacket * Packet) {
    uint8_t pin = Packet->use.data[0];
    uint8_t mode = GetChannelMode(pin);
    if (isStremChannelMode(mode)) {
        if ( getStreamHWPtr != NULL){
            // Load the data directly into the packet as the buffer
            //Data pointer is offset by one to start after the pin index
        	uint8_t size =0;
        	getStreamHWPtr(	pin,
							&size,
							&Packet->use.data[2]);
        	Packet->use.data[1] = size;
        }
    } else {
        ERR(Packet, 2, 3);
    }
    return true;
}


boolean SetChanelStreamFromPacket(BowlerPacket * Packet) {
    uint8_t pin = Packet->use.data[0];
    uint8_t mode = GetChannelMode(pin);
    if (isStremChannelMode(mode)) {
        if (setStreamHWPtr != NULL)
            // Load the data directly into the packet as the buffer
            //Data pointer is offset by one to start after the pin index
            setStreamHWPtr(	pin,
							Packet->use.data[1],
							&Packet->use.data[2]);

    } else {
        ERR(Packet, 2, 3);
    }
    READY(Packet, 2, 3);
    return true;
}

boolean SetChanelValueFromPacket(BowlerPacket * Packet) {
    uint8_t pin = Packet->use.data[0];
    uint8_t mode = GetChannelMode(pin);
    if (isStremChannelMode(mode)) {
        ERR(Packet, 1, 3);
    } else {
        int32_t data = 0;
        int32_t time = 0;

        data = get32bit(Packet, 1);

        time =  get32bit(Packet, 5);
        //println_W("Setting on pin=");p_int_W(pin); print_W(" value= ");p_int_W(data); print_W(" time= ");p_fl_W(time);
		if(mode == IS_SERVO)
			data = (data&0x000000ff) | (time<<16);

        if (setChanelValueHWPtr != NULL)
            setChanelValueHWPtr(pin, 1, &data, (float)time);

    	//println_E(__FILE__);println_E("SetChanelValueFromPacket");
        setDataTableCurrentValue(pin,data);


    }
    READY(Packet, 1, 3);
    return true;
}

boolean SetAllChannelValueFromPacket(BowlerPacket * Packet) {
    int32_t * data = (int32_t *) (&Packet->use.data[5] );
    int32_t tmp;

    if (setAllChanelValueHWPtr != NULL) {
    	uint32_t time;
        uint8_t i;

        time=get32bit(Packet, 0);

        for (i = 0; i < GetNumberOfIOChannels(); i++) {
        	if(isOutputMode(GetChannelMode(i))==true){
        		tmp = get32bit(Packet, (i*4) +5);
//        		if(GetChannelMode(i) == IS_SERVO)
//					data[i] = (tmp & 	0x000000ff) | (time<<16);
//        		else
        			data[i] = tmp;
			}else{
				data[i] = getBcsIoDataTable(i)->PIN.currentValue;
			}

        }

        setAllChanelValueHWPtr(data, time);

        for (i = 0; i < GetNumberOfIOChannels(); i++) {
        	if(isOutputMode(GetChannelMode(i))==true){

        		//println_E(__FILE__);println_E("SetAllChannelValueFromPacket");
				setDataTableCurrentValue(i,data[i]);
        	}
		}
        //READY(Packet, 3, 3);
        GetAllChanelValueFromPacket(Packet);
    } else {
        return false;
    }
    return true;
}

int32_t GetChanelSingleValue(uint8_t pin){
	int32_t val;
	uint8_t size=1;
	GetChanelValueHW(pin, &size, &val);
	return val;
}


boolean GetChanelValueFromPacket(BowlerPacket * Packet) {
    uint8_t pin = Packet->use.data[0];
    uint8_t mode = GetChannelMode(pin);
    uint8_t numValues = 1;
    int32_t data;


	if (getChanelValueHWPtr != NULL) {
		getChanelValueHWPtr(pin,
				&numValues,
				&data);
	} else {
		return false;
	}
	if(isOutputMode(GetChannelMode(pin))==false ){
		setDataTableCurrentValue(pin,data);
	}else{
		if(mode== IS_UART_RX){
			setDataTableCurrentValue(pin,data);
		}else{
			data = getBcsIoDataTable(pin)->PIN.currentValue;
		}
	}

	set32bit(Packet, data, 1);
	numValues = 4;

    Packet->use.head.DataLegnth = 4 + 1 + numValues;
    FixPacket(Packet);
    return true;
}

boolean GetAllChanelValueFromPacket(BowlerPacket * Packet) {
    int32_t * data = (int32_t *) (&Packet->use.data[1]);
    if (getAllChanelValueHWPtr != NULL) {
        int i;
        int32_t tmp;
        getAllChanelValueHWPtr(data);
        for (i = 0; i < GetNumberOfIOChannels(); i++) {
            tmp = data[i];
            if(isOutputMode(GetChannelMode(i))==false){
            	setDataTableCurrentValue(i,tmp);
            }else{
                 if(GetChannelMode(i) == IS_SERVO){
                    tmp = GetServoPos(i);
                }else if(GetChannelMode(i)== IS_UART_RX){
                	setDataTableCurrentValue(i,tmp);
    			}else{
                    tmp = getBcsIoDataTable(i)->PIN.currentValue;
    			}
            }

            set32bit(Packet, tmp, (i*4)+1);

        }
        Packet->use.data[0]=(GetNumberOfIOChannels());
        Packet->use.head.RPC=GetRPCValue("gacv");
        Packet->use.head.DataLegnth = 4+1+(GetNumberOfIOChannels()*4);
    } else
        return false;
    FixPacket(Packet);
    return true;
}

boolean ConfigureChannelFromPacket(BowlerPacket * Packet) {
    uint8_t pin = Packet->use.data[0];
    boolean setValues = Packet->use.data[1];
    uint8_t mode = GetChannelMode(pin);

    int32_t tmp;
    if(mode != 0xff && setValues){
		if (configChannelHWPtr != NULL) {

//			println_E("Pushing configs from packet ");
//			p_int_E(pin);

			tmp = get32bit(Packet,  3);

//			print_E(" value = ");
//			p_int_E(tmp);

			//println_E(__FILE__);println_E("ConfigureChannelFromPacket");
			setDataTableCurrentValue(pin,tmp);

			configChannelHWPtr(pin, 1, &tmp);
		} else {
			return false;
		}

    }
    //println_E("Loading configs into packet");
    Packet->use.head.RPC= GetRPCValue("cchn");
    Packet->use.head.Method = BOWLER_CRIT;
    Packet->use.head.DataLegnth = 4+1+(GetNumberOfIOChannels()*4);
    int32_t * data = (int32_t *) (Packet->use.data + 1);
    configChannelHWPtr(0xff, GetNumberOfIOChannels(), data);
    Packet->use.data[0] =GetNumberOfIOChannels();
    int i;
    for (i = 0; i < GetNumberOfIOChannels(); i++) {
		tmp = data[i];
		set32bit(Packet, tmp, (i*4)+1);
	}
    FixPacket(Packet);
    return true;
}

boolean isOutputMode(uint8_t mode){
    switch (mode) {

        case IS_DO:
        case IS_ANALOG_OUT:
        case IS_PWM:
        case IS_SERVO:
        case IS_COUNTER_OUTPUT_INT:
        case IS_COUNTER_OUTPUT_DIR:
        case IS_DC_MOTOR_VEL:
        case IS_DC_MOTOR_DIR:
        	return true;
        default:
            return false;
    }
}

boolean pinHasFunction(uint8_t pin, uint8_t function) {
    switch (function) {
        case IS_DI:
            return true;
        case IS_DO:
            return true;
        case IS_ANALOG_IN:
            return getBcsIoDataTable(pin)->FUNCTION.HAS_ANALOG_IN;
        case IS_ANALOG_OUT:
            return false;
            //return getBcsIoDataTable(pin)->FUNCTION.HAS_ANALOG_OUT;
        case IS_PWM:
            return getBcsIoDataTable(pin)->FUNCTION.HAS_PWM;
        case IS_SERVO:
            return true;
        case IS_UART_TX:
            return getBcsIoDataTable(pin)->FUNCTION.HAS_UART_T;
        case IS_UART_RX:
            return getBcsIoDataTable(pin)->FUNCTION.HAS_UART_R;
        case IS_SPI_MOSI:
            return getBcsIoDataTable(pin)->FUNCTION.HAS_SPI_O;
        case IS_SPI_MISO:
            return getBcsIoDataTable(pin)->FUNCTION.HAS_SPI_I;
        case IS_SPI_SCK:
            return getBcsIoDataTable(pin)->FUNCTION.HAS_SPI_C;
        case IS_COUNTER_INPUT_INT:
            return getBcsIoDataTable(pin)->FUNCTION.HAS_COUNTER_INPUT_I;
        case IS_COUNTER_INPUT_DIR:
            return getBcsIoDataTable(pin)->FUNCTION.HAS_COUNTER_INPUT_D;
        case IS_COUNTER_INPUT_HOME:
            return getBcsIoDataTable(pin)->FUNCTION.HAS_COUNTER_INPUT_H;
        case IS_COUNTER_OUTPUT_INT:
            return getBcsIoDataTable(pin)->FUNCTION.HAS_COUNTER_OUTPUT_I;
        case IS_COUNTER_OUTPUT_DIR:
            return getBcsIoDataTable(pin)->FUNCTION.HAS_COUNTER_OUTPUT_D;
        case IS_COUNTER_OUTPUT_HOME:
            return getBcsIoDataTable(pin)->FUNCTION.HAS_COUNTER_OUTPUT_H;
        case IS_DC_MOTOR_VEL:
            return getBcsIoDataTable(pin)->FUNCTION.HAS_PWM;
        case IS_DC_MOTOR_DIR:
            return getBcsIoDataTable(pin)->FUNCTION.HAS_DC_MOTOR;
        case IS_PPM_IN:
            return getBcsIoDataTable(pin)->FUNCTION.HAS_PPM;
        default:
            return false;
    }
}


boolean getFunctionList(BowlerPacket * Packet) {
    int chan = Packet->use.data[0];

    int index = 1;
    int i = 0;
    for (i = 0; i < IO_MODE_MAX; i++) {
        if (pinHasFunction(chan, i)) {
            Packet->use.data[index++] = i;
        }
    }
    Packet->use.data[0] = index - 1;
    Packet->use.head.DataLegnth = 4 + index;
    FixPacket(Packet);
    return true;
}

void printValues() {
//    int i;
//    println_I("Values");
//    for (i = 0; i < GetNumberOfIOChannels(); i++) {
//        println_I("\t# ");
//        p_int_I(i);
//        print_I("\tCurrent ");
//        p_int_I(getBcsIoDataTable(i)->PIN.currentValue);
//        //print_I("\tPrevious ");p_int_I(getBcsIoDataTable(i)->PIN.previousValue);
//    }
}

void printModes() {
//    int i;
//    println_I("Modes");
//    for (i = 0; i < GetNumberOfIOChannels(); i++) {
//        println_I("\t# ");
//        p_int_I(i);
//        print_I("\tCurrent ");
//        printMode(getBcsIoDataTable(i)->PIN.currentChannelMode, INFO_PRINT);
//        //print_I("\tPrevious ");printMode(getBcsIoDataTable(i)->PIN.previousChannelMode,INFO_PRINT);
//    }
}

void printConfigurations() {
    int i;
//    println_I("Configurations");
    for (i = 0; i < GetNumberOfIOChannels(); i++) {
        println_I("\t# ");
        p_int_I(i);
//        print_I("\tCurrent ");p_int_I(getBcsIoDataTable(i)->PIN.currentConfiguration);
//        print_I("\tPrevious ");p_int_I(getBcsIoDataTable(i)->PIN.previousConfiguration);
    }
}

void printAsync() {
//    int i;
//    println_I("Async Data ");
//    p_fl_I(getMs());
//    for (i = 0; i < GetNumberOfIOChannels(); i++) {
//        println_I("\t# ");
//        p_int_I(i);
//        print_I("\tCurrent ");
//        //FIXME
//        p_int_I(getBcsIoDataTable(i)->PIN.currentValue);
//        print_I("\tPrevious ");
//        p_int_I(getBcsIoDataTable(i)->PIN.asyncDataPreviousVal);
//        print_I("\tMode ");
//        printAsyncType(getBcsIoDataTable(i)->PIN.asyncDataType);
//        print_I("\tIteration ");
//        p_fl_I(getBcsIoDataTable(i)->asyncDataTimer.setPoint);
//        print_I("\tLast ");
//        p_fl_I(getBcsIoDataTable(i)->asyncDataTimer.MsTime);
//    }
}


/**
 * Sets the datable value and returns true if the value is new, false if it is the same as it was
 */
boolean _setDataTableCurrentValue(uint8_t pin, int32_t value){
	if(pin>=GetNumberOfIOChannels()){
		//println_E("Pin out of index! : "); p_int_E(pin);
	}
	if(value !=getBcsIoDataTable(pin)->PIN.currentValue ){
		Print_Level l = isOutputMode(GetChannelMode(pin))?ERROR_PRINT:WARN_PRINT;
		println(" Value was ",l);p_int(getBcsIoDataTable(pin)->PIN.currentValue,l);
		print_nnl(" set to ",l);p_int(value,l);
		print_nnl(" on pin ",l);p_int(pin,l);
		print_nnl(" mode ",l);printMode(GetChannelMode(pin),l);
		// THis is the only place this variable should be set
		getBcsIoDataTable(pin)->PIN.currentValue =value;
		//print_I(" confirmed ");p_int_I(getBcsIoDataTable(pin)->PIN.currentValue);
		return true;
	}
	return false;
}




