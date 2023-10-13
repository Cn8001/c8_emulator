#if !defined(MEMORY_H)
#define MEMORY_H
#include <stdint.h>
struct emulator;
/*

Memory Map:
+---------------+= 0xFFF (4095) End of Chip-8 RAM
|               |
|               |
|               |
|               |
|               |
| 0x200 to 0xFFF|
|     Chip-8    |
| Program / Data|
|     Space     |
|               |
|               |
|               |
|               |
|               |
|               |
|               |
+---------------+= 0x200 (512) Start of most Chip-8 programs
| 0x000 to 0x1FF|
| Reserved for  |
|  interpreter  |
+---------------+= 0x000 (0) Start of Chip-8 RAM

ALSO 16 16-bit stack

*/

#define INTERPETER_START_ADDR   0x000
#define PROGRAM_START_ADDR      0x200
#define MEMORY_SIZE             4096
#define STACK_SIZE              16

struct memory{
    uint8_t memory[MEMORY_SIZE];
    uint16_t stack[STACK_SIZE];
};

uint8_t memory_read_byte(struct memory *memory, int index);
void memory_write_byte(struct memory *memory, int index, uint8_t byte);
void push(struct emulator *emulator,uint16_t dbyte);
uint16_t pop(struct emulator *emulator);

#endif