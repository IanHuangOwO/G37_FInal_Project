#ifndef WINNIE_EXPLOSION_H_INCLUDED
#define WINNIE_EXPLOSION_H_INCLUDED

#include "../element/projectile.h"
#include "../element/character.h"
#include "../element/element.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"

#define WINNIE_EXPLOSION_WIDTH 64
#define WINNIE_EXPLOSION_HEIGHT 64

void Winnie_Explosion_Initialize(Projectile *proj);
void Winnie_Explosion_Interaction_Character(Elements *self, Elements *tar);
void Winnie_Explosion_Interaction_Ground(Elements *self, Elements *tar);

#endif