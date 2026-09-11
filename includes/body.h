#ifndef BODY_H
#define BODY_H

#include "../includes/vec2.h"

typedef struct{
    float mass;
    float elp_time;

    vector2 pos;
    vector2 vel;
    vector2 acc;
    vector2 force;

    float restituion;
}particle2;

void calcforce(particle2 *p);
void calcacc(particle2 *p);
void calcpos(particle2 *p);
void calcvel(particle2 *p);
void stats(particle2 *p, bool header);


#endif
