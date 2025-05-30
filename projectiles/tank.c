#include "tank.h"
#include "tank_explosion.h"

#define TANK_IMG_PATH "assets/projectiles/tank.gif"
#define TANK_DURABILITY 1
#define TANK_ACTION_COOLDOWN 30
#define TANK_BOUNCE_DECAY 0
#define TANK_COLLISION false
#define TANK_GRAVITY true

void Tank_Initialize(Projectile *proj) 
{
    proj->gif               = algif_new_gif(TANK_IMG_PATH, -1);
    proj->width             = proj->gif->width;
    proj->height            = proj->gif->height;
    proj->durability        = TANK_DURABILITY;
    proj->action_cooldown   = 0;
    proj->bounce_decay      = TANK_BOUNCE_DECAY;
    proj->collision         = TANK_COLLISION;
    proj->gravity           = TANK_GRAVITY;
    proj->hitbox            = New_Circle(proj->x + proj->width / 2,
                                        proj->y + proj->height / 2,
                                        min(proj->width, proj->height) / 2 - 16);
}
void Tank_Interaction_Character(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - TANK_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - TANK_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, TANK_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    proj->durability --;
    proj->action_cooldown = TANK_ACTION_COOLDOWN;
    return;
}
void Tank_Interaction_Ground(Elements *self, Elements *tar) {
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - TANK_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - TANK_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, TANK_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    proj->durability --;
    proj->action_cooldown = TANK_ACTION_COOLDOWN;
    return;
}