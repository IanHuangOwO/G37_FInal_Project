#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>

/*
   [game scene object]
*/

#define ROUND_START_TIME 360
#define ATTACK_START_TIME 300

typedef enum EleType
{
    Ground_L,
    Player1_L,
    Player2_L,
    Projectile_L,
    Floor_L,
    Particle_L,
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
    int game_start_timer;
    int round_start_timer;
    int attack_start_timer;
    int round_who;
    bool state;
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE_INSTANCE *bgm;
    ALLEGRO_SAMPLE_INSTANCE *count;
    ALLEGRO_BITMAP *background;
} GameScene;
Scene *New_GameScene(int label, int player1_who, int player2_who, int backgorund_who);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);
void _game_round_engine(Scene *self);
void _draw_player_stats(Scene *self, int label, int x, int y, bool flip);
void _draw_attack_indicator(Scene *self, int label);

#endif
