#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#include "includes/vec2.h"
#include "includes/body.h"

#define MAX_BODIES 100
#define g -9.8

struct w{
	// properties of world
	vector2 gravity;

	// bodies definations
	unsigned int num_of_bodies;
	unsigned int capacity;

	particle2 bodies[MAX_BODIES];

	// time
	float fixed_dt;
};

void world_set_gravity(struct w* world,vector2 gravity){
	world->gravity = gravity;

}

void world_init(struct w* world){
	world->num_of_bodies = 0;
	world->capacity = MAX_BODIES;

	world_set_gravity(world,(vector2){0.0f,9.81f});

	world->fixed_dt = 1.0f/ 60.0f;
}

particle2 *world_create_body(struct w *world, particle2 *p)
{
    if (world->num_of_bodies >= world->capacity) {
        printf("Number of bodies exceeded capacity\n");
        exit(1);
    }

    world->bodies[world->num_of_bodies] = *p;

    particle2 *body = &world->bodies[world->num_of_bodies];

    world->num_of_bodies++;

    return body;
}

void world_destroy(struct w* world){
	free(world->bodies);

	world->num_of_bodies = 0;
	world->capacity = 1;
}

void world_simulate(struct w* world){
	for(int i = 0;i < world->num_of_bodies;i++){
		particle2 *p = &world->bodies[i];

		calcforce(p);
		calcacc(p);
		calcvel(p);
		calcpos(p);

		p->elp_time += world->fixed_dt;
	}
}


int main(){
	// world definations
	struct w *world = (struct w*) malloc(sizeof(struct w));
	particle2 *p1 = (particle2*) malloc(sizeof(particle2));

	float ti = 0;
	float tf = 1;

	bool h = true;

	p1->mass = 82;
	p1->acc.x = 1;
	p1->acc.y = g;
	p1->pos.x = 0;
	p1->pos.y = 100;
	p1->elp_time = ti;

	world_init(world);
	p1 = world_create_body(world,p1);

	while(ti <= tf){
		world_simulate(world);

		stats(p1,h);

		ti += world->fixed_dt;

		if(h == true)
			h = false;

	}
}
