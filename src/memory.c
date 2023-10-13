#include "memory.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include "common.h"
#include "emulator.h"

uint8_t memory_read_byte(struct memory *memory,int index){
    if(index >= MEMORY_SIZE || index < 0){
        printf("INDEX OUT OF BOUNDS\n");
        exit(-1);
    }
    return memory->memory[index];
}
void memory_write_byte(struct memory *memory, int index, uint8_t byte){
    if(index >= MEMORY_SIZE || index < 0){
        printf("INDEX OUT OF BOUNDS\n");
        exit(-1);
    }
    memory->memory[index] = byte;
}
void push(struct emulator *emulator,uint16_t dbyte){
    if(emulator->registers.SP >= 15){
        printf("STACK IS FULL\n");
        exit(-1);
    }
    emulator->memory.stack[emulator->registers.SP++] = dbyte;
    
}
uint16_t pop(struct emulator *emulator){
    /*TODO: Reaching NULL variable problem*/
    return emulator->memory.stack[emulator->registers.SP--];
}