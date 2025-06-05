#ifndef ICEWALL_EXPLOSION_H_INCLUDED
#define ICEWALL_EXPLOSION_H_INCLUDED

#include "../element/projectile.h"
#include "../element/character.h"
#include "../element/element.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"

#define ICEWALL_EXPLOSION_WIDTH 64
#define ICEWALL_EXPLOSION_HEIGHT 64

void IceWall_Explosion_Initialize(Projectile *proj);
void IceWall_Explosion_Interaction_Character(Elements *self, Elements *tar);
void IceWall_Explosion_Interaction_Ground(Elements *self, Elements *tar);

#endif
