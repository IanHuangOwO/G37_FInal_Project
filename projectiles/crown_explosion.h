#ifndef CROWN_EXPLOSION_H_INCLUDED
#define CROWN_EXPLOSION_H_INCLUDED

#include "../element/projectile.h"
#include "../element/character.h"
#include "../element/element.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"

#define CROWN_EXPLOSION_WIDTH 64
#define CROWN_EXPLOSION_HEIGHT 64

void Crown_Explosion_Initialize(Projectile *proj);
void Crown_Explosion_Interaction_Character(Elements *self, Elements *tar);
void Crown_Explosion_Interaction_Ground(Elements *self, Elements *tar);

#endif