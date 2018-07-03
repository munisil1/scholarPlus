/*******************************************************************************
 * This function contains a library for all the functions to demo for exercise 1.7
 **************************************************************************************/

//#include "Software.c"
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
	int decisionOver2 = 1 - x; // Decision criterion divided by 2 evaluated at x=r, y=0

	WAIT_FOR_GRAPHICS;

	while (y <= x) {
		DrawLineHardware(x0, y0, x + x0, y + y0, COLOUR); // Octant 1
		DrawLineHardware(x0, y0, y + x0, x + y0, COLOUR); // Octant 2
		DrawLineHardware(x0, y0, -x + x0, y + y0, COLOUR); // Octant 4
		DrawLineHardware(x0, y0, -y + x0, x + y0, COLOUR); // Octant 3
		DrawLineHardware(x0, y0, -x + x0, -y + y0, COLOUR); // Octant 5
		DrawLineHardware(x0, y0, -y + x0, -x + y0, COLOUR); // Octant 6
		DrawLineHardware(x0, y0, x + x0, -y + y0, COLOUR); // Octant 7
		DrawLineHardware(x0, y0, y + x0, -x + y0, COLOUR); // Octant 8
		y++;

		if (decisionOver2 <= 0) {
			decisionOver2 += 2 * y + 1; // Change in decision criterion for y -> y+1
		} else {
			x--;
			decisionOver2 += 2 * (y - x) + 1; // Change for y -> y+1, x -> x-1
		}

	}

}

/*******************************************************************************
 ** Function that draws a triangle on the screen
 *******************************************************************************/
void drawTriangle() {
	DrawLineHardware(200, 200, 100, 400, RED);
	DrawLineHardware(100, 400, 300, 400, BLUE);
	DrawLineHardware(300, 400, 200, 200, BLACK);
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

void DrawText(int Colour) {
	const char large_font[] = "CPEN 391 IS SO MUCH FUN: ";
	const char small_font[] = "DEMO FOR TEAM 13 ";
	const char low_case[] = "Hello and Goodbye ";
	const char numbers[] = "15 - 02 - 2017";

	int i;
	for (i = 0; i < sizeof(large_font); i++)
		OutGraphicsCharFont2a((180 + 13 * i), 100, 0, 1, large_font[i], RED);

	for (i = 0; i < sizeof(small_font); i++)
		OutGraphicsCharFont1((180 + 6 * i), 150, 0, 1, small_font[i], BLUE);

	for (i = 0; i < sizeof(low_case); i++)
		OutGraphicsCharFont2a((180 + 13 * i), 200, 0, 1, low_case[i], CYAN);

	for (i = 0; i < sizeof(numbers); i++)
		OutGraphicsCharFont2a((180 + 13 * i), 250, 0, 1, numbers[i], LIME);
}

/*******************************************************************************
 ** Function that clears screen and makes it white
 *******************************************************************************/
void clear_screen(int Colour) {

	printf("Clearing the screen\n");

	int y1;
	for (y1 = 0; y1 <= 600; y1++) {  //FILL THE RECTANGLE WITH color 1 == white
		DrawLineHardware(0, y1, 820, y1, Colour);
	}
}

