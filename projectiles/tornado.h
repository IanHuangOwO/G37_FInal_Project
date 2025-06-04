#ifndef TORNADO_H_INCLUDED
#define TORNADO_H_INCLUDED

#include "../element/projectile.h"
#include "../element/element.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"

#define TORNADO_WIDTH 64
#define TORNADO_HEIGHT 64

void Tornado_Initialize(Projectile *proj);
void Tornado_Interaction_Character(Elements *self, Elements *tar);
void Tornado_Interaction_Ground(Elements *self, Elements *tar);
void Tornado_Update(Elements *self);


#endif