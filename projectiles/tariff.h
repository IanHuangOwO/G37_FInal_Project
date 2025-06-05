#ifndef TARIFF_H_INCLUDED
#define TARIFF_H_INCLUDED

#include "../element/projectile.h"
#include "../element/element.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"

#define TARIFF_WIDTH 225
#define TARIFF_HEIGHT 225

void Tariff_Initialize(Projectile *proj);
void Tariff_Interaction_Character(Elements *self, Elements *tar);
void Tariff_Interaction_Ground(Elements *self, Elements *tar);

#endif