#ifndef DEFS_H
#define DEFS_H

struct vector2 {
    float x;
    float y;
};

struct vector3 {
    struct vector2 v;
    float z;
};

struct vel2 {
    float x;
    float y;
};

struct vel3 {
    struct vel2 v;
    float z;
};

struct acc2 {
    float x;
    float y;
};

struct acc3 {
    struct acc2 a;
    float z;
};

struct force2 {
    float x;
    float y;
};

struct force3 {
    struct force2 f;
    float z;
};

struct particle2 {
    float mass;
    float elp_time;
    struct vector2 pos;
    struct vel2 vel;
    struct acc2 acc;
    struct force2 force;
};


typedef struct vector2  vector2;
typedef struct vector3  vector3;

typedef struct vel2     vel2;
typedef struct vel3     vel3;

typedef struct acc2     acc2;
typedef struct acc3     acc3;

typedef struct force2   force2;
typedef struct force3   force3;

typedef struct particle2 particle2;

void calcforce(particle2 *p);
void calcacc(particle2 *p);
void calcpos(particle2 *p);
void calcvel(particle2 *p);
void stats(particle2 *p, bool header);

#endif
