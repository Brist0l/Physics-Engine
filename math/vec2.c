#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "../includes/vec2.h"
#include "../includes/body.h"

vector2 *vec2_add(vector2 *a,vector2 *b){
	vector2 *temp = (vector2 *) malloc(sizeof(vector2));
	temp->x = a->x + b->x;
	temp->y = a->y + b->y;

	return temp;
}

vector2 *vec2_sub(vector2 *a,vector2 *b){
	vector2 *temp = (vector2 *) malloc(sizeof(vector2));
	temp->x = a->x - b->x;
	temp->y = a->y - b->y;

	return temp;
}

void vec2_scale(vector2 *a,const int r){
	a->x *= r;
	a->y *= r;
}

float vec2_dot(vector2 *a,vector2 *b){
	return (a->x * b->x) + (a->y * b->y);
}

float vec2_lenght(vector2 *a){
	// sqrt(x^2 + y^2)
	return sqrt(pow(a->x,2) + pow(a->y,2));

}

void calcforce(particle2 *p){
	p->force.x = p->mass * p->acc.x;
	p->force.y = p->mass * p->acc.y;
}

void calcacc(particle2 *p){
	p->acc.x = p->force.x / p->mass;
	p->acc.y = p->force.y / p->mass;
}

void calcvel(particle2 *p){
	p->vel.x = p->vel.x + p->acc.x * p->elp_time;
	p->vel.y = p->vel.y + p->acc.y * p->elp_time;
}

void calcpos(particle2 *p){
	p->pos.x += p->vel.x * p->elp_time + 0.5 * p->acc.x * p->elp_time * p->elp_time;
	p->pos.y += p->vel.y * p->elp_time + 0.5 * p->acc.y * p->elp_time * p->elp_time;

}

// Semi-Explicit Euler method
void euler_step(particle2 *p){
	calcforce(p);
	calcacc(p);

    // 1. Update velocity first
	p->vel.x += p->acc.x * p->elp_time;
	p->vel.y += p->acc.y * p->elp_time;

    // 2. Update position using the brand new velocity
	p->pos.x += p->vel.x * p->elp_time;
	p->pos.y += p->vel.y * p->elp_time;
}

void stats(particle2 *p, bool header){
	if(header == 1)
		printf("Pos\t\tVel\t\tAcc\t\tForce\t\tMass\t\tTime\n");

		printf("(%0.2f,%0.2f)\t\(%0.2f,%0.2f)\t(%0.2f,%0.2f)\t(%0.2f,%0.2f)\t%0.2f\t\t%0.2f\n",p->pos.x,p->pos.y,p->vel.x,p->vel.y,p->acc.x,p->acc.y,p->force.x,p->force.y,p->mass,p->elp_time);
}
