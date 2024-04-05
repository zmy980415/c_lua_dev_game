#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "engine.h"

#define nullptr ((void*)0)






int main(int argc, char** args)
{
    Engine* engine = NULL;
    SDL_Renderer* renderer = NULL;
    int flag = SDL_Init(SDL_INIT_VIDEO);
    if (flag) {
        exit(-1);
    }
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    
    engine = init();

    extern SDL_Renderer* global_renderer;

    SDL_Window* window = SDL_CreateWindow(
        engine->engineConfig->title,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        engine->engineConfig->width, 
        engine->engineConfig->height, 
        SDL_WINDOW_SHOWN);

    global_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;
    char quit = 0;
    SDL_Rect r1 = {0,0,100,100};
    SDL_Rect r2 = {100,100,200,200};
    SDL_Point p = { 500,100 };

    engine->funInit(engine->L);
    
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            if (event.type == SDL_KEYDOWN) {
                printf("you pressed %d", event.key.keysym.sym);
            }
        }
        engine->funUpdate(engine->L, 0.001f);
        SDL_SetRenderDrawColor(global_renderer, 0, 0, 0, 255);
        SDL_RenderClear(global_renderer);
        engine->funDraw(engine->L);
        SDL_RenderPresent(global_renderer);

       
    }
    lua_close(engine->L);  // ¹Ø±Õ²¢Ïú»ÙLua×´Ì¬
    SDL_DestroyRenderer(global_renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    exit(0);
    return 0;
}