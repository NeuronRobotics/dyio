/*
 * UartDMARx.c
 *
 *  Created on: Nov 21, 2011
 *      Author: hephaestus
 */

#include "UserApp.h"

#if defined(USE_DMA)


static DmaChannel	chn = DMA_CHANNEL1;	// DMA channel to use for our example

static int dmaReadPointer = 0;

static BYTE private[DMA_SIZE+2];

static BOOL running=FALSE;
static BOOL abortDump=FALSE;

void closeDma(){
	stopUartCoProc();
	DmaChnAbortTxfer(chn);
	DmaChnClrEvFlags(chn,DMA_EV_ALL_EVNTS);
	running=FALSE;
}

void startUartDma(){
	if(running)
		return;
	running=TRUE;
	dmaReadPointer = 0;
	startUartCoProc();
	DmaChnOpen(chn, DMA_CHN_PRI2, DMA_OPEN_DEFAULT);
	// set the events: we want the UART2 rx interrupt to start our transfer
	// also we want to enable the pattern match: transfer stops upon detection of CR
	DmaChnSetEventControl(chn, 	DMA_EV_START_IRQ_EN|
								//DMA_EV_MATCH_EN|
								DMA_EV_START_IRQ(_UART2_RX_IRQ));

	// set the transfer source and dest addresses, source and dest sizes and the cell size
	DmaChnSetTxfer(chn, (void*)&U2RXREG, private, 1, DMA_SIZE, 1);

	DmaChnSetEvEnableFlags(chn, DMA_EV_BLOCK_DONE);		// enable the transfer done interrupt

	// enable system wide multi vectored interrupts
	INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
	INTEnableInterrupts();

	INTSetVectorPriority(INT_VECTOR_DMA(chn), INT_PRIORITY_LEVEL_5);		// set INT controller priority
	INTSetVectorSubPriority(INT_VECTOR_DMA(chn), INT_SUB_PRIORITY_LEVEL_3);		// set INT controller sub-priority

	INTEnable(INT_SOURCE_DMA(chn), INT_ENABLED);		// enable the chn interrupt in the INT controller

	// enable the chn
	DmaChnEnable(chn);
	EndCritical();
	//FLAG_ASYNC=FLAG_OK;
}

int dump(int from , int to){
	if(from >= to)
		return 0;
	int i;
	int num=0;
	for(i=from;i<to;i++){
		if(abortDump==TRUE){
			//println("Aborting dump" );
			return num;
		}
		addCoProcByte(private[dmaReadPointer++]);
		num++;
	}
	return num;
}

int pushContents(){
	//FLAG_ASYNC=FLAG_BLOCK;
	abortDump=FALSE;
	int from = dmaReadPointer;
	int to = DmaChnGetDstPnt(chn);

	BOOL reset=FALSE;
	if(to>(DMA_SIZE-120)){
		to = DmaChnGetDstPnt(chn);
    	DmaChnAbortTxfer(chn);
    	DmaChnSetTxfer(chn, (void*)&U2RXREG, private, 1, DMA_SIZE, 1);
    	DmaChnEnable(chn);
		while(DataRdyUART2()){
			//Dump the remaining bytes in the UART buffer after resetting the DMA
			private[to++]=UARTGetDataByte(UART2);
			buttonCheck(56);
		}

    	reset=TRUE;
	}
	if(to>from ){
		int back = dump(from,to);
		if(reset)
			dmaReadPointer=0;
		//FLAG_ASYNC=FLAG_OK;
		return back;
	}
	//FLAG_ASYNC=FLAG_OK;
	return 0;
}

int updateUartDmaRx(){
	startUartDma();
	uartErrorCheck();
	int numAdded=0;
	numAdded = pushContents();
	return numAdded;
}

// handler for the DMA channel 1 interrupt
void __ISR(_DMA1_VECTOR, IPL5SOFT) DmaHandler1(void)
{
	int	evFlags;				// event flags when getting the interrupt

	INTClearFlag(INT_SOURCE_DMA(chn));	// release the interrupt in the INT controller, we're servicing int

	evFlags=DmaChnGetEvFlags(chn);	// get the event flags

    if(evFlags&DMA_EV_BLOCK_DONE)
    { // just a sanity check. we enabled just the DMA_EV_BLOCK_DONE transfer done interrupt
		//FLAG_ASYNC=FLAG_BLOCK;

		pushContents();
    	println("##Maxed out DMA buffer, resetting" );

    	//FLAG_ASYNC=FLAG_OK;

    }
}
#endif
