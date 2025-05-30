#ifndef TANK_H_INCLUDED
#define TANK_H_INCLUDED

#include "../element/projectile.h"
#include "../element/element.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"

#define TANK_WIDTH 64
#define TANK_HEIGHT 64

void Tank_Initialize(Projectile *proj);
void Tank_Interaction_Character(Elements *self, Elements *tar);
void Tank_Interaction_Ground(Elements *self, Elements *tar);

#endif