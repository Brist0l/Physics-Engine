#ifndef WORLD_H
#define WORLD_H

#include <stdbool.h>

#include "vec2.h"
#include "body.h"

#define MAX_BODIES 100

typedef struct World {
    /* World properties */
    vector2 gravity;

    /* Bodies */
    unsigned int num_of_bodies;
    unsigned int capacity;

    particle2 bodies[MAX_BODIES];

    /* Simulation */
    float fixed_dt;

} World;


/* World management */
void world_init(World *world);
void world_destroy(World *world);


/* World configuration */
void world_set_gravity(World *world, vector2 gravity);


/* Body management */
particle2 *world_create_body(World *world);


/* Simulation */
void world_simulate(World *world, bool by_euler);

#endif
