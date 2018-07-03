#include <Instantiate.h>
#include "Draw_Functions.c"
#include "TouchScreen.c"

int temp_color;
void polling_Status(int Colour){
	char polling[] = "START POLLING";
	drawFilledRectangle(419, 465, 320, 450, Colour); //change color to green
	int i;
	for (i = 0; i < sizeof(polling); i++)
	OutGraphicsCharFont1((327 + 9 * i), 438, 15, 1, polling[i], 2);

}

void draw_page() {
	//draw the background color
	clear_screen(1); //some kind of dirty blue 119 //250 gray
	polling_Status(3);
	drawFilledRectangle(0, 100, 0, 800, 50); //insert the top bar

	char class_name[] = "CPEN 391";
	char next[] = "NEXT";
	char last[] = "BACK";
	char show_ans[] = "SHOW ANSWER";
	char activity[] = "ACTIVITY";
	char answer[] = "Correct Answer: ";

	int i;
	for (i = 0; i < sizeof(class_name); i++)
		OutGraphicsCharFont2a((350 + 13 * i), 50, 0, 1, class_name[i], 2); //display the name of class in progress

	//frame for the question
	drawFilledRectangle(150, 370, 280, 770, 1);
	DrawHLineHardware(282, 371, 488, 15);
	DrawHLineHardware(282, 372, 488, 15);
	DrawVLineHardware(771, 152, 217, 15);
	DrawVLineHardware(772, 152, 218, 15);

	//Rectangle to start polling


	DrawCircleFill(100, 440, 25, 50);  //for the previous button
	DrawCircleFill(690, 440, 25, 50);  //for the next button
	//DrawLineHardware(680, 430, 700, 440, 15);
	//DrawLineHardware(700, 440, 680, 450, 15);

	for (i = 0; i < sizeof(next); i++)
		OutGraphicsCharFont1((675 + 9 * i), 438, 15, 1, next[i], 2);
	for (i = 0; i < sizeof(last); i++)
		OutGraphicsCharFont1((85 + 8 * i), 438, 15, 1, last[i], 2);

	//side bar for activity and answer button
	drawFilledRectangle(150, 200, 50, 147, 50);  //show answer box
	for (i = 0; i < sizeof(show_ans); i++)
		OutGraphicsCharFont1((55 + 8 * i), 175, 15, 1, show_ans[i], 2);

	drawFilledRectangle(230, 280, 50, 147, 50);  //activity box
	for (i = 0; i < sizeof(activity); i++)
		OutGraphicsCharFont1((65 + 8 * i), 255, 15, 1, activity[i], 2);

	for (i = 0; i < sizeof(answer); i++)
		OutGraphicsCharFont2a((38 + 11 * i), 300, 0, 1, answer[i], 2);

}

void multiple_qn() {
	char question[] = "How are you finding CPEN 391 ?";
	char choiceA[] = "A. A walk in the park!";
	char choiceB[] = "B. What's CPEN 391?";
	char choiceC[] = "C. It's a joke";
	char choiceD[] = "D. I don't know what i'm doing ";
	char choiceE[] = "E. None of the above";
	int i;
	for (i = 0; i < sizeof(question); i++)
		OutGraphicsCharFont2a((350 + 11 * i), 160, 0, 1, question[i], 2);
	for (i = 0; i < sizeof(choiceA); i++)
		OutGraphicsCharFont2a((380 + 11 * i), 230, 0, 1, choiceA[i], 2);
	for (i = 0; i < sizeof(choiceB); i++)
		OutGraphicsCharFont2a((380 + 11 * i), 260, 0, 1, choiceB[i], 2);
	for (i = 0; i < sizeof(choiceC); i++)
		OutGraphicsCharFont2a((380 + 11 * i), 290, 0, 1, choiceC[i], 2);
	for (i = 0; i < sizeof(choiceD); i++)
		OutGraphicsCharFont2a((380 + 11 * i), 320, 0, 1, choiceD[i], 2);
	for (i = 0; i < sizeof(choiceE); i++)
		OutGraphicsCharFont2a((380 + 11 * i), 350, 0, 1, choiceE[i], 2);

}

void shuffle_names() {
	//make the layout
	//draw the background color
	clear_screen(1); //some kind of dirty blue 119 //250 gray
	drawFilledRectangle(0, 100, 0, 800, 50); //insert the top bar

	///draw box for activity
	char class_name[] = "CPEN 391";
	char question[] = "QUESTIONS";
	char group1[] = "GROUP 1";
	char group2[] = "GROUP 2";
	drawFilledRectangle(230, 290, 600, 720, 50); //rectangle for questions
	int i;
	for (i = 0; i < sizeof(class_name); i++)
		OutGraphicsCharFont2a((350 + 13 * i), 50, 0, 1, class_name[i], 2); //d

	for (i = 0; i < sizeof(question); i++)
		OutGraphicsCharFont2a((610 + 11 * i), 255, 15, 1, question[i], 2);

	for (i = 0; i < sizeof(group1); i++)
		OutGraphicsCharFont2a((100 + 11 * i), 160, 0, 1, group1[i], 2);

	for (i = 0; i < sizeof(group2); i++)
		OutGraphicsCharFont2a((350 + 11 * i), 160, 0, 1, group2[i], 2);

}


void handle_touch() {

	Init_Touch();
	while (1) {
		if ((Touch_Status & 0x01) == 0x01) {

			if ((Touch_Recieve & 0x81) == 0x81) {
				GetPress();
			}

			else
				GetRelease();
		}

	}

}

void demo_page(){
	clear_screen(100);
	char title[] = "TEXT RECIEVED FROM THE BLUETOOTH: ";

	int i;
		for (i = 0; i < sizeof(title); i++)
			OutGraphicsCharFont2a((200 + 13 * i), 200, 0, 1, title[i], 3);

}

