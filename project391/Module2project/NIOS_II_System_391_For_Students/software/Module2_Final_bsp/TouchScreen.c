
/**********************    Touch Screen    *************************************************/
#include <TouchScreen.h>



/*****************************************************************************
 Initialise touch screen controller
*****************************************************************************/

/****              putcharTouch_Screen      *******/

int putcharTouch_Screen(int c)
{
 /// poll Tx bit in 6850 status register. Wait for it to become '1'
	// write 'c' to the 6850 TxData register to output the character
		while ((Touch_Status & 0x02) != 0x02)
		{}	;
		//printf (" after while loooop ");
		Touch_Transmit = c & 0xFF;
		return Touch_Transmit; // return c

}

/******           getcharTouch_Screen             *************/

int getcharTouch_Screen( void )
{
	int rx;
		// poll Rx bit in 6850 status register. Wait for it to become '1'
		// read received character from 6850 RxData register.
		while ((Touch_Status & 0x01) != 0x01)
			;
		rx = Touch_Recieve;
		return rx;

}

/***********      Init_Touch           *********/
void Init_Touch(void)
{
	// Program 6850 and baud rate generator to communicate with touchscreen
	// send touchscreen controller an "enable touch" command
	Touch_Control = 0x15;
	Touch_Baud = 0x05;
		
	// enable touch
	putcharTouch_Screen(0x55);
	putcharTouch_Screen(0x01);
	putcharTouch_Screen(0x12);
		
	return;
}

/*********   test if screen touched   *************************************/
int ScreenTouched( void )
{
 
	return ((Touch_Recieve &0x80) == 0x80);
}

/******** wait for screen to be touched ****************************************/
void WaitForTouch()
{
while(!ScreenTouched())
 ;
}

/* a data type to hold a point/coord */
//typedef struct { int x, y; } Point ;

/**** This function waits for a touch screen press event and returns X,Y coord **************/

Point GetPress(void)
{
	Point p1;
	int buf[4];
 	int i;
 	int yOffset = 100;
 	// wait for a pen down command then return the X,Y coord of the point
 	// calibrated correctly so that it maps to a pixel on screen
 	WaitForTouch();
 	// pick up reponse packets
 	for (i = 0; i < 4; i++) {
 		buf[i] = getcharTouch_Screen();
 	}
 	// parse x and y coordinates
 	p1.x = (buf[1] << 7) | buf[0];
 	p1.y = (buf[3] << 7) | buf[2];
 	// compute screen coordinates
 	p1.x = p1.x * 799 / 4095;
 	p1.y = (p1.y - yOffset) * 479 / (4095 - yOffset);
	printf (" GetPress: X coord =  %d \t Y coord =  %d  \n" , p1.x, p1.y);
 	
	return p1;

}

/********* This function waits for a touch screen release event and returns X,Y coord *************/

Point GetRelease(void)
{
 Point p1;
 int buf[4];
 	int i;
 	int yOffset = 100;
 	// wait for a pen down command then return the X,Y coord of the point
 	// calibrated correctly so that it maps to a pixel on screen
 	WaitForTouch();
 	// pick up reponse packets
 	for (i = 0; i < 4; i++) {
 		buf[i] = getcharTouch_Screen();
 	}
 	// parse x and y coordinates
 	p1.x = (buf[1] << 7) | buf[0];
 	p1.y = (buf[3] << 7) | buf[2];
 	// compute screen coordinates
 	p1.x = p1.x * 799 / 4095;
 	p1.y = (p1.y - yOffset) * 479 / (4095 - yOffset);

	printf ( " GetRelease: X coord =  %d \t Y coord =  %d\n " , p1.x, p1.y);

	return p1;

}

//////////////////////////////////////////////////////
Point GetPressNoWait(void) {
	Point p1;
	int buf[4];
	int i;
	int yOffset = 100;
	// wait for a pen down command then return the X,Y coord of the point
	// calibrated correctly so that it maps to a pixel on screen
	WaitForTouch();
	printf("Outof wait Touch\n");
	// pick up reponse packets
	for (i = 0; i < 4; i++) {
		buf[i] = getcharTouch_Screen();
	}
	// parse x and y coordinates
	p1.x = (buf[1] << 7) | buf[0];
	p1.y = (buf[3] << 7) | buf[2];
	// compute screen coordinates
	p1.x = p1.x * 799 / 4095;
	p1.y = (p1.y - yOffset) * 479 / (4095 - yOffset);
	printf(" GetPressFromNoWait: X coord =  %d \t Y coord =  %d  \n", p1.x,
			p1.y);

	return p1;

}


