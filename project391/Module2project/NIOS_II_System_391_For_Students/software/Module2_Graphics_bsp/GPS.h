/**********************      GPS      ********************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define pi 3.14159265358979323846


//GPS
#define GPS_Control (*(volatile unsigned char *)(0x84000210))
#define GPS_Status (*(volatile unsigned char *)(0x84000210))
#define GPS_Transmit (*(volatile unsigned char *)(0x84000212)) //TxData
#define GPS_Recieve (*(volatile unsigned char *)(0x84000212)) //RxData
#define GPS_Baud (*(volatile unsigned char *)(0x84000214))

#define switches (*(volatile unsigned short int *)(0x00002000))
#define hex1 (*(volatile unsigned short int *)(0x00002030))
#define hex2 (*(volatile unsigned short int *)(0x00002040))
#define hex3 (*(volatile unsigned short int *)(0x00002050))



int putchar_GPS(int c);
int getcharGPS( void );
void putString(char *s);
void StopLogging(void);
void ClearLogging(void);
void StartLogger(void);
void Init_GPS(void);
void printTo7Seg (int num);
void printGpsData(int data[8]);
void getGpsInfo(void);
void GPS_Real_Time(void);
