#if !defined(EMULATOR_H)
#define EMULATOR_H

#define EMULATOR_TITLE "CHIP-8"

#include "memory.h"
#include "registers.h"
#include "keyboard.h"
#include "display.h"


struct emulator{
    struct memory memory;
    struct registers registers;
    struct keyboard keyboard;
    struct display display;
};
#endif