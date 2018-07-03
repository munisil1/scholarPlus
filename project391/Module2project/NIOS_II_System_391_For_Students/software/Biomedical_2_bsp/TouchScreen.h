/**********************    Touch Screen    *************************************************/
#include <stdio.h>


#define Touch_Control (*(volatile unsigned char *)(0x84000230))
#define Touch_Status (*(volatile unsigned char *)(0x84000230))
#define Touch_Transmit (*(volatile unsigned char *)(0x84000232))
#define Touch_Recieve (*(volatile unsigned char *)(0x84000232))
#define Touch_Baud (*(volatile unsigned char *)(0x84000234))

int putcharTouch_Screen(int c);
void Init_Touch(void);
int ScreenTouched( void );
void WaitForTouch();

typedef struct { int x, y; } Point ;

Point GetPress(void);
Point GetRelease(void);
Point GetPressNoWait(void);
