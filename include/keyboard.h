#if !defined(KEYBOARD_H)
#define KEYBOARD_H
#include <stdbool.h>
#include <stdint.h>

struct keyboard{
    bool keyboard[16];
    uint8_t map[16];
};

void keyboardClick(struct keyboard *keyboard,uint8_t button_num);
bool is_clicked(struct keyboard *keyboard,uint8_t button_num);

#endif

