#ifndef BABY_EXPLOSION_H_INCLUDED
#define BABY_EXPLOSION_H_INCLUDED

#include "../element/projectile.h"
#include "../element/character.h"
#include "../element/element.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"

#define BABY_EXPLOSION_WIDTH 64
#define BABY_EXPLOSION_HEIGHT 64

void Baby_Explosion_Initialize(Projectile *proj);
void Baby_Explosion_Interaction_Character(Elements *self, Elements *tar);
void Baby_Explosion_Interaction_Ground(Elements *self, Elements *tar);

#endif