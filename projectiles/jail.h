#ifndef JAIL_EXPLOSION_H_INCLUDED
#define JAIL_EXPLOSION_H_INCLUDED

#include "../element/projectile.h"
#include "../element/character.h"
#include "../element/element.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"

#define JAIL_EXPLOSION_WIDTH 384
#define JAIL_EXPLOSION_HEIGHT 384

void Jail_Initialize(Projectile *proj);
void Jail_Interaction_Character(Elements *self, Elements *tar);
void Jail_Interaction_Ground(Elements *self, Elements *tar);

#endif