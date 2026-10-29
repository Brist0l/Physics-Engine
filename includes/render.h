#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "world.h"

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;

    int width;
    int height;
} Renderer;

int renderer_init(Renderer *r, int width, int height);
void renderer_draw(Renderer *r, World *world);
void renderer_destroy(Renderer *r);

#endif
