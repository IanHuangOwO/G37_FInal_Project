#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_font.h>

/*
   [game scene object]
*/
typedef enum EleType
{
    Ground_L,
    Player1_L,
    Player2_L,
    Projectile_L,
    Floor_L,
} EleType;

typedef enum CharacterWho
{
    Trump   = 0,
    JinPing = 1,
    GuoDong = 2
} CharacterWho;

typedef enum GroundWho
{
    White_House         = 0,
    Tiananmen_Square    = 1
} GroundWho;

typedef struct _GameScene
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *background;

} GameScene;
Scene *New_GameScene(int label);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);
void draw_attack_indicator(Elements *p1, ALLEGRO_COLOR color);

#endif
