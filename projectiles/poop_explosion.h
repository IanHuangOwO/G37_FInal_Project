#ifndef POOP_EXPLOSION_H_INCLUDED
#define POOP_EXPLOSION_H_INCLUDED

#include "../element/projectile.h"
#include "../element/character.h"
#include "../element/element.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"

#define POOP_EXPLOSION_WIDTH 64
#define POOP_EXPLOSION_HEIGHT 64

void Poop_Explosion_Initialize(Projectile *proj);
void Poop_Explosion_Interaction_Character(Elements *self, Elements *tar);
void Poop_Explosion_Interaction_Ground(Elements *self, Elements *tar);

#endif