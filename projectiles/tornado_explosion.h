#ifndef TORNADO_EXPLOSION_H_INCLUDED
#define TORNADO_EXPLOSION_H_INCLUDED

#include "../element/projectile.h"
#include "../element/character.h"
#include "../element/element.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"

#define TORNADO_EXPLOSION_WIDTH 64
#define TORNADO_EXPLOSION_HEIGHT 64

void Tornado_Explosion_Initialize(Projectile *proj);
void Tornado_Explosion_Interaction_Character(Elements *self, Elements *tar);
void Tornado_Explosion_Interaction_Ground(Elements *self, Elements *tar);
void Tornado_Destroy_Ground_At_Hitbox(Shape *hitbox, int player);

#endif