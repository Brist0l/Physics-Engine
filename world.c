#include <stdio.h>
#include <stdlib.h>

#include "includes/world.h"
#include "includes/body.h"


void world_set_gravity(World *world, vector2 gravity)
{
    world->gravity = gravity;
}


void world_init(World *world)
{
    world->num_of_bodies = 0;
    world->capacity = MAX_BODIES;

    world_set_gravity(
        world,
        (vector2){0.0f, -9.81f}
    );

    world->fixed_dt = 1.0f / 60.0f;
}


void world_destroy(World *world)
{
    /*
     * bodies[] is part of the World itself.
     * It was not allocated using malloc(),
     * so DO NOT free(world->bodies).
     */

    world->num_of_bodies = 0;
    world->capacity = 0;
}


particle2 *world_create_body(World *world)
{
    if (world->num_of_bodies >= world->capacity) {
        printf("Number of bodies exceeded capacity\n");
        return NULL;
    }

    particle2 *body =
        &world->bodies[world->num_of_bodies];

    world->num_of_bodies++;

    return body;
}


void world_simulate(World *world, bool by_euler)
{
    for (unsigned int i = 0;
         i < world->num_of_bodies;
         i++)
    {
        particle2 *p = &world->bodies[i];

        /*
         * Gravity is converted into force here.
         *
         * F = ma
         * therefore:
         * F = gravity * mass
         */

        p->force.x = world->gravity.x * p->mass;
        p->force.y = world->gravity.y * p->mass;


        if (by_euler) {
            euler_step(p);
        }
        else {
            calcforce(p);
            calcacc(p);
            calcvel(p);
            calcpos(p);
        }

        p->elp_time += world->fixed_dt;
    }
}
