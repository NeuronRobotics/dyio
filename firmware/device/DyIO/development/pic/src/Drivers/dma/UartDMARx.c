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

static int lastIndex=0;
static int sameCheck =0;

static BYTE private[DMA_SIZE];

static BOOL running=FALSE;

void closeDma(){
	//println("Closing DMA");
	lastIndex=0;
	sameCheck=0;
	dmaReadPointer = 0;

	DmaChnAbortTxfer(chn);
	INTEnable(INT_SOURCE_DMA(chn), INT_DISABLED);
	DmaChnClrEvFlags(chn,DMA_EV_ALL_EVNTS);
	DmaChnDisable(chn);
	running=FALSE;
}

void startUartDma(){
	if(running)
		return;
	//closeDma();
	//println("Starting DMA");
	running=TRUE;
	lastIndex=0;
	sameCheck=0;
	dmaReadPointer = 0;
	initCoProcUART();
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
}

int dump(int from , int to){
	int i;
	int num=0;
	for(i=from;i<to;i++){
		addCoProcByte(private[i]);
		num++;
	}
	return num;
}

int pushContents(){
	int back = dump(dmaReadPointer,DmaChnGetDstPnt(chn));
	dmaReadPointer+=back;
	return back;
}

int updateUartDmaRx(){
	startUartDma();
	int numAdded=0;
//	int got = 	DmaChnGetDstPnt(chn);
//	if((got == lastIndex) || got==DMA_SIZE){
//		if(got>0){
//			sameCheck++;
//			if(sameCheck>2|| got==DMA_SIZE){
//				//println("DMA got:");p_ul(got);//print(" Data [");
//				//StartCritical();
//				numAdded = pushContents();
//				sameCheck=0;
//			}else{
//				//DelayMs(1);
//			}
//		}
//	}else{
//		//DelayMs(1);
//		lastIndex = got;
//	}
//	//EndCritical();
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
    	//println("Maxed out DMA buffer, resetting");

    	int from = dmaReadPointer;
    	int to = DmaChnGetDstPnt(chn);
    	closeDma();
    	startUartDma();
    	dump(from,to);
    	print("`");
    	//println("Maxed out DMA buffer, resetting from: " );p_ul(from);print(" to: ");p_ul(to);
    }
}
#endif
