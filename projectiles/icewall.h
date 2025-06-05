#ifndef ICEWALL_H_INCLUDED
#define ICEWALL_H_INCLUDED

#include "../element/projectile.h"
#include "../element/element.h"
#include "../shapes/Rectangle.h"
#include "../scene/sceneManager.h"

#define ICEWALL_WIDTH 64
#define ICEWALL_HEIGHT 64
#define ICEWALL_DURATION 300 // Approx 5 seconds at 60 FPS

void IceWall_Initialize(Projectile *proj);
void IceWall_Interaction_Character(Elements *self, Elements *tar);
void IceWall_Interaction_Ground(Elements *self, Elements *tar);

#endif