/*
 * CoProcCom.c

 *
 *  Created on: Nov 21, 2009
 *      Author: hephaestus
 */

#include "UserApp.h"
extern volatile unsigned int        U2BRG __attribute__((section("sfrs")));

#define MAX_RETRY 5
#define DELAY_TIMEOUT 50

boolean valadateRPC(int response, int sent);
uint8_t sendPacket(BowlerPacket * Packet);
boolean clearToSend(void);
void dealWithAsyncPacket(BowlerPacket * Packet);
int uartErrorCheck();
void newByte();


uint8_t privateRX[BOWLER_PacketSize];
BYTE_FIFO_STORAGE store;
boolean lastWasError = false;
boolean CoProcComInit = false;
boolean processing = false;
BowlerPacket downstream;
BowlerPacket asyncPacket;


//extern DATA_STRUCT DATA;
//extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));
//boolean addJunk = false;
//uint8_t GetCoProcSingleByte(void);
//uint32_t CalcBaud(uint32_t Baud);

boolean getPacket(BowlerPacket * packet) {
#if defined(USE_DMA)
    int numAdded = updateUartDmaRx();
    if (numAdded > 0) {
        println_I("getPacket DMA added ");
        p_int_I(numAdded);
        printFiFoState_I(&store, downstream.stream);
    }
#endif
    StartCritical();
    boolean b = _getBowlerPacket(packet, & store, true);
    EndCritical();
    if (b) {
        //println_I("Returning packet");
    }
    return b;
}

void addCoProcByte(uint8_t b) {
    //print_I("[");p_int_I(b);print_I("]");
    uint8_t err;
    FifoAddByte(&store, b, &err);
}

void PushCoProcAsync(void) {
    BowlerPacket * Packet = &asyncPacket;
    while (getPacket(Packet) == true) {
        buttonCheck(6);
        dealWithAsyncPacket(Packet);
    }
}

boolean isProcessing() {
    return processing;
}

boolean coProcRunning = false;
//void stopUartCoProc(){
//	//Disable first to clear
//	INTEnable(INT_SOURCE_UART(UART2)		, INT_DISABLED);
//	INTEnable(INT_SOURCE_UART_TX(UART2)		, INT_DISABLED);
//	INTEnable(INT_SOURCE_UART_ERROR(UART2)	, INT_DISABLED);
//	INTEnable(INT_SOURCE_UART_RX(UART2)		, INT_DISABLED);
//
//	INTClearFlag(INT_SOURCE_UART_ERROR(UART2));
//	INTClearFlag(INT_SOURCE_UART_TX(UART2));
//	INTClearFlag(INT_SOURCE_UART_RX(UART2));
//	INTClearFlag(INT_SOURCE_UART(UART2));
//	CloseUART2();
//	coProcRunning = false; 
//}

void startUartCoProc() {
    if (coProcRunning == true)
        return;

    //println_W("startUartCoProc");

    //Rx should be open collector
    mPORTFOpenDrainOpen(BIT_5);

    //Start configuration
    UARTConfigure(UART2, UART_ENABLE_PINS_TX_RX_ONLY | UART_ENABLE_HIGH_SPEED );
    UARTSetFifoMode(UART2, UART_INTERRUPT_ON_RX_NOT_EMPTY);

    //OpenUART1(UART_EN|UART_EVEN_PAR_8BIT|UART_1STOPBIT|UART_DIS_BCLK_CTS_RTS,UART_TX_ENABLE|UART_RX_ENABLE,CalcBaud(INTERNAL_BAUD ));
    UARTSetLineControl(UART2, UART_DATA_SIZE_8_BITS | UART_PARITY_EVEN | UART_STOP_BITS_1);
    //UARTSetLineControl(UART2, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE| UART_STOP_BITS_1);
    //int actual = UARTSetDataRate(UART2, GetPeripheralClock(), INTERNAL_BAUD+5);
    int calculated = (GetPeripheralClock()/(4*INTERNAL_BAUD))-1;
    //calculated +=1;// fudge factor
    U2BRG = calculated;
//    float actual = ((float)GetPeripheralClock()/(4.0*(((float)calculated)+1.0)));
//
//    float percent = ( actual / ((float) INTERNAL_BAUD))*100.0f;
//    if (actual != INTERNAL_BAUD) {
//        println_E("###Uart baud not what was set!! Actual = ");
//        p_fl_E(actual);
//        print_E(", desired = ");
//        p_int_E(INTERNAL_BAUD);
//        print_E(" ");
//        p_fl_E(percent);
//        print_E("%, U2BRG = ");
//        p_int_E(calculated);
//    }
    UARTEnable(UART2, UART_ENABLE_FLAGS(
            UART_PERIPHERAL |
            UART_RX | UART_TX));


    INTEnable(INT_SOURCE_UART_RX(UART2), INT_ENABLED);
    INTEnable(INT_SOURCE_UART_ERROR(UART2), INT_ENABLED);

    INTSetVectorPriority(INT_VECTOR_UART(UART2), INT_PRIORITY_LEVEL_7);
    INTSetVectorSubPriority(INT_VECTOR_UART(UART2), INT_SUB_PRIORITY_LEVEL_3);
    coProcRunning = true;

}

void initCoProcUART() {
	FLAG_ASYNC = FLAG_BLOCK;
    //println_W("initCoProcUART");
    coProcRunning = false;
#if defined(USE_DMA)
    closeDma();
#endif
    //Disable first to clear
    INTEnable(INT_SOURCE_UART(UART2), INT_DISABLED);
    INTEnable(INT_SOURCE_UART_TX(UART2), INT_DISABLED);
    INTEnable(INT_SOURCE_UART_ERROR(UART2), INT_DISABLED);
    INTEnable(INT_SOURCE_UART_RX(UART2), INT_DISABLED);

    INTClearFlag(INT_SOURCE_UART_ERROR(UART2));
    INTClearFlag(INT_SOURCE_UART_TX(UART2));
    INTClearFlag(INT_SOURCE_UART_RX(UART2));
    INTClearFlag(INT_SOURCE_UART(UART2));
    CloseUART2();

    uartErrorCheck();
#if defined(USE_DMA)
    startUartDma();
#else
    startUartCoProc();
#endif
    StartCritical();
    InitByteFifo(&store, privateRX, sizeof (privateRX));
    EndCritical();
    FLAG_ASYNC = FLAG_BLOCK;
}

int uartErrorCheck() {
    int err = UART2GetErrors();
    if (err) {
    	FLAG_ASYNC = FLAG_BLOCK;
        		if(err & _U2STA_FERR_MASK){
        			//println_E("\n\n\nFraming error");
        		}
        		else if(err & _U2STA_OERR_MASK){
        			//println_E("\n\n\n\nOverflow error");
        		}
        		else if(err & _U2STA_PERR_MASK){
        			//println_E("\n\n\n\nPARITY error");
        		}
        		else {
        			//println_E("\n\n\n\nUnknown UART error");
        		}
        UART2ClearAllErrors();
        initCoProcUART();
        return err;
    }
    return 0;
}

void initCoProcCom() {
    //	println_I("initCoProcCom");
    CoProcComInit = true;

    initCoProcUART();
    Init_FLAG_BUSY_ASYNC();
    FLAG_ASYNC = FLAG_OK;
}

void SendPacketToCoProc(BowlerPacket * Packet) {
    //float start = getMs();

    processing = true;
    if (CoProcComInit == false) {
        //		println_I("SendPacketToCoProc Co-proc initializing..");
        initCoProcCom();
    }

    //
    uint8_t i = 0;
    uint8_t ret = 0;
    int rpc = Packet->use.head.RPC;
    do {
        if (ret > 0) {
            println_E("Resending:");
            printPacket(Packet, ERROR_PRINT);
            FixPacket(Packet);
        }
        ret = sendPacket(Packet);
        i++;
        buttonCheck(5);
        //		if(ret!=0){
        //			initCoProcCom();
        //		}
    } while ((i != MAX_RETRY) && (ret != 0) && valadateRPC(Packet->use.head.RPC, rpc));


    if (i == MAX_RETRY) {
        println_E("#Fail:");
        printPacket(Packet, ERROR_PRINT);
        SetColor(1, 0, 0);
        initCoProcCom();
        PowerCycleAVR();
        DelayMs(200);
        ret = sendPacket(Packet);
        if (ret == 0) {
            println_W("AVR reset");
            return;
        }
        //println_E("##Failed sending to co-proc after reset also!!:");
        //p_int_E(ret);
        ERR(Packet, 0x55, ret);
        lastWasError = true;
    }

    Packet->use.head.ResponseFlag = 1;
    processing = false;
    //println_I("Coproc transaction took: ");p_fl_I(getMs()-start);print_I(" after try count: ");p_int_I(i);
}

uint8_t sendPacket(BowlerPacket * Packet) {
    //	println_I("sendPacket");
    uint8_t i;
    //int serIndex;

    for (i = 0; i < 6; i++) {
        Packet->use.head.MAC.v[i] = 0; //Set the mac address to broadcast
    }
    Packet->use.head.ProtocolRevision = BOWLER_VERSION;
    SetCRC(Packet);
    if (Packet->use.head.RPC != GetRPCValue("_pwr") &&
    	Packet->use.head.RPC != GetRPCValue("eepd") &&
        Packet->use.head.RPC != GetRPCValue("sacv")
            ) {//Ignore Power Packet
//        println("CoPro TX>>:", ERROR_PRINT);
//        printPacket(Packet, ERROR_PRINT);
    }

    int packetSize = BowlerHeaderSize + Packet->use.head.DataLegnth;

    PushCoProcAsync(); //clear out any packets before begining
    FixPacket(Packet);
    float packStartTime = getMs();
    if (SendPacketUARTCoProc(Packet->stream, packetSize)) {
        //println_I("Coproc Send took: ");p_fl_I(getMs()-packStartTime);

        packStartTime = getMs();
        RunEveryData wait = {getMs(), DELAY_TIMEOUT};
        //int dots=0;
        while (RunEvery(&wait) <= 0) {
            //			print_I("\nCurrent time=");p_fl_I(getMs()/1000);
            //			print_I("\tCurrent ticks=");p_int_I(TickGet());
            //			print_I("\tCurrent Lower ticks=");p_int_I(TickGetLower());
            //			print_I("\tCurrent Upper ticks=");p_int_I(TickGetUpper());

            if (getPacket(&downstream)) {
                //println_I("Got packet from getPacket");
                if (downstream.use.head.Method == BOWLER_ASYN) {
                    //println_I("Packet was async");
                    //println_I("<<ASYNC\n");printPacket(&downstream,INFO_PRINT);
                    dealWithAsyncPacket(&downstream);
                    //wait.MsTime += 2;
                } else {
                    //println_I("Not async");
                    if (!valadateRPC(downstream.use.head.RPC, Packet->use.head.RPC)) {
                        println_E("Valadation failed, junk TX>>");
                        printPacket(Packet, ERROR_PRINT);
                        print_E("\nRX<<\n");
                        printPacket(&downstream, ERROR_PRINT);
                        //SendPacketUARTCoProc(Packet->stream,packetSize);
                        SetColor(1, 0, 0);
                        //wait.MsTime += 2;
                    } else {

                        copyPacket(&downstream, Packet);
                        //println_I("<<RX CoProc\n");printPacket(Packet,INFO_PRINT);
                        return 0; //Got a synchronus packet
                    }
                }
            }else{
            	//newByte();
            }

            buttonCheck(4);
        }
        println_E("Rx took: ");
        p_fl_E(getMs() - packStartTime);
        printPacket(Packet, ERROR_PRINT);
        //printFiFoState_E(&store);
        PushCoProcAsync(); //clear out any packets
        initCoProcUART();
        return 2;
    } else {
        println_E("Tx took: ");
        p_fl_E(getMs() - packStartTime);
        return 1;
    }
}

boolean valadateRPC(int response, int sent) {
    switch (sent) {
        case GACV:
            switch (response) {
                case GACV:
                    return true;
                default:
                    return false;
            }
        case GACM:
            switch (response) {
                case GACM:
                    return true;
                default:
                    return false;
            }
        case GCHM:
            switch (response) {
                case GCHM:
                    return true;
                default:
                    return false;
            }
        case GCHV:
            switch (response) {
                case GCHV:
                case _ERR:
                    return true;
                default:
                    return false;
            }
        case EEPD:
            switch (response) {
                case EEPD:
                case _ERR:
                    return true;
                default:
                    return false;
            }
        case _REV:
            switch (response) {
                case _REV:
                case _ERR:
                    return true;
                default:
                    return false;
            }
        case SAVE:
            switch (response) {
                case SAVE:
                    return true;
                default:
                    return false;
            }
        case SCHM:
            switch (response) {
                case SCHM:
                case _ERR:
                    return true;
                default:
                    return false;
            }
        case SACM:
            switch (response) {
                case GACM:
                case _ERR:
                case _RDY:
                    return true;
                default:
                    return false;
            }
        case SCHV:
            switch (response) {
                case _RDY:
                case _ERR:
                case GACM:
                case SCHV:
                    return true;
                default:
                    return false;
            }
        case SACV:
            switch (response) {
                case _RDY:
                case _ERR:
                case GACV:
                    return true;
                default:
                    return false;
            }
        case _PWR:
            switch (response) {
                case _PWR:
                    return true;
                default:
                    return false;
            }
        case CCHN:
            switch (response) {
                case CCHN:
                    return true;
                default:
                    return false;
            }
        case _MAC:
            switch (response) {
                case _RDY:
                case _ERR:
                    return true;
                default:
                    return false;
            }
        default:
            println_E("Method unknown");
            return true;
    }
}

boolean SendPacketUARTCoProc(uint8_t * packet, uint16_t size) {
    FLAG_ASYNC = FLAG_BLOCK;
    uint16_t i;
    RunEveryData wait = {getMs(), 500};
    //	Print_Level l = getPrintLevel();
    //	setPrintLevelInfoPrint();
    //	println_I("SendPacketUARTCoProc ");p_int_I(size);print_I(" Bytes [");
    for (i = 0; i < size; i++) {
        do {
            //print_I("_");
            if (RunEvery(&wait) > 0) {
                //print_I("X");
                FLAG_ASYNC = FLAG_OK;
                //setPrintLevel(l);
                return false;
            }
            buttonCheck(3);
        } while (clearToSend() == false);
        if (!Write32UART2(packet[i])) {
            println_E("ERROR Write failed!!");
            initCoProcUART();
            //setPrintLevel(l);
            return false;
        }
        //Delay10us(2);
        //print_I(" 0x");prHEX8(packet[i],INFO_PRINT);
    }
    //println_I("] Sending to co proc Done ");
    FLAG_ASYNC = FLAG_OK;
    //	setPrintLevel(l);
    return true;
}

boolean clearToSend(void) {
    if (FLAG_BUSY != 0)
        return false;
    return true;
}
//#define SHORTISR

void newByte() {
#if defined(USE_DMA)
    return;
#else
#if !defined(SHORTISR)
    int timeout = 0;
    while (DataRdyUART2()) {
        addCoProcByte(UARTGetDataByte(UART2));
        mU2ClearAllIntFlags();
        //buttonCheck(17);
        timeout++;
        if (timeout > BOWLER_PacketSize) {// size of the built in FIFo
            return;
        }
    }
#else
    if (DataRdyUART2()) {
        addCoProcByte(UARTGetDataByte(UART2));
    }
#endif

#endif
}
//#if !defined(USE_DMA)

void __ISR(_UART_2_VECTOR, IPL7AUTO) My_U2_ISR(void) {
	StartCritical();
    FLAG_ASYNC = FLAG_BLOCK;
    if (INTGetFlag(INT_SOURCE_UART_RX(UART2))) {
        newByte();
        INTClearFlag(INT_SOURCE_UART_RX(UART2));
        EndCritical();
    } else if (INTGetFlag(INT_SOURCE_UART_ERROR(UART2))) {
        	println_E("&@&@&&@&@&@ generic uart error");

        INTClearFlag(INT_SOURCE_UART_ERROR(UART2));
    } else {
        if (INTGetFlag(INT_SOURCE_UART_TX(UART2))) {
            INTClearFlag(INT_SOURCE_UART_TX(UART2));
            println_E("&@&@&&@&@&@ wtf tx");
        }
        if (INTGetFlag(INT_SOURCE_UART(UART2))) {
            INTClearFlag(INT_SOURCE_UART(UART2));
            println_E("&@&@&&@&@&@ generic uart");
        }
    }
    int err = uartErrorCheck();
    if(err)
    	return;


    FLAG_ASYNC = FLAG_OK;
}
//#endif

