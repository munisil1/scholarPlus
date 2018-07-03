
/*********************   WIFI    *****************/
#include<WIFI.h>

/////*****      WIFI       **//


// Configure serial port (Baud = 115Kbps, 8 bits of data, no parity, 1 stop bit)
void init_wifi(void)
{
	//0x03 for resetting the wifi 
	WIFI_CONTROL =0x03;
    WIFI_CONTROL = 0x15;
    WIFI_BAUD = 0x01;
    putString_wifi("\r\n");
    usleep(40000);
    putString_wifi("\r\n");
    usleep(40000);


}

// Function blocks till serial port read status is ready
void wait_for_read_ready()
{
    while((WIFI_STATUS & 0x01) != 0x01);
}

// Write 1-byte of data into serial port [WIFI]
void putchar_wifi(char c)
{
    while ((WIFI_STATUS & 0x02) != 0x02);
    WIFI_TXDATA = c & 0xFF;
}

// Write a string (series of 1-byte data) into serial port [WIFI]
void putString_wifi(char *s)
{
    int i;
    for(i=0; s[i]!='\0'; i++){
        putchar_wifi((char) s[i]);
    }
}

// Read 1-byte of data into serial port [WIFI]
char getchar_wifi(void)
{
    wait_for_read_ready();
    return WIFI_RXDATA;
}

/*                                        */
//int main(){
//
//
//
//	printf("Hello from Nios II!\n");
//	init_wifi();
//
//	putString_wifi("dofile(\"send_text_message.lua\")");
//	putString_wifi("gpio.mode(3, gpio.OUTPUT)");
//	printf("sending commands\n");
//	usleep(10000);
//
//	putString_wifi("check_wifi()");
//
//	return 0;
//}


