#ifndef DUMP_TRUCK_H_INCLUDED
#define DUMP_TRUCK_H_INCLUDED

#include "../element/projectile.h"
#include "../element/element.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"

#define DUMP_TRUCK_WIDTH 32
#define DUMP_TRUCK_HEIGHT 32

void Dump_Truck_Initialize(Projectile *proj);
void Dump_Truck_Interaction_Character(Elements *self, Elements *tar);
void Dump_Truck_Interaction_Ground(Elements *self, Elements *tar);

#endif