#include "includes/render.h"
#include <stdio.h>

int renderer_init(Renderer *r, int width, int height)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 0;
    }

    r->window = SDL_CreateWindow(
        "2D Physics Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!r->window) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    r->renderer = SDL_CreateRenderer(
        r->window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (!r->renderer) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(r->window);
        SDL_Quit();
        return 0;
    }

    r->width = width;
    r->height = height;

    return 1;
}

static int world_to_screen_y(Renderer *r, float y)
{
    return r->height - (int)y;
}

void renderer_draw(Renderer *r, World *world)
{
    SDL_SetRenderDrawColor(
        r->renderer,
        20, 20, 20, 255
    );

    SDL_RenderClear(r->renderer);

    SDL_SetRenderDrawColor(
        r->renderer,
        255, 255, 255, 255
    );

    for (unsigned int i = 0;
         i < world->num_of_bodies;
         i++)
    {
        particle2 *p = &world->bodies[i];

        int x = (int)p->pos.x;
        int y = world_to_screen_y(r, p->pos.y);

        SDL_Rect body = {
            x - 5,
            y - 5,
            10,
            10
        };

        SDL_RenderFillRect(r->renderer, &body);
    }

    SDL_RenderPresent(r->renderer);
}

void renderer_destroy(Renderer *r)
{
    SDL_DestroyRenderer(r->renderer);
    SDL_DestroyWindow(r->window);
    SDL_Quit();
}
