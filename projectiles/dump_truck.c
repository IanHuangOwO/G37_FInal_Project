#include "dump_truck.h"
#include "dump_truck_explosion.h"

#define DUMP_TRUCK_IMG_PATH "assets/projectiles/dump_truck.gif"
#define DUMP_TRUCK_DURABILITY 1
#define DUMP_TRUCK_ACTION_COOLDOWN 30
#define DUMP_TRUCK_BOUNCE_DECAY 0
#define DUMP_TRUCK_COLLISION false
#define DUMP_TRUCK_GRAVITY true

void Dump_Truck_Initialize(Projectile *proj) 
{
    proj->gif               = algif_new_gif(DUMP_TRUCK_IMG_PATH, -1);
    proj->width             = proj->gif->width;
    proj->height            = proj->gif->height;
    proj->durability        = DUMP_TRUCK_DURABILITY;
    proj->action_cooldown   = 0;
    proj->bounce_decay      = DUMP_TRUCK_BOUNCE_DECAY;
    proj->collision         = DUMP_TRUCK_COLLISION;
    proj->gravity           = DUMP_TRUCK_GRAVITY;
    proj->hitbox            = New_Circle(proj->x + proj->width / 2,
                                        proj->y + proj->height / 2,
                                        min(proj->width, proj->height) / 2 - 16);
}
void Dump_Truck_Interaction_Character(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - DUMP_TRUCK_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - DUMP_TRUCK_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, DUMP_TRUCK_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    proj->durability --;
    proj->action_cooldown = DUMP_TRUCK_ACTION_COOLDOWN;
    return;
}
void Dump_Truck_Interaction_Ground(Elements *self, Elements *tar) {
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - DUMP_TRUCK_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - DUMP_TRUCK_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, DUMP_TRUCK_EXPLOSION, proj->player);
    _Register_elements(scene, explode);
    Elements *poop_0 = New_Projectile(Projectile_L, center_x, center_y,   0, 8, POOP, proj->player);
    Elements *poop_1 = New_Projectile(Projectile_L, center_x, center_y,  45, 6, POOP, proj->player);
    Elements *poop_2 = New_Projectile(Projectile_L, center_x, center_y,  90, 8, POOP, proj->player);
    Elements *poop_3 = New_Projectile(Projectile_L, center_x, center_y, 135, 6, POOP, proj->player);
    Elements *poop_4 = New_Projectile(Projectile_L, center_x, center_y, 180, 8, POOP, proj->player);
    Elements *poop_5 = New_Projectile(Projectile_L, center_x, center_y, 225, 6, POOP, proj->player);
    Elements *poop_6 = New_Projectile(Projectile_L, center_x, center_y, 270, 8, POOP, proj->player);
    Elements *poop_7 = New_Projectile(Projectile_L, center_x, center_y, 315, 6, POOP, proj->player);
    _Register_elements(scene, poop_0);
    _Register_elements(scene, poop_1);
    _Register_elements(scene, poop_2);
    _Register_elements(scene, poop_3);
    _Register_elements(scene, poop_4);
    _Register_elements(scene, poop_5);
    _Register_elements(scene, poop_6);
    _Register_elements(scene, poop_7);

    proj->durability --;
    proj->action_cooldown = DUMP_TRUCK_ACTION_COOLDOWN;
    return;
}