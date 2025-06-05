#ifndef CHARATER_H_INCLUDED
#define CHARATER_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../physics/contact.h"
#include "../algif5/algif.h"
#include <stdbool.h>
/*
   [character object]
*/

#define ATTACK_POWER_MAX 20
#define ATTACK_POWER_MIN 0.1
#define ATTACK_POWER_CHARGE_SPEED 0.1

#define ATTACK_ANGLE_MAX  90
#define ATTACK_ANGLE_MIN -90
#define ATTACK_ANGLE_CHARGE_SPEED 0.2

#define HP_MAX      300
#define EXP_MAX     10000
#define FURRY_MAX   150
#define MOVE_SPEED     5

typedef enum CharacterStatus
{
    IDLE    = 0,
    MOVE    = 1,
    ATK     = 2,
    HURT    = 3,
} CharacterStatus;

typedef enum {
    SOUND_ATTACK_0 = 0,
    SOUND_ATTACK_1 = 1,
    SOUND_ATTACK_2 = 2,
    SOUND_ATTACK_3 = 3,
    SOUND_ATTACK_CHARGING = 4,
    SOUND_HURT = 5,
    SOUND_DEATH = 6,
} SoundIndex;

typedef struct _Character
{
    int x, y;
    float vx, vy;
    float bounce_decay;
    int width, height;                  // the width and height of image
    bool dir;                           // true: face to right, false: face to left
    bool is_in_air;                     // true: character is airborn
    int who;                            // The character type
    int player;
    int player_now;
    int state;                          // the state of character
    int anime;                          // counting the time of animation
    int anime_time;                     // indicate how long the animation
    ALGIF_ANIMATION *gif_status[4];     // gif for each state. 0: stop, 1: move, 2:attack 3:hurt
    ALLEGRO_SAMPLE_INSTANCE *sounds[7]; 
    float atk_power;
    bool attack_ok;
    bool was_charging;
    bool charging;
    float atk_angle;
    int atk_level;
    int atk_furry;
    int hurt_cooldown;
    int hp;
    bool new_proj;
    bool ultimate;
    ContactInfo contact; 
    Shape *hitbox;                      // the hitbox of object
} Character;

Elements *New_Character(int who, int label);

void Character_update(Elements *self);
void Character_interact(Elements *self);
void Character_draw(Elements *self);
void Character_destory(Elements *self);

void Character_Attack(Elements *self);
void Character_Hurt(Elements *self, int damage);
void Character_Furry(Elements *self, int amount);
void Character_Level(Elements *self, int amount);

void _Character_update_position(Elements *self, int dx, int dy);

#endif