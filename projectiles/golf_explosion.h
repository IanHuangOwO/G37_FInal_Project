#ifndef GOLF_EXPLOSION_H_INCLUDED
#define GOLF_EXPLOSION_H_INCLUDED

#include "../element/projectile.h"
#include "../element/character.h"
#include "../element/element.h"
#include "../scene/sceneManager.h"

#define GOLF_EXPLOSION_WIDTH 64
#define GOLF_EXPLOSION_HEIGHT 64

void Golf_Explosion_Initialize(Projectile *proj);
void Golf_Explosion_Interaction_Character(Elements *self, Elements *tar);
void Golf_Explosion_Interaction_Ground(Elements *self, Elements *tar);

#endif