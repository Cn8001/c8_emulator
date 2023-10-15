#include "emulator.h"
#include "common.h"
#include "display.h"

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

#include <string.h>
#include <stdio.h>
#include <memory.h>
#include <windows.h>

struct SDL_Window *window;
struct SDL_Renderer *renderer;
struct emulator *emulator;

const char init_sprites[] = {
        0xf0,0x90,0x90,0x90,0xf0, // 0
        0x20,0x60,0x20,0x20,0x70, // 1
        0xf0,0x10,0xf0,0x80,0xf0, // 2
        0xf0,0x10,0xf0,0x10,0xf0, // 3
        0x90,0x90,0xf0,0x10,0x10, // 4
        0xf0,0x80,0xf0,0x10,0xf0, // 5
        0xf0,0x80,0xf0,0x90,0xf0, // 6
        0xf0,0x10,0x20,0x40,0x40, // 7
        0xf0,0x90,0xf0,0x90,0xf0, // 8
        0xf0,0x90,0xf0,0x10,0xf0, // 9
        0xf0,0x90,0xf0,0x90,0x90, // A
        0xe0,0x90,0xe0,0x90,0xe0, // B
        0xf0,0x80,0x80,0x80,0xf0, // C
        0xe0,0x90,0x90,0x90,0xe0, // D
        0xf0,0x80,0xf0,0x80,0xf0, // E
        0xf0,0x80,0xf0,0x80,0x80  // F
};

int load_program(char *),init(),handle_events(SDL_Event*);
void draw_screen(),intro();

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("[ERROR] Usage: %s <path to program>\n",argv[0]);
        exit(-1);
    }
    SDL_Event e;
    int qsignal=1,intro_v=1,res;

    /*Initialize*/
    res = init();
    
    /*Load program*/
    res = load_program(argv[1]);

    /*Game loop*/
    while(qsignal){
        /*Handle interrupts*/
        qsignal = handle_events(&e);

        clear_screen_buffer(&emulator->display);
        if(intro_v){
            intro();
            intro_v=0;
            Sleep(1000);
            emulator->registers.ST = 20;
        }
        /*Draw*/
        draw_screen();
        SDL_ShowWindow(window);

        /*Delay timer and sound timer*/
        if(emulator->registers.DT-- > 0)
            Sleep(3);
        if(emulator->registers.ST > 0){
            Beep(4000,10 * emulator->registers.ST);
            emulator->registers.ST =0;
        }
    }

    SDL_DestroyWindow(window);
    free(emulator);
    return res;
}

int init(){
    const char map[] = {
        SDLK_0,SDLK_1,SDLK_2,SDLK_3,
        SDLK_4,SDLK_5,SDLK_6,SDLK_7,
        SDLK_8,SDLK_9,SDLK_a,SDLK_b,
        SDLK_c,SDLK_d,SDLK_e,SDLK_f
    };
    /*Init SDL and create a renderer*/
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(EMULATOR_TITLE,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,(WINDOW_W * WINDOW_MULT),(WINDOW_H * WINDOW_MULT),0);
    renderer = SDL_CreateRenderer(window,-1,0);
    if(!window || !renderer)
        fatal("while initializing SDL window");
    
    /*Initialize emulator and all context (keyboard-pixels-memory etc.)*/
    emulator = (struct emulator*)malloc(sizeof(struct emulator));
    if(!emulator)
        fatal("while creating the emulator context");
    memset(emulator,0,sizeof(struct emulator));
    
    /*Set keyboard map*/
    emulator->keyboard.map = map;

    /*Copy default characters to the location*/
    memcpy(&emulator->memory.memory[INTERPETER_START_ADDR],init_sprites,sizeof(init_sprites));
    return 0;
}

int load_program(char *filename){
    FILE *f;
    if((f = fopen(filename,"rb")) == NULL)
        fatal("when opening the file");
    
    fseek(f,0,SEEK_END);
    int size = ftell(f);
    rewind(f); // OR fseek(f,0,seek_set)

    char *buffer;
    if((buffer=(char*)malloc(size)) == NULL)
        fatal("not enough memory to read the program");
    if(fread(buffer,size,1,f) != 1) //Read one chunk (one 2800 bytes not 2800 of 1 bytes)
        fatal("while reading the file");
    
    /*Copy program to the memory*/
    if(MEMORY_SIZE-PROGRAM_START_ADDR < size)
        fatal("Program is too big");
    memcpy(&emulator->memory.memory[PROGRAM_START_ADDR],buffer,size);

    free(buffer);
    fclose(f);

    /*For debug purpose*/
    #if defined(DEBUG)
    printf("[DEBUG] The program %s has size %d and copied to addr started from 0x%x\n",filename,size,PROGRAM_START_ADDR);
    #endif
    return 0;
}

void draw_screen(){
    int x,y;

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);

    for(y=0;y<WINDOW_H;y++){
        for(x=0;x<WINDOW_W;x++){
            if(pixel_is_set(&emulator->display,x,y)){
                /*Basically r is a big pixel Width=10 H=10*/
                struct SDL_Rect r;
                r.w = WINDOW_MULT;
                r.h = WINDOW_MULT;
                r.x = x*WINDOW_MULT;
                r.y = y*WINDOW_MULT;

                SDL_RenderFillRect(renderer,&r);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

int handle_events(SDL_Event *e){
    while(SDL_PollEvent(e)){
        switch (e->type){
            case SDL_QUIT:
                return 0;
            break;

            case SDL_KEYDOWN:
            {
                int key = e->key.keysym.sym;
                int vkey;
                if((vkey = keyboard_button_index(key,emulator->keyboard.map)) >=0)
                    keyboardClick(&emulator->keyboard,vkey);
            };
            break;

            case SDL_KEYUP:
            {
                int key = e->key.keysym.sym;
                int vkey;
                if((vkey = keyboard_button_index(key,emulator->keyboard.map)) >=0)
                    keyboardUp(&emulator->keyboard,vkey);
            };
            break;

            default:
                break;
        }
    }
    return 1;
}

void intro(){
    draw_sprite(&emulator->display,26,14,&emulator->memory.memory[0x3C],5);
    draw_sprite(&emulator->display,31,14,&emulator->memory.memory[0x41],5);
    draw_screen();
}