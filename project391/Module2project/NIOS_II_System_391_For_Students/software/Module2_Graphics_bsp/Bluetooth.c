
/*
 * Set up 6850 Control register to utilise a divided by 16 clock
 * Slave mode
 * Serial port: Baud = 115 kbps use 8 bits of data, no parity, one stop bit
 * Serial port flow control disabled
 */


#define BLUETOOTH_Control (*(volatile unsigned char *)(0x84000220))
#define BLUETOOTH_Status (*(volatile unsigned char *)(0x84000220))
#define BLUETOOTH_TxData (*(volatile unsigned char *)(0x84000222))
#define BLUETOOTH_RxData (*(volatile unsigned char *)(0x84000222))
#define BLUETOOTH_Baud (*(volatile unsigned char *)(0x84000224))

#define SECONDS 1000000

void init_Bluetooth(void){
	printf("Start initialising the bluetooth...");
	BLUETOOTH_Control = 0x15;
	BLUETOOTH_Baud = 0x01;
	usleep(SECONDS); //wait for 100ms
	printf("Done initialization\n");
}

/*
 * Poll Tx bit in 6850 status register. Wait for it to become "1", and then
 * write c to the 6850 TxData register to output the character
 */
char putChar_Bluetooth(char c){

	while(1){
		if(BLUETOOTH_Status & 0x2){
			BLUETOOTH_TxData = c;
			break;
		}
	}
		return c;


}

/*
 * Poll Rx bit in 6850 status register. Wait for it to become "1", and then
 * read received character from 6850 RxData register
 */

char getChar_Bluetooth(void){
	while(1){
		if(BLUETOOTH_Status & 0x1){
			break;
		}
	}
	return BLUETOOTH_RxData;
}


/*
 * Send the command to the bluetooth dongle through the serial port.
 */
void send_command(char string[], int length){
	printf("Start sending the commands...");
	int i = 0;
	for(; i < length; i++){
		usleep(SECONDS); //wait for 100ms
		putChar_Bluetooth(string[i]);
	}
	printf("Commands sent\n");
}

/*
 * Enter the command mode
 */
void start_command(){
	usleep(SECONDS); //wait for 100ms
	send_command("$$$", 3); //Enter the command mode
	usleep(SECONDS); //wait for 100ms
	printf("Start the command mode here\n");
}

/*
 * Quit the command mode
 */
void end_command(){
	usleep(SECONDS); //wait for 100ms
	send_command("---\r\n", 5); //Exit the command mode
	usleep(SECONDS); //wait for 100ms
	printf("Exit the command mode here\n");
}

void putStringBluetooth(char *s){
	char i;
	while((i = *s) != 0){
		putChar_Bluetooth(i);
		s++;
	}
}

/*
 * Reset the bluetooth dongle
 */
void dongle_reset(){
	char *resetCommand = "SF,1\r\n";
	printf("doing a factory reset");
	putStringBluetooth(resetCommand);
}

void change_name(void){
	 const char name[] = "ZXYM";
	 printf("Start setting up the Bluetooth name: '%s'", name);
	  send_command("SN,", 3);
	  send_command(name, 3);
	  send_command("\r\n", 2);
	  printf("Done with the name setup...");
}

void change_password(){
	  const char password[] = "0987";

	    printf("Start setting up the Bluetooth password: '%s'", password);
	    send_command("SP,", 3);
	    send_command(password, 4);
	    send_command("\r\n", 2);

}



void getStringBluetooth(char s[]){
    int i = 0;
    while(s[i] != '@'){
        while(s[0] != '$')
            s[0] = getChar_Bluetooth();
        i ++;
        s[i] = getChar_Bluetooth();
    }
    int j;
    for(j = 1; j < 6; j ++){
    	printf("%o", j);
        printf("%c", s[j]);
    }

}
