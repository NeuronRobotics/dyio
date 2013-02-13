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

static BYTE private[DMA_SIZE*2];

static BOOL running=FALSE;

void closeDma(){
	FLAG_ASYNC=FLAG_BLOCK;
	DmaChnAbortTxfer(chn);
	DmaChnClrEvFlags(chn,DMA_EV_ALL_EVNTS);
	running=FALSE;
}

void startUartDma(){
	if(running)
		return;
	FLAG_ASYNC=FLAG_BLOCK;
	running=TRUE;
	println_I("startUartDma");

	dmaReadPointer = 0;
	startUartCoProc();
	DmaChnOpen(chn, DMA_CHN_PRI2, DMA_OPEN_DEFAULT);
	// set the events: we want the UART2 rx interrupt to start our transfer
	DmaChnSetEventControl(chn, 	DMA_EV_START_IRQ_EN|
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
	FLAG_ASYNC=FLAG_OK;
	println_I("DMA now started");
}

int dump(int from , int to){
	if(from >= to)
		return 0;
	int i;
	int num=0;
	for(i=from;i<to;i++){
		addCoProcByte(private[dmaReadPointer++]);
		num++;
	}
	return num;
}

int pushContents(){
	FLAG_ASYNC=FLAG_BLOCK;
	int from = dmaReadPointer;
	int to = DmaChnGetDstPnt(chn);

	BOOL reset=FALSE;
	if(to>(DMA_SIZE/2)){
		DelayMs(1);
		to = DmaChnGetDstPnt(chn);
    	DmaChnAbortTxfer(chn);
    	if(DataRdyUART2()){
    		println_I("Dumping UART buffer: ");
    		int b=0;
			while(DataRdyUART2()){
				uartErrorCheck();
				//Dump the remaining bytes in the UART buffer after resetting the DMA
				private[to++]=UARTGetDataByte(UART2);
				buttonCheck(56);
				b++;
			}
			p_sl_I(b);print_I(" added");
    	}
      	DmaChnSetTxfer(chn, (void*)&U2RXREG, private, 1, DMA_SIZE, 1);
      	DmaChnEnable(chn);
    	reset=TRUE;
	}
	if(to>from ){
		if(to<0||to>DMA_SIZE||from<0||from>DMA_SIZE){
			println_I("Load size, WTF? from=");p_sl_I(from);print_I(" to=");p_sl_I(to);
		}
		int back = dump(from,to);
		FLAG_ASYNC=FLAG_OK;
		if(reset){
			dmaReadPointer=0;
			println_I("Dma reset");
		}
		return back;
	}else{
		if(to != from){
			dmaReadPointer = DmaChnGetDstPnt(chn);
			println_E("Load error, WTF? from=");p_sl_E(from);print_E(" to=");p_sl_E(to);
		}

	}
	FLAG_ASYNC=FLAG_OK;
	return 0;
}

int updateUartDmaRx(){
	//println_I("updateUartDmaRx");
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
    	updateUartDmaRx();
    	println_I("##Maxed out DMA buffer, resetting" );
    	//FLAG_ASYNC=FLAG_OK;
    }
}
#endif
