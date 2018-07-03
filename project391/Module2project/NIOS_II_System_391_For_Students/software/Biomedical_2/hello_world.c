
#include <main.h>
#include <const.h>
#include "page1.c"
#include "page2.c"
#include "page3.c"
#include "Boimed.c"
#include "WIFI.c"

char okValue_SpO2[7];
char okValue_PR[11];
char title_cat[9];

char pregnant[] = "PREGNANT ";
int SpO2_L = 70;
int SpO2_H = 100;
#define pregOk_SpO2_L  95
#define pregOk_SpO2_H 99
char pregOk_SpO2[] = "95%-99%";
char pregOk_PR[] = "80-90bpm  ";

char anemic[] = "ANEMIC ";
#define anemiaOk_SpO2_L 92
#define anemiaOk_SpO2_H 99
char anemiaOk_SpO2[] = "92%-99%";
char anemiaOk_PR[] = "135-139bpm";

char chil[] = "A CHILD";
#define childOk_SpO2_L 93
#define childOk_SpO2_H 99
char childOk_SpO2[] = "92%-99%";
char childOk_PR[] = "130-137bpm";

char pulmonary[] = "PULMONIC ";
#define pulmOk_SpO2_L 90
#define pulmOk_SpO2_H 99
char pulmOk_SpO2[] = "90%-99%";
char pulmOk_PR[] = "90-120bpm";

char heal[] = "HEALTHY";
#define healthyOk_SpO2_L 94
#define healthyOk_SpO2_H 99
char healthyOk_SpO2[] = "94%-99%";
char healthyOk_PR[] = "60-100bpm";

int offset = 48;
int graph_offset = 350;
int graphing_colour = BLUE;


char invalid[] = "N/A";
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
///////////////////////////REAL TIME
void GPS_Real_Time() {
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

		OutGraphicsCharFont2a((40 + 13 * i), 120, 4, 1, tmp[i], 1); //for actual value of data

	}
}


//---------------draw the screen--------------------------------------------

int main() {



	int categ = 0;
	int gps_flag = 0;
	int x = 190;

	page1();

reset:

	graphing_colour = BLUE;
	page2(); //menu

	categ = button_Pressed();

	//the buttonPressed() waits until the screen is touched
	//if no button is pressed then categ will be 0, and keep calling it until a button is pressed

	while (!categ)
		categ = button_Pressed();

	int i;
	switch (categ) {
	case preg:
		for (i = 0; i < sizeof(pregOk_SpO2); i++)
			okValue_SpO2[i] = pregOk_SpO2[i];
		SpO2_L = pregOk_SpO2_L;
		SpO2_H = pregOk_SpO2_H;
		for (i = 0; i < sizeof(pregnant); i++)
			title_cat[i] = pregnant[i];
		for (i = 0; i < sizeof(pregOk_PR); i++)
			okValue_PR[i] = pregOk_PR[i];
		break;
	case anemia:
		for (i = 0; i < sizeof(anemiaOk_SpO2); i++)
			okValue_SpO2[i] = anemiaOk_SpO2[i];
		SpO2_L = anemiaOk_SpO2_L;
		SpO2_H = anemiaOk_SpO2_H;
		for (i = 0; i < sizeof(anemic); i++)
			title_cat[i] = anemic[i];
		for (i = 0; i < sizeof(anemiaOk_PR); i++)
			okValue_PR[i] = anemiaOk_PR[i];
		break;
	case child:
		for (i = 0; i < sizeof(childOk_SpO2); i++)
			okValue_SpO2[i] = childOk_SpO2[i];
		SpO2_L = childOk_SpO2_L;
		SpO2_H = childOk_SpO2_H;
		for (i = 0; i < sizeof(chil); i++)
			title_cat[i] = chil[i];
		for (i = 0; i < sizeof(childOk_PR); i++)
			okValue_PR[i] = childOk_PR[i];
		break;
	case pulm:
		for (i = 0; i < sizeof(pulmOk_SpO2); i++)
			okValue_SpO2[i] = pulmOk_SpO2[i];
		SpO2_H = pulmOk_SpO2_H;
		SpO2_L = pulmOk_SpO2_L;
		for (i = 0; i < sizeof(pulmonary); i++)
			title_cat[i] = pulmonary[i];
		for (i = 0; i < sizeof(pulmOk_PR); i++)
			okValue_PR[i] = pulmOk_PR[i];
		break;
	case healthy:
		for (i = 0; i < sizeof(healthyOk_SpO2); i++)
			okValue_SpO2[i] = healthyOk_SpO2[i];
		SpO2_H = healthyOk_SpO2_H;
		SpO2_L = healthyOk_SpO2_L;
		for (i = 0; i < sizeof(heal); i++)
			title_cat[i] = heal[i];
		for (i = 0; i < sizeof(healthyOk_PR); i++)
			okValue_PR[i] = healthyOk_PR[i];
		break;
	default:
		for (i = 0; i < sizeof(healthyOk_SpO2); i++)
			okValue_SpO2[i] = healthyOk_SpO2[i];
		SpO2_H = healthyOk_SpO2_H;
		SpO2_L = healthyOk_SpO2_L;
		for (i = 0; i < sizeof(heal); i++)
			title_cat[i] = heal[i];
		for (i = 0; i < sizeof(healthyOk_PR); i++)
			okValue_PR[i] = healthyOk_PR[i];
		break;
	}
	Init_GPS();
	Init_Bio();


	page3();
	init_wifi();
	int pv1 = get_Pulse();
	int pv2 = get_Pulse();
	//functions that display the hard-coded optimal values
	for (i = 0; i < sizeof(okValue_SpO2); i++)
		OutGraphicsCharFont2a((260 + 11 * i), 415, 4, 1, okValue_SpO2[i], 1); //OK VALUE of oxygen

	for (i = 0; i < sizeof(okValue_PR); i++)
		OutGraphicsCharFont2a((260 + 11 * i), 438, 4, 1, okValue_PR[i], 1); //OK VALUE of pulse rate

	for (i = 0; i < sizeof(title_cat); i++)
		OutGraphicsCharFont2a((454 + 11 * i), 45, 4, 1, title_cat[i], 1); //title of category

refresh:
	graphing_colour = BLUE;
	x = 190;

	while (1) {

		GPS_Real_Time();

		if (ScreenTouched()) {
			Point res;
			res = GetPressNoWait();
			if ((res.x > 630 && res.x < 700) && (res.y > 410 && res.y < 465)) {
				printf("before back to reset\n");
				goto reset;
			}
			else if ((res.x > 540 && res.x < 610)
					&& (res.y > 410 && res.y < 465)) {
				printf("refreshing the screen\n");
				drawFilledRectangle(75, 400, 180, 700, 0); //color of screen to show pulse rate
				goto refresh;
			}

		}

		int spo2 = get_Spo2();
		int hr = get_HR();

//		DrawLineHardware(x , graph_offset - pv1 , x+10 , graph_offset - pv2, RED);
//				x = x + 10;
//		if(x > 690){
//				x = 180;
//				drawFilledRectangle(75, 400, 180, 700, 0);//clear the plot area
//		}
//		pv1 = pv2;
//		pv2 = get_Pulse();

		char oxyL[3];

		if(spo2 > 70 && spo2 < 100){
			//check if in valid range, if not change colors to red
			if( spo2 < SpO2_L || spo2 > SpO2_H){
				graphing_colour = RED;
				//wifi function goes here~~~

				printf("initializing wifi to get a call\n");


					putString_wifi("dofile(\"send_text_message.lua\")");
					putString_wifi("gpio.mode(3, gpio.OUTPUT)");
					printf("sending commands\n");
					usleep(10000);

					putString_wifi("check_wifi()");

			}
			oxyL[0] = spo2 / 100 + offset;
			spo2 = spo2 % 100;
			oxyL[0] = spo2 / 10 + offset;
			spo2 = spo2 % 10;
			oxyL[1] = spo2 + offset;
			for (i = 0; i < sizeof(oxyL); i++){
				OutGraphicsCharFont2a((60 + 11 * i), 230, WHITE, 1, invalid[i], 1); //sp02
				OutGraphicsCharFont2a((60 + 11 * i), 230, graphing_colour, 1, oxyL[i], 1); //sp02
			}
		printf("hr = %d\n", hr );
		if(hr > 50 &&  hr < 128){
			char HR[3];
			HR[0] = hr / 100 + offset;
			hr = hr % 100;
			HR[1] = hr / 10 + offset;
			hr = hr % 10;
			HR[2] = hr + offset;
			for (i = 0; i <  sizeof(HR); i++)
				OutGraphicsCharFont2a((60 + 11 * i), 340, graphing_colour, 1, HR[i], 1); //pulse
		}

	}
	else
		for (i = 0; i <  sizeof(invalid); i++){
			OutGraphicsCharFont2a((60 + 11 * i), 230, 0, 1, invalid[i], 1); //pulse
			OutGraphicsCharFont2a((60 + 11 * i), 340, 0, 1, invalid[i], 1);
		}

		//plot the graph here for the values
		pv2 = get_Pulse();
		DrawLineHardware(x , graph_offset - pv1 , x+10 , graph_offset - pv2, graphing_colour);
		x = x + 10;
		if(x > 690){
			x = 180;
			drawFilledRectangle(75, 400, 180, 700, 0);//clear the plot area
		}
		pv1 = pv2;
		pv2 = get_Pulse();


	}



	return 0;
}

