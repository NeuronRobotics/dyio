
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
    StartCritical();
    FifoAddPacket(&packetFifo, Packet);
    EndCritical();
    return true;
}
void startTimer(boolean on){
    if(on){
            OpenTimer4(T4_ON | T4_SOURCE_INT | T4_PS_1_256, 500);
            ConfigIntTimer4(T4_INT_ON | T4_INT_PRIOR_5);
    }else
       CloseTimer4();
}

void __ISR(_TIMER_4_VECTOR, ipl5) _Timer4Handler(void) {
    //shut off the timer to avoid process recoursion
    mT4ClearIntFlag();
    EndCritical();
    startTimer(false);

    //button check in the timer, acts as a psudo-watchdog
    if (_RB0 == 1) {
        SetColor(0, 1, 1);
        U1CON = 0x0000;
        DelayMs(100);
        Reset();
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
    if (FifoGetPacketCount(&packetFifo) > 0) {
        FifoGetPacket(&packetFifo, &ISRPacket);
        SetRed(1);
        PutBowlerPacket(& ISRPacket);
        SetRed(0);
    }
    startTimer(true);
}

void runDyIOMain(void) {
    startScheduler();
    Bowler_HAL_Init();
    Bowler_Init(); // Com Stack Init. Sets up timeout timer, uart 0 and if debug enabled, uart 1

    UserInit(); // User code init
    //println_I("Main Loop Start");
    InitPacketFifo(&packetFifo, buffer, SIZE_OF_PACKET_BUFFER);
    //kick off packet processor timer
    startTimer(true);

    while (1) {
        RunNamespaceAsync(&Packet, &PutBowlerPacketLocal);
        buttonCheck(0);
    }
}




