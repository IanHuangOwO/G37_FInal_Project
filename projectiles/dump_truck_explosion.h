#ifndef DUMP_TRUCK_EXPLOSION_H_INCLUDED
#define DUMP_TRUCK_EXPLOSION_H_INCLUDED

#include "../element/projectile.h"
#include "../element/character.h"
#include "../element/element.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"

#define DUMP_TRUCK_EXPLOSION_WIDTH 64
#define DUMP_TRUCK_EXPLOSION_HEIGHT 64

void Dump_Truck_Explosion_Initialize(Projectile *proj);
void Dump_Truck_Explosion_Interaction_Character(Elements *self, Elements *tar);
void Dump_Truck_Explosion_Interaction_Ground(Elements *self, Elements *tar);

#endif