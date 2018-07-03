//
//  page1.c
//  
//
//  Created by Yixin Zhao on 2017-02-14.
//
//

#include "page1.h"

void page1() {

	clear_screen(1);
	const char title[] = "PULSE RATE & OXYGEN SATURATION FEEDBACK";
	const char welcome[] = "WELCOME!";
	const char setts[] = "SETTING UP THE SYSTEM........";

	//border for wwelcome age
	//drawFilledRectangle(80, 400, 50, 300, BLACK);
	drawFilledRectangle(20, 470, 100, 690, CYAN);
	//drawFilledRectangle(110, 370, 80, 270, WHITE);
	drawFilledRectangle(50, 440, 130, 660, WHITE);

	int i;
	for (i = 0; i < sizeof(title); i++)
		OutGraphicsCharFont2a((150 + 13 * i), 100, 0, 1, title[i], 1);

	for (i = 0; i < sizeof(welcome); i++)
		OutGraphicsCharFont2a((350 + 13 * i), 200, 0, 1, welcome[i], 1);

	for (i = 0; i < sizeof(setts); i++)
		OutGraphicsCharFont2a((230 + 13 * i), 350, BLUE, 1, setts[i], 1);

	usleep(5000000);

}
