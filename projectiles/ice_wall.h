#ifndef ICE_WALL_H
#define ICE_WALL_H
#define ICE_WALL_WIDTH  64
#define ICE_WALL_HEIGHT 64


#include "../element/projectile.h"

void IceWall_Initialize(Projectile *proj);
void IceWall_Interaction_Character(Elements *self, Elements *tar);


#endif
