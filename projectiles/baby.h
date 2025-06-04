#ifndef BABY_H_INCLUDED
#define BABY_H_INCLUDED

#include "../element/projectile.h"
#include "../element/element.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"

#define BABY_WIDTH 64
#define BABY_HEIGHT 64

void Baby_Initialize(Projectile *proj);
void Baby_Interaction_Character(Elements *self, Elements *tar);
void Baby_Interaction_Ground(Elements *self, Elements *tar);

#endif