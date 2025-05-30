#ifndef DEPORT_H_INCLUDED
#define DEPORT_H_INCLUDED

#include "../element/projectile.h"
#include "../element/element.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"

#define DEPORT_WIDTH 64
#define DEPORT_HEIGHT 64

void Deport_Initialize(Projectile *proj);
void Deport_Interaction_Character(Elements *self, Elements *tar);
void Deport_Interaction_Ground(Elements *self, Elements *tar);

#endif