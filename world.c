#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#include "includes/vec2.h"
#include "includes/body.h"
#include "includes/args.h"

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

void world_simulate(struct w* world,bool by_e){
	for(int i = 0;i < world->num_of_bodies;i++){
		particle2 *p = &world->bodies[i];


		if(by_e == true)
			euler_step(p);
		else{
			calcforce(p);
			calcacc(p);
			calcvel(p);
			calcpos(p);
		}

		p->elp_time += world->fixed_dt;
	}
}


int main(int argc,char* argv[]){
	// world definations
	struct w *world = (struct w*) malloc(sizeof(struct w));
	particle2 *p1 = (particle2*) malloc(sizeof(particle2));
	particle2 *p2 = (particle2*) malloc(sizeof(particle2));

	struct t_thing args = sendargs(argc,argv);
	bool by_euler = pyboolconverter(args.sliced_args[0]);

	if(by_euler == true)
		printf("Simulating using euler\n");

	float ti = 0;
	float tf = 0.5;

	bool h = true;

	p1->mass = 82;
	p1->acc.x = 1;
	p1->acc.y = g;
	p1->pos.x = 0;
	p1->pos.y = 100;
	p1->elp_time = ti;

	p2->mass = 200;
	p2->acc.x = 0;
	p2->acc.y = g;
	p2->pos.x = 0;
	p2->pos.y = 100;
	p2->elp_time = ti;

	world_init(world);

	p1 = world_create_body(world,p1);
	p2 = world_create_body(world,p2);

	while(ti <= tf){
		world_simulate(world,by_euler);

		ti += world->fixed_dt;


        	// P1 uses Linear/Explicit Kinematics

        	printf("P1 -> ");
		stats(p1, h);

		if(h == true)
			h = false;


       	 	// P2 uses Semi-Explicit Euler


        	printf("P2 -> ");
		stats(p2, h);

		printf("\n");

		p1->mass -= 1;
		p2->mass -= 1;
	}
}
