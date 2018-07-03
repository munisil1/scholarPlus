#include <stdlib.h>
#include "Demo_Switch.c"

void page2_text() {
	const char choose[] = "CHOOSE YOUR CATEGORY: ";

	int i;

	for (i = 0; i < sizeof(choose); i++)
		OutGraphicsCharFont2a((300 + 13 * i), 30, 0, 1, choose[i], 3); //for choose

}

/*******************************************************************************
 ** Function that draws the menu boxes on the screen
 *******************************************************************************/
void draw_menu(int Colour) {
	printf("Drawing filled rectangles through the screen lines\n");
	page2_text();

	drawFilledRectangle(50, 120, 300, 550, Colour);
	drawFilledRectangle(130, 210, 300, 550, Colour);
	drawFilledRectangle(220, 300, 300, 550, Colour);
	drawFilledRectangle(310, 390, 300, 550, Colour);
	drawFilledRectangle(400, 475, 300, 550, Colour);

}

void titles_menu() {
	const char menu[] = "PULMONARY";
	const char menu_1[] = "DISEASES";
	const char menu_2[] = "PREGNANT";
	const char menu_3[] = "ANEMIC";
	const char menu_4[] = "CHILD";
	const char menu_5[] = "HEALTHY";

	int i;
	for (i = 0; i < sizeof(menu); i++)
		OutGraphicsCharFont2a((360 + 13 * i), 70, 0, 6, menu[i], 1); //for pulmonary

	for (i = 0; i < sizeof(menu_1); i++)
		OutGraphicsCharFont2a((370 + 13 * i), 90, 0, 6, menu_1[i], 1); //for diseases

	for (i = 0; i < sizeof(menu_2); i++)
		OutGraphicsCharFont2a((370 + 13 * i), 170, 0, 6, menu_2[i], 1); //for pregnant

	for (i = 0; i < sizeof(menu_3); i++)
		OutGraphicsCharFont2a((380 + 13 * i), 260, 0, 6, menu_3[i], 1); //for Anemic

	for (i = 0; i < sizeof(menu_4); i++)
		OutGraphicsCharFont2a((390 + 13 * i), 350, 0, 6, menu_4[i], 1); //for child

	for (i = 0; i < sizeof(menu_5); i++)
		OutGraphicsCharFont2a((380 + 13 * i), 440, 0, 6, menu_5[i], 1); //for healthy
}
void tostring(char str[], int num) {
	int i;
	int rem;
	int len = 0;
	int n;
	n = num;
	while (n != 0) {
		len++;
		n /= 10;
	}
	for (i = 0; i < len; i++) {
		rem = num % 10;
		num = num / 10;
		str[len - (i + 1)] = rem + '0';
	}
	str[len] = '\0';
}

/*******************************************************************************
 **The function that writes the text choose your category
 *******************************************************************************/

char dataAscii[8][20];

void pulse_title() {
	const char pulse[] = "PULSE RATE FOR: ";
	const char refresh[] = "REFRESH";
	const char reset[] = "RESET";

	drawFilledRectangle(75, 400, 180, 700, 0); //color of screen to show pulse rate

	drawFilledRectangle(410, 465, 540, 610, 3); //refresh button with green
	drawFilledRectangle(410, 465, 630, 700, 2);  //reset button with red

	int i;
	for (i = 0; i < sizeof(pulse); i++)
		OutGraphicsCharFont2a((250 + 13 * i), 45, 0, 1, pulse[i], 1);

	for (i = 0; i < sizeof(refresh); i++)
		OutGraphicsCharFont2a((540 + 10 * i), 430, 1, 3, refresh[i], 1);

	for (i = 0; i < sizeof(reset); i++)
		OutGraphicsCharFont2a((643 + 11 * i), 430, 1, 2, reset[i], 1);

}

void side_menu() {
	const char oxy[] = "O2 Saturation";
	const char abbr[] = "(%SpO2)";
	const char pr[] = "PR/BMP";
	const char opt_oxy[] = "Optimal O2 Saturation: ";
	const char opt_pul[] = "Optimal Pulse Rate: ";
	const char gps_time[] = "Time in UTC";

	int i;
	for (i = 0; i < sizeof(oxy); i++)
		OutGraphicsCharFont2a((40 + 10 * i), 160, 0, 1, oxy[i], 1); //oxygen saturation

	for (i = 0; i < sizeof(abbr); i++)
		OutGraphicsCharFont2a((60 + 13 * i), 180, 0, 1, abbr[i], 1); //abbreviation
	drawRectangle(210, 270, 50, 150, 0);

	for (i = 0; i < sizeof(pr); i++)
		OutGraphicsCharFont2a((70 + 13 * i), 290, 0, 1, pr[i], 1); //bmp and pr
	drawRectangle(320, 380, 50, 150, 0);

	for (i = 0; i < sizeof(opt_oxy); i++)
		OutGraphicsCharFont2a((40 + 10 * i), 415, 4, 1, opt_oxy[i], 1); //Optimal O2 Saturation:

	//for(i = 0; i < sizeof(okValue); i++)
	//OutGraphicsCharFont2a((260 + 11 * i), 415, 4, 1, okValue[i], 1); //OK VALUE DEPENDING ON STATE

	for (i = 0; i < sizeof(opt_pul); i++)
		OutGraphicsCharFont2a((40 + 11 * i), 438, 4, 1, opt_pul[i], 1); //Optimal pulse rate

	for (i = 0; i < sizeof(gps_time); i++)
		OutGraphicsCharFont2a((40 + 11 * i), 100, 4, 1, gps_time[i], 1); //Time

}
