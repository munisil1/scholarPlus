/*******************************************************************************
 * This function contains a library for all the functions to demo for exercise 1.7
 **************************************************************************************/


#include "Font_Types.c"

/**********************************************************************
 * This function draws a vertical or horizontal line on the screen depending on the command sent

 * Note colour is a palette number (0-255) not a 24 bit RGB value
 **********************************************************************/
void DrawHLineHardware(int x1, int y1, int length, int Colour) {
	WAIT_FOR_GRAPHICS;
	GraphicsX1Reg = x1;
	GraphicsY1Reg = y1;
	GraphicsX2Reg = x1 + length;
	GraphicsY2Reg = y1;
	GraphicsColourReg = Colour;
	GraphicsCommandReg = DrawHLine;

}

void DrawVLineHardware(int x1, int y1, int length, int Colour) {
	WAIT_FOR_GRAPHICS;
	GraphicsX1Reg = x1;
	GraphicsY1Reg = y1;
	GraphicsX2Reg = x1;
	GraphicsY2Reg = y1 + length;
	GraphicsColourReg = Colour;
	GraphicsCommandReg = DrawVLine;

}

void DrawLineHardware(int x1, int y1, int x2, int y2, int Colour) {
	WAIT_FOR_GRAPHICS;
	GraphicsX1Reg = x1;
	GraphicsY1Reg = y1;
	GraphicsX2Reg = x2;
	GraphicsY2Reg = y2;
	GraphicsColourReg = Colour;
	GraphicsCommandReg = DrawLine;

}

/********************************************************
 *Implementation of circle drawing algorithm
 *
 ********************************************************/

void drawcircle(int x0, int y0, int radius, int Colour) {
	int x = radius;
	int y = 0;
	int err = 0;

	WAIT_FOR_GRAPHICS;

	while (x >= y) {
		WriteAPixel(x0 + x, y0 + y, Colour);
		WriteAPixel(x0 + y, y0 + x, Colour);
		WriteAPixel(x0 - y, y0 + x, Colour);
		WriteAPixel(x0 - x, y0 + y, Colour);
		WriteAPixel(x0 - x, y0 - y, Colour);
		WriteAPixel(x0 - y, y0 - x, Colour);
		WriteAPixel(x0 + y, y0 - x, Colour);
		WriteAPixel(x0 + x, y0 - y, Colour);

		if (err <= 0) {
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0) {
			x -= 1;
			err -= 2 * x + 1;
		}
	}



}

/***********************
 * Function that draws an arc or half a circle
 */
void DrawArc(int x0, int y0, int radius, int Colour) {
	int x = radius;
	int y = 0;
	int err = 0;

	WAIT_FOR_GRAPHICS;

	while (x >= y) {
		WriteAPixel(x0 + x, y0 + y, Colour);
		WriteAPixel(x0 + y, y0 + x, Colour);
		WriteAPixel(x0 - y, y0 + x, Colour);
		WriteAPixel(x0 - x, y0 + y, Colour);

		if (err <= 0) {
			y += 1;
			err += 2 * y + 1;
		}
		if (err > 0) {
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

/************************************************************
 * Function to draw a filled circle
 */
void DrawCircleFill(int x0, int y0, int radius, int COLOUR) {
	int x = radius;
	int y = 0;


	WAIT_FOR_GRAPHICS;

	//alternative algorithm
		for( y=-radius; y<=radius; y++)
		    for( x=-radius; x<=radius; x++)
		        if(x*x+y*y <= radius*radius)
		            WriteAPixel(x0+x, y0+y, COLOUR);

}

/*******************************************************************************
 ** Function that draws a triangle on the screen
 *******************************************************************************/
void drawTriangle() {
	DrawLineHardware(200, 200, 100, 400, 2);
	DrawLineHardware(100, 400, 300, 400, 4);
	DrawLineHardware(300, 400, 200, 200, 0);
}

/*******************************************************************************
 **Function that draws a filled rectangle on the screen
 *******************************************************************************/
void drawFilledRectangle(int y1, int y2, int x1, int x2, int Colour) {
	int YVALUE;
	DrawLineHardware(x1, y1, x2, y1, Colour);
	DrawLineHardware(x2, y1, x2, y2, Colour);
	DrawLineHardware(x2, y2, x1, y2, Colour);
	DrawLineHardware(x1, y2, x1, y1, Colour);

	for (YVALUE = y1; YVALUE <= y2; YVALUE++) { //FILL THE RECTANGLE WITH color 6== cyan
		DrawLineHardware(x1, YVALUE, x2, YVALUE, Colour);
	}
}

void drawRectangle(int y1, int y2, int x1, int x2, int Colour) {
	DrawLineHardware(x1, y1, x2, y1, Colour);
	DrawLineHardware(x2, y1, x2, y2, Colour);
	DrawLineHardware(x2, y2, x1, y2, Colour);
	DrawLineHardware(x1, y2, x1, y1, Colour);
}


/*******************************************************************************
 ** Function that clears screen and makes it white
 *******************************************************************************/
void clear_screen(int Colour) {

	printf("Clearing the screen\n");

	int y1;
	for (y1 = 0; y1 <= 600; y1++) {
		DrawLineHardware(0, y1, 820, y1, Colour);
	}
}

