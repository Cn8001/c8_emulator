#include "display.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

bool pixel_is_set(struct display *display,int x,int y){
    return display->display[(y%WINDOW_H)*WINDOW_W+(x%WINDOW_W)];
}

void clear_screen_buffer(struct display *display){
    memset(display->display,0,sizeof(display->display));
}

//Return true if pixel collided returns 0 if none of pixel have collided.
bool draw_sprite(struct display *display,int x,int y,const char *sprite, int size){
    int i,pos;
    bool res;
    res=false;

    //LOOP For Y (Y is each byte)
    for(i=0;i<size;i++){
        char col = sprite[i];

        //LOOP For X (X is each byte and corresponds a pixel)
        for(int j=0;j<__CHAR_BIT__;j++){

            //For collisions we used % operator.
            pos = ((((y+i)%WINDOW_H)*WINDOW_W)+((x+j)%WINDOW_W));
            char pixel;

            //IF pixel = 0, continue.
            if((pixel = col & (0b10000000 >> j)) == 0){
                continue;
            }
            
            //return true if any pixel collided.
            if(pixel_is_set(display,x,y))
                res = true;
            display->display[pos] ^= pixel;
        }
    }
    return res;
}