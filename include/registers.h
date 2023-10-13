#if !defined(REGISTERS_H)
#define REGISTERS_H

#include <stdint.h>

#define DATA_REGISTER_NUM 16

struct registers{
    uint8_t V[DATA_REGISTER_NUM];
    uint16_t I;
    uint8_t DT;
    uint8_t ST;
    uint8_t PC;
    uint8_t SP;
};
#endif