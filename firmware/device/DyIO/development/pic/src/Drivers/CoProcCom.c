/*
 * CoProcCom.c
 *
 *  Created on: Nov 21, 2009
 *      Author: hephaestus
 */
#include "UserApp.h"

#define MAX_RETRY 5
#define DELAY_TIMEOUT 300
BOOL valadateRPC(int response,int sent);

BYTE sendPacket(BowlerPacket * Packet);
BYTE GetCoProcSingleByte(void);

DWORD CalcBaud(DWORD Baud);
BOOL clearToSend(void);

extern DATA_STRUCT DATA;
extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));

static BYTE privateRX[BOWLER_PacketSize*10];
static BYTE_FIFO_STORAGE store;
static BOOL lastWasError = FALSE;
static BOOL init=FALSE;
static BOOL processing=FALSE;
//static BOOL addJunk = FALSE;



static BowlerPacket downstream;
static BowlerPacket asyncPacket;
void dealWithAsyncPacket(BowlerPacket * Packet);
void uartErrorCheck();


BOOL getPacket(BowlerPacket * packet){
#if defined(USE_DMA)
	int numAdded = updateUartDmaRx();
	if(numAdded>0){
		println("getPacket DMA added ");p_ul(numAdded);
		printFiFoState(&store,downstream.stream);
	}
#endif
	BOOL b = _getBowlerPacket(packet,& store,TRUE);
	if(b){
		println("Returning packet");
	}
	return b;
}

void addCoProcByte(BYTE b){
	//print("[");p_ul(b);print("]");
	BYTE err;
	FifoAddByte(&store,b,&err);
}



void PushCoProcAsync(void){
	BowlerPacket * Packet=&asyncPacket;
	while (getPacket(Packet)==TRUE){
		buttonCheck(6);
		if(Packet->use.head.MessageID!=0){
			dealWithAsyncPacket(Packet);
		}else{
			enableDebug();
			println("###########Stray sync packet..");
			printPacket(Packet);
		}
	}
}

BOOL isProcessing(){
	return processing;
}

BOOL coProcRunning = FALSE;
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
//	coProcRunning = FALSE;
//}

void startUartCoProc(){
	if(coProcRunning == TRUE)
		return;

	println("startUartCoProc");

	//Start configuration
	UARTConfigure(UART2, UART_ENABLE_PINS_TX_RX_ONLY|UART_ENABLE_HIGH_SPEED );
	UARTSetFifoMode(UART2, UART_INTERRUPT_ON_RX_NOT_EMPTY);

	//OpenUART1(UART_EN|UART_EVEN_PAR_8BIT|UART_1STOPBIT|UART_DIS_BCLK_CTS_RTS,UART_TX_ENABLE|UART_RX_ENABLE,CalcBaud(INTERNAL_BAUD ));
	//UARTSetLineControl(UART2, UART_DATA_SIZE_8_BITS | UART_PARITY_EVEN | UART_STOP_BITS_1);
	UARTSetLineControl(UART2, UART_DATA_SIZE_8_BITS | UART_PARITY_NONE| UART_STOP_BITS_1);
	int actual = UARTSetDataRate(UART2, GetPeripheralClock(), INTERNAL_BAUD );
	float percent = (((float)INTERNAL_BAUD)/((float) actual))*100.0f;
	if(actual!=INTERNAL_BAUD){
		println("###Uart baud not what was set!! Actual=");p_ul(actual);print(" desired=");p_ul(INTERNAL_BAUD);print(" %");p_fl(percent);
	}
	UARTEnable(UART2, UART_ENABLE_FLAGS(
			//UART_PERIPHERAL |
			UART_RX | UART_TX));


	INTEnable(INT_SOURCE_UART_RX(UART2)		, INT_ENABLED);
	INTEnable(INT_SOURCE_UART_ERROR(UART2)	, INT_ENABLED);

	INTSetVectorPriority(INT_VECTOR_UART(UART2), INT_PRIORITY_LEVEL_7);
	INTSetVectorSubPriority(INT_VECTOR_UART(UART2), INT_SUB_PRIORITY_LEVEL_0);
	coProcRunning = TRUE;
}

void initCoProcUART(){
	println("initCoProcUART");
	//Disable first to clear
	INTEnable(INT_SOURCE_UART(UART2)		, INT_DISABLED);
	INTEnable(INT_SOURCE_UART_TX(UART2)		, INT_DISABLED);
	INTEnable(INT_SOURCE_UART_ERROR(UART2)	, INT_DISABLED);
	INTEnable(INT_SOURCE_UART_RX(UART2)		, INT_DISABLED);

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
}

void uartErrorCheck(){
	int err = UART2GetErrors();
	if(err & _U2STA_FERR_MASK){
		println("\n\n\nFraming error");
		//UART2ClearAllErrors();
		return;
	}
	if(err & _U2STA_OERR_MASK){
		println("\n\n\n\nOverflow error");
		//UART2ClearAllErrors();
		return;
	}
	if(err & _U2STA_PERR_MASK){
		println("\n\n\n\nPARITY error");
		//UART2ClearAllErrors();
		return;
	}
	if(err ){
		println("\n\n\n\nUnknown UART error");
		//UART2ClearAllErrors();
	}
}

void initCoProcCom(){
	println("initCoProcCom");
	init = TRUE;
	StartCritical();
	InitByteFifo(&store,privateRX,sizeof(privateRX));
	EndCritical();
	initCoProcUART();
	Init_FLAG_BUSY_ASYNC();
	FLAG_ASYNC=FLAG_OK;
}


void SendPacketToCoProc(BowlerPacket * Packet){
	float start = getMs();

	processing=TRUE;
	if(init == FALSE){
		println("SendPacketToCoProc Co-proc initializing..");
		initCoProcCom();
	}

	//
	BYTE i=0;
	BYTE ret=0;
	int rpc = Packet->use.head.RPC;
	do{
		ret=sendPacket(Packet);
		i++;
		buttonCheck(5);
//		if(ret!=0){
//			initCoProcCom();
//		}
	}while ( (i!=MAX_RETRY) && (ret !=0 ) && valadateRPC(Packet->use.head.RPC,rpc));


	if (i==MAX_RETRY){
		enableDebug();
		printfDEBUG("############Five times failed, co-proc reset: ");printPacket(Packet);
		SetColor(1,0,0);
		//initCoProcCom();
		PowerCycleAVR();
		DelayMs(200);
		ret = sendPacket(Packet);
		if(ret == 0){
			printfDEBUG("##SUCCESS! OK after AVR reset");
			return;
		}
		printfDEBUG("##Failed sending to co-proc after reset also!!:");
		printfDEBUG_UL(ret);
		ERR(Packet,0x55,ret);
		lastWasError = TRUE;
		//Reset();
	}

	Packet->use.head.ResponseFlag = 1;
	processing=FALSE;
	//println("Coproc transaction took: ");p_fl(getMs()-start);print(" after try count: ");p_ul(i);
}

BYTE sendPacket(BowlerPacket * Packet){
	println("sendPacket");
	BYTE i;
	//int serIndex;

	for(i=0;i<6;i++){
		Packet->use.head.MAC.v[i]=0;//Set the mac address to broadcast
	}
	Packet->use.head.ProtocolRevision=BOWLER_VERSION;
	SetCRC(Packet);
	println(">>TX CoProc\n");printPacket(Packet);
	int packetSize = BowlerHeaderSize + Packet->use.head.DataLegnth;

	PushCoProcAsync();//clear out any packets before begining
	float packStartTime=getMs();
	if (SendPacketUARTCoProc(Packet->stream,packetSize)){
		println("Coproc Send took: ");p_fl(getMs()-packStartTime);

		packStartTime=getMs();
		RunEveryData wait={getMs(),DELAY_TIMEOUT};
		//int dots=0;
		while (RunEvery(&wait)<=0){
//			print("\nCurrent time=");p_fl(getMs()/1000);
//			print("\tCurrent ticks=");p_ul(TickGet());
//			print("\tCurrent Lower ticks=");p_ul(TickGetLower());
//			print("\tCurrent Upper ticks=");p_ul(TickGetUpper());

			if(getPacket(&downstream)){
				println("Got packet from getPacket");
				if(downstream.use.head.MessageID!=0){
					println("Packet was async");
					println("<<ASYNC\n");printPacket(&downstream);
					dealWithAsyncPacket(&downstream);
					//wait.MsTime += 2;
				}else{
					println("Not async");
					if(!valadateRPC(downstream.use.head.RPC,Packet->use.head.RPC) ){
						enableDebug();
						println("@@#@#@@Valadation failed, junk TX>>");printPacket(Packet);print("\nRX<<\n");printPacket(&downstream);
						//SendPacketUARTCoProc(Packet->stream,packetSize);
						SetColor(1,0,0);
						//wait.MsTime += 2;
					}else{

						copyPacket(&downstream,Packet);
						println("<<RX CoProc\n");printPacket(Packet);
						return 0;//Got a synchronus packet
					}
				}
			}

			buttonCheck(4);
		}
		enableDebug();
		initCoProcUART();
		printfDEBUG("############Response Timed Out, took: ");printfDEBUG_FL(getMs()-packStartTime);
		printfDEBUG_NNL(" ms to send:\n");printBowlerPacketDEBUG(Packet);
		printFiFoState(&store,downstream.stream);
		PushCoProcAsync();//clear out any packets
		return 2;
	}else{
		enableDebug();
		printfDEBUG("@@@@@@@@@@@@Transmit Timed Out, took: ");printfDEBUG_FL(getMs()-packStartTime);printfDEBUG_NNL(" ms");
		return 1;
	}
}

BOOL valadateRPC(int response,int sent){
	switch(sent){
	case GACM:
		switch(response){
		case GACM:
			return TRUE;
		default:
			return FALSE;
		}
	case GCHM:
		switch(response){
		case GCHM:
			return TRUE;
		default:
			return FALSE;
		}
	case GCHV:
		switch(response){
		case GCHV:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	case EEPD:
		switch(response){
		case EEPD:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	case _REV:
		switch(response){
		case _REV:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	case SAVE:
		switch(response){
		case SAVE:
			return TRUE;
		default:
			return FALSE;
		}
	case SCHM:
		switch(response){
		case SCHM:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	case SACM:
		switch(response){
		case SACM:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	case SCHV:
		switch(response){
		case _RDY:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	case SACV:
		switch(response){
		case _RDY:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	case _PWR:
		switch(response){
		case _PWR:
			return TRUE;
		default:
			return FALSE;
		}
	case CCHN:
		switch(response){
		case _RDY:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	case _MAC:
		switch(response){
		case _RDY:
		case _ERR:
			return TRUE;
		default:
			return FALSE;
		}
	default:
		println("Method unknown");
		return TRUE;
	}
}


BOOL SendPacketUARTCoProc(BYTE * packet,WORD size){
	FLAG_ASYNC=FLAG_BLOCK;
	WORD i;
	RunEveryData wait={getMs(),500};
	println("SendPacketUARTCoProc ");p_ul(size);print(" Bytes [");
	for (i=0;i<size;i++){
		do{
			//print("_");
			if(RunEvery(&wait) > 0){
				//print("X");
				FLAG_ASYNC=FLAG_OK;
				return FALSE;
			}
			buttonCheck(3);
		}while ( clearToSend() == FALSE);
		print(" 0x");prHEX8(packet[i]);
		Write32UART2(packet[i]);
		//Delay10us(2);
	}
	println("] Sending to co proc Done ");
	FLAG_ASYNC=FLAG_OK;
	return TRUE;
}

BOOL clearToSend(void){
	if (FLAG_BUSY!=0)
		return FALSE;
	return TRUE;
}
#define SHORTISR
void newByte(){
#if defined(USE_DMA)
	return;
#else
//	#if !defined(SHORTISR)
//		int timeout =0;
//		while(DataRdyUART2()){
//
//			addCoProcByte(UARTGetDataByte(UART2));
//
//			//buttonCheck(17);
//			timeout++;
//			if(timeout>8){// size of the built in FIFo
//				return;
//			}
//		}
//	#else
		if(DataRdyUART2()){
			addCoProcByte(UARTGetDataByte(UART2));
		}
//	#endif

#endif
}
//#if !defined(USE_DMA)
void __ISR(_UART_2_VECTOR, ipl7) My_U2_ISR(void){
	//FLAG_ASYNC=FLAG_BLOCK;
	StartCritical();
	if (INTGetFlag(INT_SOURCE_UART_RX(UART2))){
		newByte();
		INTClearFlag(INT_SOURCE_UART_RX(UART2));
	}else
	 if(INTGetFlag(INT_SOURCE_UART_ERROR(UART2))){
		//uartErrorCheck();
		INTClearFlag(INT_SOURCE_UART_ERROR(UART2));
	}else{
		if ( INTGetFlag(INT_SOURCE_UART_TX(UART2)) ) {
			INTClearFlag(INT_SOURCE_UART_TX(UART2));
			//println("&@&@&&@&@&@ wtf tx");
		}
		if(INTGetFlag(INT_SOURCE_UART(UART2))){
			INTClearFlag(INT_SOURCE_UART(UART2));
			//println("&@&@&&@&@&@ generic uart");
		}
	}
	//mU2ClearAllIntFlags();
	EndCritical();
	//FLAG_ASYNC=FLAG_OK;
}
//#endif

