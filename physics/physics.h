// physics.h

#ifndef PHYSICS_H
#define PHYSICS_H

// Include the full definition of Elements so we can access its members
#include "../element/element.h"

void Contact_Check_To_Character(Elements *self);
void Movement_Physics_To_Character(Elements *self);

void Contact_Check_To_Projectile(Elements *self, bool collision);
void Movement_Physics_To_Projectile(Elements *self, bool collision, bool gravity);

#endif // PHYSICS_H