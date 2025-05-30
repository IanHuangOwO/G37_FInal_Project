#ifndef DEPORT_EXPLOSION_H_INCLUDED
#define DEPORT_EXPLOSION_H_INCLUDED

#include "../element/projectile.h"
#include "../element/character.h"
#include "../element/element.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"

#define DEPORT_EXPLOSION_WIDTH 64
#define DEPORT_EXPLOSION_HEIGHT 64

void Deport_Explosion_Initialize(Projectile *proj);
void Deport_Explosion_Interaction_Character(Elements *self, Elements *tar);
void Deport_Explosion_Interaction_Ground(Elements *self, Elements *tar);

#endif