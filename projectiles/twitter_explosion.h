#ifndef TWITTER_EXPLOSION_H_INCLUDED
#define TWITTER_EXPLOSION_H_INCLUDED

#include "../element/projectile.h"
#include "../element/character.h"
#include "../element/element.h"
#include "../scene/sceneManager.h"

#define TWITTER_EXPLOSION_WIDTH 64
#define TWITTER_EXPLOSION_HEIGHT 64

void Twitter_Explosion_Initialize(Projectile *proj);
void Twitter_Explosion_Interaction_Character(Elements *self, Elements *tar);
void Twitter_Explosion_Interaction_Ground(Elements *self, Elements *tar);

#endif