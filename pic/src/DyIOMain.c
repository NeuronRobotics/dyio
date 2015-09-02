
#include "UserApp.h"

void buttonCheck(uint8_t code) {
    if (_RB0 == 1) {
        p_int_E(code);
        print_E(" Reset");
        SetColor(1, 1, 1);
        U1CON = 0x0000;
        DelayMs(100);
        Reset();
    }

}
BowlerPacket ISRPacket;
BowlerPacket Packet;
boolean pushing = false;
#define SIZE_OF_PACKET_BUFFER 10
PACKET_FIFO_STORAGE packetFifo;
BowlerPacket buffer[SIZE_OF_PACKET_BUFFER];

boolean PutBowlerPacketLocal(BowlerPacket * Packet) {
    DisableIntT4;
    FifoAddPacket(&packetFifo, Packet);
    EnableIntT4;
    return true;
}
void startCoreUpstreamServerTimer(boolean on){
    if(on){
            OpenTimer4(T4_ON | T4_SOURCE_INT | T4_PS_1_256, 2000);
            ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_1);
    }else
       CloseTimer4();
}

void server(){
    //button check in the timer, acts as a psudo-watchdog
    buttonCheck(1);

    if (FifoGetPacketCount(&packetFifo) > 0) {
        FifoGetPacket(&packetFifo, &ISRPacket);
        SetRed(1);
        //println_E("Asyn");
        PutBowlerPacket(& ISRPacket);
        SetRed(0);
        return;
    }
    // Run the Bowler Stack Namespace iteration of all async packets
    // Pass in  the function pointer to push the packets upstream
    boolean back = GetBowlerPacket_arch(&ISRPacket);
    if (back) {
        if (process(&ISRPacket)) {
            SetGreen(1);
            //Packet found, sending
            PutBowlerPacket(&ISRPacket);
            SetGreen(0);
        }

    }//Have a packet

}

void __ISR(_TIMER_4_VECTOR, ipl1) _Timer4Handler(void) {
    //shut off the timer to avoid process recoursion
    mT4ClearIntFlag();
    startCoreUpstreamServerTimer(false);
    USBEnableInterrupts();
    EndCritical();

    server();

    startCoreUpstreamServerTimer(true);
}

void runDyIOMain(void) {
    InitPacketFifo(&packetFifo, buffer, SIZE_OF_PACKET_BUFFER);
    startScheduler();
    Bowler_HAL_Init();
    Bowler_Init(); // Com Stack Init. Sets up timeout timer, uart 0 and if debug enabled, uart 1

    UserInit(); // User code init
    //println_I("Main Loop Start");
    
    //kick off packet processor timer
    startCoreUpstreamServerTimer(true);
    //setPrintLevelNoPrint();
    if(getPrintLevel()!=NO_PRINT){
         //disableSerialComs(true);
         println_E("Serial Port Disabled!");
    }else{
         disableSerialComs(false);
    }
    //SetGreen(0);
    while (1) {
        //server();
        RunNamespaceAsync(&Packet, &PutBowlerPacketLocal);
        buttonCheck(0);
    }
}




