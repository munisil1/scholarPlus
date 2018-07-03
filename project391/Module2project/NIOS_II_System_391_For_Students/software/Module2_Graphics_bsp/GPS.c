

/**********************      GPS      ********************/
#include <GPS.h>


/********* Initialise GPS controller **************************************/
/************************************   putchar_GPS      ***************************************/
int putchar_GPS(int c)
{
 // poll Tx bit in 6850 status register. Wait for it to become '1'
 // write 'c' to the 6850 TxData register to output the character
	while ((GPS_Status & 0x02) != 0x02 )
	{};

	return GPS_Transmit =  c & 0x7F;

}
/************************************   getcharGPS      ***************************************/

int getcharGPS( void )
{
 // poll Rx bit in 6850 status register. Wait for it to become '1'
 // read received character from 6850 RxData register.
	while ((GPS_Status & 0x01) != 0x01 ){};
	//printf("before while");
	 unsigned char TS;
               TS  = GPS_Recieve ;
            //   printf ("getDone,Touch_Recieve= %x \n" , TS );
	 return TS ;

}

/************************************   putString     ***************************************/

void putString(char *s) {
	char i;
	printf("before while");
	while ((i = *s) != 0) {

		putchar_GPS(i);
		s++;
	}
	printf("out of while");
}

/*****   we might need those     *****************************/

void StopLogging(void) {
	char *buff = "$PMTK185,1";
	putString(buff);

}

void ClearLogging(void) {
	char *buff = "$PMTK184,1";
	putString(buff);
}

void StartLogger(void) {
	char *buff = "$PMTK186,1";
	putString(buff);

}

/***********************  Init_GPS    *******************************/

void Init_GPS(void)
{
 // 9600 baud, 8 bits of data, no parity, 1 stop bit etc
	    GPS_Control 	= 0x15;
	    GPS_Baud 		= 0x05; //9600 baud

	    return;
}

/******************************************************************************
// takes a 4 byte float in string form (8 chars) and converts to 4 byte form
// (still stored in an int but in float form)
// and swaps the bytes order the reason for this is the GPS outputs the
// longitude and latitude LOG data in 4 byte float form but as little endian
// NIOS however uses big endian

int swapEndian(char *s){

	register int val;
	val = strtoul(s, NULL, 16) ; // convert to 4 byte int form in base 16
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF );
	val = (val << 16) | ((val >> 16) & 0xFFFF);
	return val ;
}

// these two functions take a 4 byte IEEE-754 format float
// (passed as a 4 byte int representing latitude and longitude values)
// in big endian format and converts it to an ASCII decimal string
// which it returns with decimal point in the string.
char *FloatToLatitudeConversion(int x) //output format is xx.yyyy
{
	static char buff[100] ;
	float *ptr = (float *)(&x) ; // cast int to float
	float f = *ptr ; // get the float
	sprintf(buff, "%2.4f", f); // write in string to an array
	return buff ;
}


char *FloatToLongitudeConversion(int x) // output format is (-)xxx.yyyy
{
	static char buff[100] ;
	float *ptr = (float *)(&x) ;
	float f = *ptr ;
	sprintf(buff, "%3.4f", f);
	return buff ;
}


char count;
				char arr [100] ={0} ;
				int i=0;
//void combined_string(void){



//}
*******************************************************/

/********     print GPS data on 7seg              *******************/

void printTo7Seg (int num){


	hex1 = num % 100;
	hex2 = (num % 10000)/100;
	hex3 = num / 10000;

	return;

}

/******************         Switches manipulation                   *********************/

void printGpsData(int data[8]){

	int sw = switches;
	switch (sw){
	case 0:
		// print time
		printTo7Seg(data[0]);
		break;

	case 1:
		// print latitude part1
		printTo7Seg(data[2]);
		break;
	case 2:
		// print latitude par2
		printTo7Seg(data[3]);

		break;
	case 3:
		// print N / S
		printTo7Seg(data[4]);
		break;
	case 4:
		// print longitude part1
		printTo7Seg(data[5]);
		break;
	case 5:
		// print longitude par2
		printTo7Seg(data[6]);
		break;
	case 6:
			// print E / W
		printTo7Seg(data[7]);
		break;

	}

}

//global variable used to get GPS data and display them on the touch screen
char dataAscii [8][20] ;

/*****        Extact data from GPS               **********************/
char dataAscii [8][20] ;
void getGpsInfo(void){
	//printf("inside INFO>>>>> \n");
	int  buffer [200];
				int c;
				int i=0;
					do{
					 c = getcharGPS();
					// printf("after get char, %c \n", getcharGPS());
					 buffer[i] = c;
					// printf("c: \n ", buffer[i]);

					 i++;
					}while (c != '\n');
					i=0;
					if (buffer[4] == 'G'){
						printf("INSIDE IF \n");
						i=7;
						int  data[8];
						int  k=0;
						do{
							int  j = 0;
							char tmp[20];
							printf("tmp creation");

							do{
								if (buffer[i] != ',' && buffer[i] != '.')
									tmp[j] = buffer[i];
									dataAscii[k][j]= tmp[j];
								printf("%c", buffer[i]);
								i++;j++;
							}while (buffer[i] != ',' && buffer[i] != '.');
							tmp[j] = '\0';
							if (k == 4){
								data[k] = (tmp[0] == 'N')?2:3;
							}else if (k == 7){
								data[k] = (tmp[0] == 'W')?4:5;
							}else
								data[k] = atoi(tmp);

							printf (" data int %d\n",data[k]);
							k++;
						}while (buffer[i] != '\n' && k<8);



							printGpsData(data);


						printf("\n");
						return;
					}
					i=0;
}

///////////////////////////REAL TIME
void GPS_Real_Time() {
	//printf("inside REAL TIME");
	getGpsInfo();
	int i;
	char tmp[8];
	int k = 0;
	int j;
	for (j = 0; j < 8; j++) {

		if ((j == 2) || (j == 5))
			tmp[j] = ':';
		else {
			tmp[j] = dataAscii[0][k];
			k++;
		}

	}
	for (i = 0; i < 8; i++) {
		printf("%c", tmp[i]);

		//printf("right after tmp");
		OutGraphicsCharFont2a((40 + 13 * i), 120, 4, 1, tmp[i], 1); //for actual value of data

	}
}
