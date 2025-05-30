#include "poop.h"
#include "poop_explosion.h"

#define POOP_IMG_PATH "assets/projectiles/poop.gif"
#define POOP_DURABILITY 3
#define POOP_ACTION_COOLDOWN 30
#define POOP_BOUNCE_DECAY 0.6
#define POOP_COLLISION true
#define POOP_GRAVITY true

void Poop_Initialize(Projectile *proj) 
{
    proj->gif               = algif_new_gif(POOP_IMG_PATH, -1);
    proj->width             = proj->gif->width;
    proj->height            = proj->gif->height;
    proj->durability        = POOP_DURABILITY;
    proj->action_cooldown   = 0;
    proj->bounce_decay      = POOP_BOUNCE_DECAY;
    proj->collision         = POOP_COLLISION;
    proj->gravity           = POOP_GRAVITY;
    proj->hitbox            = New_Circle(proj->x + proj->width / 2,
                                        proj->y + proj->height / 2,
                                        min(proj->width, proj->height) / 2);
}
void Poop_Interaction_Character(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - POOP_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - POOP_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, POOP_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    proj->durability --;
    proj->action_cooldown = POOP_ACTION_COOLDOWN;
    return;
}
void Poop_Interaction_Ground(Elements *self, Elements *tar) {
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - POOP_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - POOP_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, POOP_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    proj->durability --;
    proj->action_cooldown = POOP_ACTION_COOLDOWN;
    return;
}