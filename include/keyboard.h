#if !defined(KEYBOARD_H)
#define KEYBOARD_H
#include <stdbool.h>
#include <stdint.h>

#define NUM_OF_KEYS 16

struct keyboard{
    bool keyboard[NUM_OF_KEYS];
    const char *map;
};

void keyboardClick(struct keyboard *keyboard,int index);
bool is_clicked(struct keyboard *keyboard,int index);
void keyboardUp(struct keyboard *keyboard,int index);
void set_keyboard_map(struct keyboard *keyboard, const char *map);
int keyboard_button_index(int key, const char *map);

#endif

