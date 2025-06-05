#pragma once

#include "../element/character.h"
#include "../element/projectile.h"
#include "../scene/sceneManager.h"
#include "../algif5/algif.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>

#define MAX_GIF 4
#define MAX_SOUNDS 7

void JinPing_Load_Assets(Character *chara);
void JinPing_Attack(Elements *self);
void _JinPing_Attack_0(Elements *self);
void _JinPing_Attack_1(Elements *self);
void _JinPing_Attack_2(Elements *self);
void _JinPing_Attack_3(Elements *self);