#ifndef POOP_H_INCLUDED
#define POOP_H_INCLUDED

#include "../element/projectile.h"
#include "../element/element.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"

#define POOP_WIDTH 64
#define POOP_HEIGHT 64

void Poop_Initialize(Projectile *proj);
void Poop_Interaction_Character(Elements *self, Elements *tar);
void Poop_Interaction_Ground(Elements *self, Elements *tar);

#endif