#ifndef Projectile_H_INCLUDED
#define Projectile_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include "element.h"
#include "../physics/contact.h"
#include "../shapes/Shape.h"
#include "../algif5/algif.h"
/*
   [Projectile object]
*/

typedef enum ProjectileWho
{
    MAGA = 0,
    MAGA_EXPLOSION,
    DUMP_TRUCK,
    DUMP_TRUCK_EXPLOSION,
    POOP,
    POOP_EXPLOSION,
    DEPORT,
    DEPORT_EXPLOSION,
    CROWN,
    CROWN_EXPLOSION,
    WINNIE,
    WINNIE_EXPLOSION,
    TANK,
    TANK_EXPLOSION,
    JAIL,
    BABY,
    BABY_EXPLOSION,
    TORNADO,
    TORNADO_EXPLOSION,
    ICEWALL,
    ICEWALL_EXPLOSION,
    AXE,
    TARIFF,
    TARIFF_EXPLOSION,
} ProjectileWho;

typedef enum {
    SOUND_BOMB = 0,
} ProjectileSoundIndex;

typedef struct _Projectile
{
    // Identity of the projectile
    int who;
    int player;
    int width, height;
    int label;    
    // Motion of the projectile
    int x, y;
    float vx, vy;
    bool is_in_air; 
    float bounce_decay;
    bool collision;
    bool gravity;
    Shape *hitbox;
    ContactInfo contact;
    void *update; 

    // Interaction of the projectile
    int durability;
    int action_cooldown;
    int special_action;
    int anime;
    int anime_time;
    int duration;
    ALGIF_ANIMATION *gif;
    ALLEGRO_SAMPLE_INSTANCE *sounds[1];
} Projectile;

Elements *New_Projectile(int label, int x, int y, float angle_deg, float power, int who, int player);
void Projectile_update(Elements *self);
void Projectile_interact(Elements *self);
void Projectile_draw(Elements *self);
void Projectile_destory(Elements *self);

void _Projectile_update_position(Elements *self, int dx, int dy);
void _Projectile_interact_Floor(Elements *self, Elements *tar);
void _Projectile_interact_Ground(Elements *self, Elements *tar);
void _Projectile_interact_Character(Elements *self, Elements *tar);

#endif
