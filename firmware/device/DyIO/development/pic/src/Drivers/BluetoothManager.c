
/**
 * This file is for managment of the onboard bluetooth module
 */
#include "UserApp.h"
BOOL btOk = FALSE;
BOOL btChecked = FALSE;

#define HIGH_BAUD 230400
char packet[50];

int bauds[] = {
				230400,
				9600
				//115200
};
int myBaud = HIGH_BAUD;

int getBluetoothBaud(){
	return myBaud;
}

void sendString(char * data){
	Pic32UARTGetArray(packet,Pic32Get_UART_Byte_Count());
	int i=0;
	while(data[i++]!=0){}
	Pic32UARTPutArray(data,i-1);
	DelayMs(1000);
}

void configBluetooth(){
	sendString("AT+NAMENeuron_Robotics_DyIO");
	Pic32UARTGetArray(packet,Pic32Get_UART_Byte_Count());
	//sendString("AT+BAUD9");
	//Pic32UARTGetArray(packet,Pic32Get_UART_Byte_Count());
	//Pic32UARTSetBaud( HIGH_BAUD );
}

BOOL testAtCommand(int baud){

	Pic32UARTSetBaud( baud );
	BluetoothCommand = OFF;
	// Reset module
	BluetoothReset=BTReset; // reset
	DelayMs(10);
	BluetoothReset=BTNotReset; // reset

	//from http://www.e-gizmo.com/KIT/images/EGBT-04/EGBT-045MS-046S%20Bluetooth%20Module%20Manual%20rev%201r0.pdf
	//Testing AT command
	sendString("AT");
	if( Pic32Get_UART_Byte_Count()>1){
		Pic32UARTGetArray(packet,Pic32Get_UART_Byte_Count());
		if(packet[0]=='O' && packet[1]=='K'){
			SetColor(0,1,0);//Set LEd to green
			DelayMs(1100);
			BluetoothCommand = OFF;
			return TRUE;
		}
	}
	Pic32UARTSetBaud( 9600 );
	BluetoothCommand = OFF;
	DelayMs(500);
	return FALSE;
}

BYTE hasBluetooth(){
	if(!btChecked){

		SetColor(1,1,0);//Set LEd to yellow

		/**
		 * Start by checking the possible baudrates
		 */
		int i;
		for(i=0;i<(sizeof(bauds)/sizeof(int));i++){
			if(btOk==FALSE ){
				if(testAtCommand(bauds[i])){
					btOk = TRUE;
					myBaud  = bauds[i];
					if(bauds[i] == 9600){
						configBluetooth();
					}
				}
			}
		}


		if(!btOk){
			SetColor(1,0,1);//Set LED to purple
			DelayMs(5000);
		}

		btChecked = TRUE;
	}
	return btOk;
}


void initBluetooth(){
	btChecked = FALSE;
	mPORTDOpenDrainClose(BIT_1 | BIT_2 | BIT_3); // make sure the com port is driven 3.3
	BluetoothResetTRIS = OUTPUT; //output mode on reset line
	BluetoothCommandTRIS = OUTPUT; //output mode on CMD line
	BluetoothReset=ON; // Pull BT module out of reset
	Pic32UARTSetBaud( 9600 );
	hasBluetooth();
}
