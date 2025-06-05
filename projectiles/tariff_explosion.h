#ifndef TARIFF_EXPLOSION_H_INCLUDED
#define TARIFF_EXPLOSION_H_INCLUDED

#include "../element/projectile.h"
#include "../element/character.h"
#include "../element/element.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"

#define TARIFF_EXPLOSION_WIDTH 355
#define TARIFF_EXPLOSION_HEIGHT 365

void Tariff_Explosion_Initialize(Projectile *proj);
void Tariff_Explosion_Interaction_Character(Elements *self, Elements *tar);
void Tariff_Explosion_Interaction_Ground(Elements *self, Elements *tar);

#endif