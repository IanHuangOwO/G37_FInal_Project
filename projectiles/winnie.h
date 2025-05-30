#ifndef WINNIE_H_INCLUDED
#define WINNIE_H_INCLUDED

#include "../element/projectile.h"
#include "../element/element.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"

#define WINNIE_WIDTH 64
#define WINNIE_HEIGHT 64

void Winnie_Initialize(Projectile *proj);
void Winnie_Interaction_Character(Elements *self, Elements *tar);
void Winnie_Interaction_Ground(Elements *self, Elements *tar);

#endif