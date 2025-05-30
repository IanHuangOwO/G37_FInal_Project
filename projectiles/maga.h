#ifndef MAGA_H_INCLUDED
#define MAGA_H_INCLUDED

#include "../element/projectile.h"
#include "../element/element.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"

#define MAGA_WIDTH 64
#define MAGA_HEIGHT 64

void Maga_Initialize(Projectile *proj);
void Maga_Interaction_Character(Elements *self, Elements *tar);
void Maga_Interaction_Ground(Elements *self, Elements *tar);

#endif