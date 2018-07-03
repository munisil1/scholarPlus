#include "Demo_Switch.c"

#include <stdlib.h>

#define switches (*(volatile unsigned short int *)(0x00002000))


int flag = 0;
int last_sw;



void printShapes(void){

	int sw = switches;
	int i, last_sw;

while(1){
	last_sw= sw;
	sw = switches;

	if(last_sw != sw){
		flag =0;
	}
	switch (sw){
	


	case 1:
		// clear screen , white background
		if(!flag){
		clear_screen(1);
		flag = 1;
		}
		break;

	case 2:

		//Draw many horizontal lines on the screen
		if(!flag){
		clear_screen(1);

		for(i = 0; i < 480; i++){
		DrawHLineHardware(0, i, 800, rand()%8);
		}
		flag = 1;
		}
		break;
	
	case 3:
		//Draw many vertical lines on the screen
		if(!flag){
		clear_screen(1);
		for(i = 0; i < 800; i++){
		DrawVLineHardware(i, 0, 480, rand()%8);
		}
		flag = 1;
		}
		break;
	
	case 4:
		//Draw a filled rectangle and an empty rectangle with a border
		if(!flag){
		clear_screen(1);
		drawFilledRectangle(80, 400, 50, 300, BLACK);
		drawFilledRectangle(110, 370, 80, 270, WHITE);

		drawRectangle(80, 400, 420, 700 ,RED);
		drawRectangle(110, 370, 450, 670,BLUE);
		flag = 1;
		}
		break;
	
	case 5:
		//Draw an empty triangle on the screen
		if(!flag){
		clear_screen(1);
		drawTriangle();
		flag = 1;
		}
		break;
	
	case 6:
		//Function to draw an empty circle, filled circle and an arc
		if(!flag){
		clear_screen(1);
		drawcircle(150, 200, 90, RED);
		DrawCircleFill(340, 200, 90, CYAN);
		DrawArc(540, 200, 100, LIME);
		flag = 1;
		}
		break;
	
	case 7:
		//Function to draw multiple rectangles flickering on the screen
	  //DrawHLineHardware(rand()% 800,rand()% 480, rand()%800,rand()%8);
	  //DrawVLineHardware(rand()% 800,rand()% 480, rand()%480,rand()%8);
		drawFilledRectangle(rand()% 800,rand()% 480,rand()% 800,rand()% 480,rand()%8);
		break;
		
	case 8:
		//Function to display different texts on screen
		if(!flag){
		clear_screen(1);
		DrawText(BLACK);
		flag = 1;
		}
		break;

	default:
		if(!flag){
		clear_screen(3);
		flag = 1;
		}
		break;
	}
}
}
