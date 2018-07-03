#include "Menu_Pages.c"


#include <stdio.h>
#include <unistd.h>
#include "GPS.c"
#include "Bluetooth.c"


int main()
{
	 int GPS_flag = 0;
	demo_page();
	//draw_page();
char s[22];
    init_Bluetooth();
    putStringBluetooth("YIXIN");
    Init_GPS();
    int i = 0;
        while(s[i] != '@'){
            while(s[0] != '$')
                s[0] = getChar_Bluetooth();

            i ++;
            s[i] = getChar_Bluetooth();

            if(s[i] == '*'){
            	GPS_flag = 1;
            	//printf("GOT the special charc");

            }
        }


        int j;
        for(j = 1; j < 10; j ++){
            printf("%c", s[j]);
            OutGraphicsCharFont2a((250 + 13 * j), 230, 0, 1, s[j], 3);
        }

        if(GPS_flag ==1){
               	 printf("before GPS REAL TIME\n");
               	GPS_Real_Time();
               }




    return 0;
}

