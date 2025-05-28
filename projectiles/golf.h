#ifndef GOLF_H_INCLUDED
#define GOLF_H_INCLUDED

#include "../element/projectile.h"
#include "../element/element.h"
#include "../scene/sceneManager.h"
#include "golf_explosion.h"

#define GOLF_WIDTH 22
#define GOLF_HEIGHT 22

void Golf_Initialize(Projectile *proj);
void Golf_Interaction_Character(Elements *self, Elements *tar);
void Golf_Interaction_Ground(Elements *self, Elements *tar);

#endif