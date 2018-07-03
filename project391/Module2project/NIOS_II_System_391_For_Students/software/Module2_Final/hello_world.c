#include "Menu_Pages.c"
#include <stdio.h>
#include <unistd.h>
#include "GPS.c"
#include <stdlib.h>
#include <string.h>

#define BLUETOOTH_Status (*(volatile unsigned char *)(0x84000220))
#define BLUETOOTH_RxData (*(volatile unsigned char *)(0x84000222))

int main() {

	draw_page();
	Init_Touch();
	Init_GPS();
	init_Bluetooth();

	char s[9];
	int timeRequired = 0;
	int i = 0;
	while (1) {
		while (BLUETOOTH_Status & 0x1) {
			s[i] = BLUETOOTH_RxData;
			while (s[i] != '@') {
				i++;
				s[i] = getChar_Bluetooth();
				if (s[i] == '1')
					timeRequired = 1;

			}

			printf("out of the loop s[%d] is %c\n ", i, s[i]);
		}
		if (timeRequired != 0) {
			GPS_Real_Time();
			timeRequired = 0;
		}
		if (ScreenTouched()/*(Touch_Status & 0x01) == 0x01*/) {
			Point res;
			//printf("touch screen has something for me");

			if ((Touch_Recieve & 0x81) == 0x81) {
				//printf("get press has something for me");
				res = GetPressNoWait();
				//GetPress();
				if(res.x > 310 && res.x < 460 && res.y > 409 && res.y < 475){
					putStringBluetooth("Q1");
					printf("i have enabled polling \n");
				}


			}
//			} else {
//				printf("get release has something for me");
//				GetRelease();
//			}
			/* getting the message from android
			 * If the ending char '@' is not received,
			 * keep getting data and start putting it in the string if we get the starting char '$'
			 * If we get the special char '*' means a student is connected and real-time need to be sent
			 *
			 */
//				GPS_Real_Time();
			/*
			 * read the question file and write it on the screen
			 * when clicked on next, show next question
			 * send the question number to the Android Studio
			 * draw the stop line after click on start pooling
			 */
		}
	}
	return 0;

}

