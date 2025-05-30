#include "maga.h"
#include "maga_explosion.h"

#define MAGA_IMG_PATH "assets/projectiles/maga.gif"
#define MAGA_DURABILITY 1
#define MAGA_ACTION_COOLDOWN 30
#define MAGA_BOUNCE_DECAY 0
#define MAGA_COLLISION false
#define MAGA_GRAVITY true

void Maga_Initialize(Projectile *proj) 
{
    proj->gif               = algif_new_gif(MAGA_IMG_PATH, -1);
    proj->width             = proj->gif->width;
    proj->height            = proj->gif->height;
    proj->durability        = MAGA_DURABILITY;
    proj->action_cooldown   = 0;
    proj->bounce_decay      = MAGA_BOUNCE_DECAY;
    proj->collision         = MAGA_COLLISION;
    proj->gravity           = MAGA_GRAVITY;
    proj->hitbox            = New_Circle(proj->x + proj->width / 2,
                                        proj->y + proj->height / 2,
                                        min(proj->width, proj->height) / 2 - 16);
}
void Maga_Interaction_Character(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - MAGA_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - MAGA_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, MAGA_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    proj->durability --;
    proj->action_cooldown = MAGA_ACTION_COOLDOWN;
    return;
}
void Maga_Interaction_Ground(Elements *self, Elements *tar) {
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - MAGA_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - MAGA_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, MAGA_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    proj->durability --;
    proj->action_cooldown = MAGA_ACTION_COOLDOWN;
    return;
}