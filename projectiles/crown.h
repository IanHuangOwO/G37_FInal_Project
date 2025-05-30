#ifndef CROWN_H_INCLUDED
#define CROWN_H_INCLUDED

#include "../element/projectile.h"
#include "../element/element.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"

#define CROWN_WIDTH 64
#define CROWN_HEIGHT 64

void Crown_Initialize(Projectile *proj);
void Crown_Interaction_Character(Elements *self, Elements *tar);
void Crown_Interaction_Ground(Elements *self, Elements *tar);

#endif