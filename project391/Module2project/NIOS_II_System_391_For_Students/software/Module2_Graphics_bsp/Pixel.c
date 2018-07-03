

#include <Instantiate.h>

/**********************************************************************

 * This function writes a single pixel to the x,y coords specified in the specified colour

 * Note colour is a palette number (0-255) not a 24 bit RGB value
 **********************************************************************/
void WriteAPixel(int x, int y, int Colour) {
	WAIT_FOR_GRAPHICS
	;			// is graphics ready for new command

	GraphicsX1Reg = x;			// write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsColourReg = Colour;		// set pixel colour with a palette number
	GraphicsCommandReg = PutAPixel;		// give graphics a "write pixel" command
	GraphicsBackGroundColourReg = Colour; //set the background color to white

}

/*****************************************************************************************
 * This function read a single pixel from x,y coords specified and returns its colour
 * Note returned colour is a palette number (0-255) not a 24 bit RGB value
 ******************************************************************************************/
int ReadAPixel(int x, int y) {
	WAIT_FOR_GRAPHICS
	;			// is graphics ready for new command

	GraphicsX1Reg = x;			// write coords to x1, y1
	GraphicsY1Reg = y;
	GraphicsCommandReg = GetAPixel;		// give graphics a "get pixel" command
	GraphicsBackGroundColourReg = 1;

	WAIT_FOR_GRAPHICS
	;			// is graphics done reading pixel
	return (int) (GraphicsColourReg);	// return the palette number (colour)
}

/****************************************************************************************************
 ** subroutine to program a hardware (graphics chip) palette number with an RGB value
 ** e.g. ProgramPalette(RED, 0x00FF0000) ;
 ****************************************************************************************************/

void ProgramPalette(int PaletteNumber, int RGB) {
	WAIT_FOR_GRAPHICS
	;
	GraphicsColourReg = PaletteNumber;
	GraphicsX1Reg = RGB >> 16;        // program red value in ls.8 bit of X1 reg
	GraphicsY1Reg = RGB;         // program green and blue into 16 bit of Y1 reg
	GraphicsCommandReg = ProgramPaletteColour;	// issue command
	GraphicsBackGroundColourReg = 1;
}
