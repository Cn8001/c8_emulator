#include "keyboard.h"
#include<stdio.h>
#include "common.h"

void keyboardClick(struct keyboard *keyboard,int index){
    if(keyboard != NULL && index >= 0 && index < NUM_OF_KEYS)
        keyboard->keyboard[index] = true;
}
bool is_clicked(struct keyboard *keyboard,int index){
    if(keyboard != NULL && index >= 0 && index < NUM_OF_KEYS)
        return keyboard->keyboard[index];
}
void keyboardUp(struct keyboard *keyboard,int index){
    if(keyboard != NULL && index >= 0 && index < NUM_OF_KEYS)
        keyboard->keyboard[index] = false;
}
void set_keyboard_map(struct keyboard *keyboard, const char *map){
    if(sizeof(map) == 16)
        keyboard->map = map;
}
int keyboard_button_index(int key, const char *map){
    int i;
    for(i=0;i<sizeof(map),map[i] != key;i++);
    i = i>15 ? -1 : i;
    return i;
}