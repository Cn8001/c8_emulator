#if !defined(DISPLAY_H)
#define DISPLAY_H
#include <stdbool.h>
#include "common.h"

struct display{
    bool display[WINDOW_W * WINDOW_H];
};

bool draw_sprite(struct display *display,int x,int y,const char *sprite, int size);
void clear_screen_buffer(struct display *display);
bool pixel_is_set(struct display *display,int x,int y);
#endif