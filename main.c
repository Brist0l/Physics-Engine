#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "includes/world.h"
#include "includes/args.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define PIXELS_PER_METER 2.0f
#define TARGET_FPS 60
#define FRAME_DELAY (1000 / TARGET_FPS)

static int world_to_screen_x(float x)
{
    return WINDOW_WIDTH / 2 + (int)(x * PIXELS_PER_METER);
}

static int world_to_screen_y(float y)
{
    return WINDOW_HEIGHT - (int)(y * PIXELS_PER_METER);
}

int main(int argc, char *argv[])
{
    struct t_thing args = sendargs(argc, argv);
    bool by_euler = pyboolconverter(args.sliced_args[0]);

    if (by_euler)
        printf("Simulating using Euler\n");
    else
        printf("Simulating using Semi-Explicit Euler\n");

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "2D Physics Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (renderer == NULL) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    World world;
    world_init(&world);

    particle2 *p1 = world_create_body(&world);
    p1->mass = 82.0f;
    p1->pos.x = -150.0f;
    p1->pos.y = 100.0f;
    p1->vel.x = 25.0f;  // Given initial velocity to animate
    p1->vel.y = 10.0f;
    p1->acc.x = 1.0f;
    p1->acc.y = 0.0f;
    p1->force.x = 0.0f;
    p1->force.y = 0.0f;
    p1->elp_time = 0.0f;

    particle2 *p2 = world_create_body(&world);
    p2->mass = 200.0f;
    p2->pos.x = 150.0f;
    p2->pos.y = 100.0f;
    p2->vel.x = -20.0f; // Given initial velocity to animate
    p2->vel.y = 15.0f;
    p2->acc.x = 0.0f;
    p2->acc.y = 2.0f;
    p2->force.x = 0.0f;
    p2->force.y = 0.0f;
    p2->elp_time = 0.0f;

    particle2 *p3 = world_create_body(&world);
    p3->mass = 82.0f;
    p3->pos.x = -50.0f;
    p3->pos.y = 50.0f;
    p3->vel.x = 5.0f;  // Given initial velocity to animate
    p3->vel.y = 1.0f;
    p3->acc.x = 0.0f;
    p3->acc.y = 0.0f;
    p3->force.x = 0.0f;
    p3->force.y = 0.0f;
    p3->elp_time = 0.0f;

    bool running = true;
    SDL_Event event;
    Uint32 frame_start;
    int frame_time;

    while (running)
    {
        frame_start = SDL_GetTicks();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        world_simulate(&world, by_euler);

        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);

        for (unsigned int i = 0; i < world.num_of_bodies; i++)
        {
            particle2 *p = &world.bodies[i];

            int x = world_to_screen_x(p->pos.x);
            int y = world_to_screen_y(p->pos.y);

            SDL_Rect body = {
                x - 5,
                y - 5,
                10,
                10
            };

            if (i == 0) {
                SDL_SetRenderDrawColor(renderer, 255, 80, 80, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, 80, 150, 255, 255);
            }

            SDL_RenderFillRect(renderer, &body);
        }

        SDL_RenderPresent(renderer);

        frame_time = SDL_GetTicks() - frame_start;
        if (FRAME_DELAY > frame_time) {
            SDL_Delay(FRAME_DELAY - frame_time);
        }
    }


    world_destroy(&world);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
