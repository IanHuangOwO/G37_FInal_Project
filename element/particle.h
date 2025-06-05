#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h"
#include "../algif5/algif.h"
/*
   [particle object]
*/
typedef enum ParticleWho
{
    ULTIMATE = 0,
} ParticleWho;
typedef struct _Particle
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int duration;
    ALGIF_ANIMATION *gif;
} Particle;
Elements *New_Particle(int label, int x, int y, int who, int duration);
void Particle_update(Elements *self);
void Particle_interact(Elements *self);
void Particle_draw(Elements *self);
void Particle_destory(Elements *self);

#endif
