
/**
 * This file is for managment of the onboard bluetooth module
 */
#include "UserApp.h"
boolean btOk = false; 
boolean btChecked = false; 
extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var")));

#define HIGH_BAUD 230400
char packet[50];
#define BT_RESET_DELAY 300
int bauds[] = {
				HIGH_BAUD,
				9600,
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
	int tick = 2000;
	while(Pic32Get_UART_Byte_Count()<2 && tick>0){
		tick--;
		DelayMs(1);
		buttonCheck(100);
	}

}



void configBluetooth(){
	char name [] ="AT+NAMENR_DyIOxxxx\0";
	FlashGetMac(MyMAC.v);
	name[14]=GetHighNib(MyMAC.v[4]);
	name[15]=GetLowNib(MyMAC.v[4]);
	name[16]=GetHighNib(MyMAC.v[5]);
	name[17]=GetLowNib(MyMAC.v[5]);

	sendString(name);
	Pic32UARTGetArray(packet,Pic32Get_UART_Byte_Count());
	if(!(packet[0]=='O' && packet[1]=='K')){
		int i=0;
		for(i=0;i<10;i++){
			SetColor(i%2,i%2,i%2);//Set LED to white
			DelayMs(100);
		}
	}
	if(myBaud == 9600){
		sendString("AT+BAUD9");
		Pic32UARTGetArray(packet,Pic32Get_UART_Byte_Count());
		if(packet[0]=='O' && packet[1]=='K'){
			Pic32UARTSetBaud( HIGH_BAUD );
			BluetoothReset=OFF; // Pull BT module out of reset
			DelayMs(100);
			BluetoothReset=ON; // Pull BT module out of reset
			DelayMs(100 );//wait for it to settle
		}else{
			int i=0;
			for(i=0;i<10;i++){
				SetColor(i%2,0,0);//Set LED to red
				DelayMs(100);
			}
		}
	}
}

boolean testAtCommand(int baud){

	Pic32UARTSetBaud( baud );
	//from http://www.e-gizmo.com/KIT/images/EGBT-04/EGBT-045MS-046S%20Bluetooth%20Module%20Manual%20rev%201r0.pdf
	//Testing AT command
	sendString("AT");
	if( Pic32Get_UART_Byte_Count()>1){
		Pic32UARTGetArray(packet,Pic32Get_UART_Byte_Count());
		if(packet[0]=='O' && packet[1]=='K'){
			return true; 
		}
	}

	return false; 
}

uint8_t hasBluetooth(){
#if defined(HAS_BLUTOOTH)
	if(!btChecked){

		SetColor(1,1,0);//Set LEd to yellow

		/**
		 * Start by checking the possible baudrates
		 */
		int i;
		for(i=0;i<(sizeof(bauds)/sizeof(int));i++){
			if(btOk==false ){
				if(testAtCommand(bauds[i])){
					btOk = true; 
					myBaud  = bauds[i];
					//if(myBaud == 9600){
						configBluetooth();
					//}
				}
			}
		}


		if(!btOk){
			int i=0;
			for(i=0;i<10;i++){
				SetColor(i%2,0,i%2);//Set LED to purple
				DelayMs(100);
			}
		}

		btChecked = true; 
	}
	return btOk;
#else
	return false; 
#endif
}


void initBluetooth(){
#if defined(HAS_BLUTOOTH)
	btChecked = false; 
	mPORTDOpenDrainClose(BIT_1 | BIT_2 | BIT_3); // make sure the com port is driven 3.3
	BluetoothResetTRIS = OUTPUT; //output mode on reset line
	BluetoothCommandTRIS = OUTPUT; //output mode on CMD line
	BluetoothReset=ON; // Pull BT module out of reset
	DelayMs(BT_RESET_DELAY );//wait for it to settle
	if(!hasBluetooth()){
		Pic32UARTSetBaud( 115200 );
	}
#endif
}
