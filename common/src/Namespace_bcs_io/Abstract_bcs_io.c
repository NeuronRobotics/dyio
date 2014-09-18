/*
 * Abstract_bcs_io.c
 *
 *  Created on: Mar 21, 2013
 *      Author: hephaestus
 */

#include "Bowler/Bowler.h"
#include "Namespace/Namespace_bcs_io.h"


static int NumberOfIOChannels = 0;
static DATA_STRUCT * dataPtr = NULL;

boolean(*setChanelValueHWPtr)(uint8_t  , uint8_t, int32_t *, float);
boolean(*getChanelValueHWPtr)(uint8_t  , uint8_t*, int32_t *);
boolean(*setAllChanelValueHWPtr)(int32_t *, float);
boolean(*getAllChanelValueHWPtr)(int32_t *);
boolean(*configChannelHWPtr)(uint8_t  , uint8_t, int32_t *);

void InitilizeBcsIo(int numPins,
					DATA_STRUCT * dataPtrLocal,
					boolean (*setChanelValueHWPtrLocal)(uint8_t,uint8_t,int32_t *,float),
					boolean (*getChanelValueHWPtrLocal)(uint8_t,uint8_t*,int32_t *),
					boolean (*setAllChanelValueHWPtrLocal)(int32_t *,float),
					boolean (*getAllChanelValueHWPtrLocal)(int32_t *),
					boolean (*configChannelHWPtrLocal)(uint8_t,uint8_t,int32_t *)
) {
    if (numPins < 1
            ) {
        setPrintLevelErrorPrint();
        println_E("Failed IO sanity check: failed initialization channels #");
        p_int_E(numPins);
        //println_E("Failed IO sanity check: failed initialization channels #");p_int_E(numPins);
        //FAIL sanity check
        while (1);
    }
    if (
            dataPtrLocal == NULL
            ) {
        setPrintLevelErrorPrint();
#if !defined(__AVR_ATmega644P__) && !defined(__AVR_ATmega644PA__) && !defined(__AVR_ATmega324P__)
        println_E("Failed IO sanity check: failed initialization dataPtrLocal");
#endif
        //println_E("Failed IO sanity check: failed initialization dataPtrLocal");
        //FAIL sanity check
        while (1);
    }
    if (
            setChanelValueHWPtrLocal == NULL
            ) {
        setPrintLevelErrorPrint();
#if !defined(__AVR_ATmega644P__) && !defined(__AVR_ATmega644PA__) && !defined(__AVR_ATmega324P__)
        println_E("Failed IO sanity check: failed initialization setChanelValueHWPtrLocal");
#endif
        //println_E("Failed IO sanity check: failed initialization setChanelValueHWPtrLocal");
        //FAIL sanity check
        while (1);
    }
    if (
            getChanelValueHWPtrLocal == NULL
            ) {
        setPrintLevelErrorPrint();
#if !defined(__AVR_ATmega644P__) && !defined(__AVR_ATmega644PA__) && !defined(__AVR_ATmega324P__)
        println_E("Failed IO sanity check: failed initialization getChanelValueHWPtrLocal");
#endif
        //println_E("Failed IO sanity check: failed initialization getChanelValueHWPtrLocal");
        //FAIL sanity check
        while (1);
    }
    if (
            setAllChanelValueHWPtrLocal == NULL
            ) {
        setPrintLevelErrorPrint();
#if !defined(__AVR_ATmega644P__) && !defined(__AVR_ATmega644PA__) && !defined(__AVR_ATmega324P__)
        println_E("Failed IO sanity check: failed initialization setAllChanelValueHWPtrLocal");
#endif
        //println_E("Failed IO sanity check: failed initialization setAllChanelValueHWPtrLocal");
        //FAIL sanity check
        while (1);
    }
    if (
            getAllChanelValueHWPtrLocal == NULL
            ) {
        setPrintLevelErrorPrint();
#if !defined(__AVR_ATmega644P__) && !defined(__AVR_ATmega644PA__) && !defined(__AVR_ATmega324P__)
        println_E("Failed IO sanity check: failed initialization getAllChanelValueHWPtrLocal");
#endif
        //println_E("Failed IO sanity check: failed initialization getAllChanelValueHWPtrLocal");
        //FAIL sanity check
        while (1);
    }
    if (
            configChannelHWPtrLocal == NULL
            ) {
        setPrintLevelErrorPrint();
#if !defined(__AVR_ATmega644P__) && !defined(__AVR_ATmega644PA__) && !defined(__AVR_ATmega324P__)
        println_E("Failed IO sanity check: failed initialization configChannelHWPtrLocal");
#endif
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
}

int GetNumberOfIOChannels() {
    return NumberOfIOChannels;
}

uint8_t GetChannelMode(uint8_t pin) {
    if (pin < 0 || pin > GetNumberOfIOChannels()) {
        setPrintLevelErrorPrint();
#if !defined(__AVR_ATmega644P__) && !defined(__AVR_ATmega644PA__) && !defined(__AVR_ATmega324P__)
        println_E("Failed IO sanity check: channel number out of bounds # ");
        p_int_E(pin);
#endif
        //FAIL sanity check
        while (1);
    }
    //Strip off the internally stored High Bit
    return getBcsIoDataTable(pin)->PIN.currentChannelMode;
}

RunEveryData * getPinsScheduler(int pin) {
    return & dataPtr[pin].asyncDataTimer;
}

DATA_STRUCT * getBcsIoDataTable(int pin) {
    if (dataPtr == NULL) {
        setPrintLevelErrorPrint();
#if !defined(__AVR_ATmega644P__) && !defined(__AVR_ATmega644PA__) && !defined(__AVR_ATmega324P__)
        println_E("Failed IO sanity check: no data table");
#endif
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
    return true;
}

boolean GetAllChannelModeFromPacket(BowlerPacket * Packet) {
    int i;
    Packet->use.head.Method = BOWLER_POST;
    Packet->use.data[0] = GetNumberOfIOChannels();
    for (i = 0; i < GetNumberOfIOChannels(); i++) {
        Packet->use.data[1 + i] = GetChannelMode(i);
    }
    Packet->use.head.DataLegnth = 4 + GetNumberOfIOChannels();
    FixPacket(Packet);
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
    ;
    Packet->use.head.DataLegnth = 4 + 4;
    FixPacket(Packet);
    return true;
}

boolean SetChanelStreamFromPacket(BowlerPacket * Packet) {
    uint8_t pin = Packet->use.data[0];
    uint8_t mode = GetChannelMode(pin);
    if (isStremChannelMode(mode)) {
        if (setChanelValueHWPtr != NULL)
            // Load the data directly into the packet as the buffer
            //Data pointer is offset by one to start after the pin index
            setChanelValueHWPtr(pin,
                Packet->use.head.DataLegnth - (4 + 1),
                (int32_t *) (Packet->use.data + 1),
                (float) 0);
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
        float time = 0;

        data = get32bit(Packet, 1);

        time = (float) get32bit(Packet, 5);

        getBcsIoDataTable(pin)->PIN.currentValue = data;
        //println_W("Setting on pin=");p_int_W(pin); print_W(" value= ");p_int_W(data); print_W(" time= ");p_fl_W(time);
        if (setChanelValueHWPtr != NULL)
            setChanelValueHWPtr(pin, 1, &data, time);

    }
    READY(Packet, 1, 3);
    return true;
}

boolean SetAllChannelValueFromPacket(BowlerPacket * Packet) {
    int32_t * data = (int32_t *) (Packet->use.data + 4);
    uint32_t tmp;
    if (setAllChanelValueHWPtr != NULL) {
        UINT32_UNION time;
        uint8_t i;

        time.byte.FB = Packet->use.data[0];
        time.byte.TB = Packet->use.data[1];
        time.byte.SB = Packet->use.data[2];
        time.byte.LB = Packet->use.data[3];
        for (i = 0; i < GetNumberOfIOChannels(); i++) {
            tmp = get32bit(Packet, i * 4);
            getBcsIoDataTable(i)->PIN.currentValue = tmp;
            data[i] = tmp;
        }
        setAllChanelValueHWPtr(data, time.Val);
        READY(Packet, 3, 3);
        FixPacket(Packet);
    } else {
        return false;
    }
    return true;
}

boolean GetChanelValueFromPacket(BowlerPacket * Packet) {
    uint8_t pin = Packet->use.data[0];
    uint8_t mode = GetChannelMode(pin);
    uint8_t numValues = 1;
    if (isStremChannelMode(mode)) {

        if (getChanelValueHWPtr != NULL) {
            // Load the data directly into the packet as the buffer
            //Data pointer is offset by one to start after the pin index
            getChanelValueHWPtr(pin,
                    &numValues,
                    (int32_t *) (Packet->use.data + 1));
        } else {
            return false;
        }
    } else {
        int32_t data;
        if (getChanelValueHWPtr != NULL) {
            getChanelValueHWPtr(pin,
                    &numValues,
                    &data);
        } else {
            return false;
        }
//        if (GetChannelMode(pin) == IS_ANALOG_IN) {
//            println_W("Analog value= ");
//            p_int_W(data);
//        }
        set32bit(Packet, data, 1);
        numValues = 4;


    }
    Packet->use.head.DataLegnth = 4 + 1 + numValues;
    FixPacket(Packet);
    return true;
}

boolean GetAllChanelValueFromPacket(BowlerPacket * Packet) {
    int32_t * data = (int32_t *) (Packet->use.data);
    if (getAllChanelValueHWPtr != NULL) {
        int i;
        int32_t tmp;
        getAllChanelValueHWPtr((int32_t *) Packet->use.data);
        for (i = 0; i < GetNumberOfIOChannels(); i++) {
            tmp = data[i];
            getBcsIoDataTable(i)->PIN.currentValue = tmp;
            set32bit(Packet, tmp, i * 4);
        }
        Packet->use.head.DataLegnth = 4 + GetNumberOfIOChannels()*4;
    } else
        return false;
    FixPacket(Packet);
    return true;
}

boolean ConfigureChannelFromPacket(BowlerPacket * Packet) {
    uint8_t pin = Packet->use.data[0];
    uint8_t mode = GetChannelMode(pin);
    int32_t * data = (int32_t *) (Packet->use.data + 1);
    int32_t tmp;
    int i;
    if (configChannelHWPtr != NULL) {
        if (Packet->use.head.DataLegnth > 5 && mode != IS_SERVO) {
            int numVals = (Packet->use.head.DataLegnth - (4 + 1)) / 4;
            for (i = 0; i < numVals; i++) {
                tmp = get32bit(Packet, (i * 4) + 1);
                getBcsIoDataTable(i)->PIN.currentValue = tmp;
                data[i] = tmp;
            }
            configChannelHWPtr(pin, numVals, (int32_t *) (Packet->use.data + 1));
        } else {
            // Single Byte Servo, legacy HACK
            int32_t value = Packet->use.data[1];
            configChannelHWPtr(pin, 1, &value);
        }
    } else {
        return false;
    }
    FixPacket(Packet);
    return true;
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
    int i;
    println_I("Values");
    for (i = 0; i < GetNumberOfIOChannels(); i++) {
        println_I("\t# ");
        p_int_I(i);
        print_I("\tCurrent ");
        p_int_I(getBcsIoDataTable(i)->PIN.currentValue);
        //print_I("\tPrevious ");p_int_I(getBcsIoDataTable(i)->PIN.previousValue);
    }
}

void printModes() {
    int i;
    println_I("Modes");
    for (i = 0; i < GetNumberOfIOChannels(); i++) {
        println_I("\t# ");
        p_int_I(i);
        print_I("\tCurrent ");
        printMode(getBcsIoDataTable(i)->PIN.currentChannelMode, INFO_PRINT);
        //print_I("\tPrevious ");printMode(getBcsIoDataTable(i)->PIN.previousChannelMode,INFO_PRINT);
    }
}

void printConfigurations() {
    int i;
    println_I("Configurations");
    for (i = 0; i < GetNumberOfIOChannels(); i++) {
        println_I("\t# ");
        p_int_I(i);
        //print_I("\tCurrent ");p_int_I(getBcsIoDataTable(i)->PIN.currentConfiguration);
        //print_I("\tPrevious ");p_int_I(getBcsIoDataTable(i)->PIN.previousConfiguration);
    }
}

void printAsync() {
    int i;
    println_I("Async Data ");
    p_fl_I(getMs());
    for (i = 0; i < GetNumberOfIOChannels(); i++) {
        println_I("\t# ");
        p_int_I(i);
        print_I("\tCurrent ");
        p_int_I(getBcsIoDataTable(i)->PIN.asyncDataCurrentVal);
        print_I("\tPrevious ");
        p_int_I(getBcsIoDataTable(i)->PIN.asyncDataPreviousVal);
        print_I("\tMode ");
        printAsyncType(getBcsIoDataTable(i)->PIN.asyncDataType);
        print_I("\tIteration ");
        p_fl_I(getBcsIoDataTable(i)->asyncDataTimer.setPoint);
        print_I("\tLast ");
        p_fl_I(getBcsIoDataTable(i)->asyncDataTimer.MsTime);
    }
}




