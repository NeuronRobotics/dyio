
/**
 * This file is for managment of the onboard bluetooth module
 */
#include "UserApp.h"
BOOL btOk = FALSE;
BOOL btChecked = FALSE;

#define HIGH_BAUD 230400
char packet[20];
void sendString(char * data){
	int i=0;
	while(data[i++]!='\0');
	Pic32UARTPutArray(data,i);
	DelayMs(1100);
}

BOOL testAtCommand(int baud){
	Pic32UART_HAL_INIT(baud);
	//from http://www.e-gizmo.com/KIT/images/EGBT-04/EGBT-045MS-046S%20Bluetooth%20Module%20Manual%20rev%201r0.pdf
	//Testing AT command
	sendString("AT");
	if( Pic32Get_UART_Byte_Count()>1){
		Pic32UARTGetArray(packet,Pic32Get_UART_Byte_Count());
		//if(packet[0]=='O' && packet[1]=='K'){
			sendString("AT+NAMEDyIO");
			Pic32UARTGetArray(packet,Pic32Get_UART_Byte_Count());
			sendString("AT+BAUD9");
			Pic32UART_HAL_INIT(HIGH_BAUD);
			Pic32UARTGetArray(packet,Pic32Get_UART_Byte_Count());
			return TRUE;
		//}
	}
	return FALSE;
}

BYTE hasBluetooth(){
	if(!btChecked){
		/**
		 * Start by checking the low baudrate
		 */
		//BluetoothCommand=ON;//Command mode

		SetColor(1,1,0);//Set LEd to yellow

		if(testAtCommand(9600)){
			btOk = TRUE;
		}else if (testAtCommand(HIGH_BAUD)){
			btOk = TRUE;
		}else{
			SetColor(1,0,1);
			DelayMs(500);
			btOk = FALSE;
			Pic32UART_HAL_INIT(9600);
		}

		btChecked = TRUE;
		BluetoothReset=OFF; // reset
		DelayMs(100);
		BluetoothReset=ON; // Pull BT module out of reset
	}
	BluetoothCommand=OFF;//Command mode
	return btOk;
}


void initBluetooth(){
	BluetoothResetTRIS = OUTPUT; //output mode on reset line
	BluetoothCommandTRIS = OUTPUT; //output mode on CMD line
	BluetoothLinkTRIS = INPUT;
	BluetoothReset=ON; // Pull BT module out of reset
	BluetoothCommand=OFF;//Data mode
	mPORTDOpenDrainClose(BIT_2 | BIT_3); // make sure the com port is driven 3.3
	hasBluetooth();
}
