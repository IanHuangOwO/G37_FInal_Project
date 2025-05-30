#ifndef TANK_EXPLOSION_H_INCLUDED
#define TANK_EXPLOSION_H_INCLUDED

#include "../element/projectile.h"
#include "../element/character.h"
#include "../element/element.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"

#define TANK_EXPLOSION_WIDTH 64
#define TANK_EXPLOSION_HEIGHT 64

void Tank_Explosion_Initialize(Projectile *proj);
void Tank_Explosion_Interaction_Character(Elements *self, Elements *tar);
void Tank_Explosion_Interaction_Ground(Elements *self, Elements *tar);

#endif