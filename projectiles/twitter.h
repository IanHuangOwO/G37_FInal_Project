#ifndef TWITTER_H_INCLUDED
#define TWITTER_H_INCLUDED

#include "../element/projectile.h"
#include "../element/element.h"
#include "../scene/sceneManager.h"
#include "twitter_explosion.h"

#define TWITTER_WIDTH 22
#define TWITTER_HEIGHT 22

void Twitter_Initialize(Projectile *proj);
void Twitter_Interaction_Character(Elements *self, Elements *tar);
void Twitter_Interaction_Ground(Elements *self, Elements *tar);

#endif