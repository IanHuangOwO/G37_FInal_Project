#ifndef Projectile_H_INCLUDED
#define Projectile_H_INCLUDED
#include "element.h"
#include "../physics/contact.h"
#include "../shapes/Shape.h"
#include "../algif5/algif.h"
/*
   [Projectile object]
*/

typedef enum ProjectileWho
{
    GOLF = 0,
    GOLF_EXPLOSION,
    TWITTER,
    TWITTER_EXPLOSION,
    GREAT_WALL,
    CROWN,
    WINNIE,
    TANK,
    JAIL,
    BABY,
    TORNADO,
    ICE_WALL,
    AXE,
    
} ProjectileWho;

typedef struct _Projectile
{
    // Identity of the projectile
    int who;
    int player;
    int width, height;
    
    // Motion of the projectile
    int x, y;
    float vx, vy;
    bool is_in_air; 
    float bounce_decay;
    bool collision;
    bool gravity;
    Shape *hitbox;
    ContactInfo contact; 

    // Interaction of the projectile
    int durability;
    int action_cooldown;
    int anime;
    int anime_time;
    ALGIF_ANIMATION *gif;
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
