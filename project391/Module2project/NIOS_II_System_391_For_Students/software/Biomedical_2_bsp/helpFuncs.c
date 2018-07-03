//
//  helpFuncs.c
//  
//
//  Created by Yixin Zhao on 2017-02-14.
//
//

#include <helpFuncs.h>
#include <const.h>



//-------check which button is pressed-------

int button_Pressed(){
    
    int choose = 0;
    Point coord;
    
    coord = GetPress();
    //then check if the touched coordinate is a button: if yes, then return the corresponding category; if not, return choose as 0 means did not choose a category
    while(coord.x < 300 || coord.x > 550){
        coord = GetPress();
    }
    
    if(coord.y > 130 && coord.y < 210)//pregnant pressed
        choose = preg;
    else if(coord.y > 220 && coord.y < 300)//anemia pressed
        choose = anemia;
    else if(coord.y > 310 && coord.y < 390)
        choose = child;
    else if(coord.y > 400 && coord.y < 475)
        choose = healthy;
    else if(coord.y > 50 && coord.y < 120)
        choose = pulm;
    
    return choose;
}

////--------------for page3------------------
//void GPS(){
//    //print the time
//}
//
//void check_Reset(){
//
//}
//
//void check_Refresh(){
//
//}
//
//void refresh(){
//    //clear the data seciton
//}

void draw_Data(){
    //do some stuff to draw the real-time data
}


