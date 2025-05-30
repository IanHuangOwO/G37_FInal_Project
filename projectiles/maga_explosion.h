#ifndef MAGA_EXPLOSION_H_INCLUDED
#define MAGA_EXPLOSION_H_INCLUDED

#include "../element/projectile.h"
#include "../element/character.h"
#include "../element/element.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"

#define MAGA_EXPLOSION_WIDTH 64
#define MAGA_EXPLOSION_HEIGHT 64

void Maga_Explosion_Initialize(Projectile *proj);
void Maga_Explosion_Interaction_Character(Elements *self, Elements *tar);
void Maga_Explosion_Interaction_Ground(Elements *self, Elements *tar);

#endif