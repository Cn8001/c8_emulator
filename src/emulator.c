#include "emulator.h"
#include <stdio.h>
#include "common.h"
#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include <fcntl.h>

int main(int argc, char *argv[]){
    struct SDL_Window *window;
    struct SDL_Renderer *renderer;
    int res =0;

    
    /*Init SDL and create a renderer*/
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(EMULATOR_TITLE,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,(WINDOW_W * WINDOW_MULT),(WINDOW_H * WINDOW_MULT),0);
    renderer = SDL_CreateRenderer(window,-1,0);
    if(!window || !renderer)
        fatal("while initializing SDL window");
    
    /*Game loop*/
    SDL_Event e;
    while(1){
        while(SDL_PollEvent(&e)){
            switch (e.type)
            {
            case SDL_QUIT:
                goto quit;
            break;
            
            default:
                break;
            }
        }

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        
        /*Draw things here*/

        SDL_ShowWindow(window);

    }

quit:
    SDL_DestroyWindow(window);
    return res;
}