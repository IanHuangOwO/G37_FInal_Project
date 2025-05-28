#include "golf.h"

#define GOLF_IMG_PATH "assets/projectiles/golf.gif"
#define GOLF_DURABILITY 1
#define GOLF_ACTION_COOLDOWN 5
#define GOLF_BOUNCE_DECAY 0
#define GOLF_COLLISION false
#define GOLF_GRAVITY true

void Golf_Initialize(Projectile *proj) 
{
    proj->gif = algif_new_gif(GOLF_IMG_PATH, -1);
    proj->durability        = GOLF_DURABILITY;
    proj->action_cooldown   = 0;
    proj->bounce_decay      = GOLF_BOUNCE_DECAY;
    proj->collision         = GOLF_COLLISION;
    proj->gravity           = GOLF_GRAVITY;
}
void Golf_Interaction_Character(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - GOLF_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - GOLF_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, GOLF_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    proj->durability --;
    proj->action_cooldown = GOLF_ACTION_COOLDOWN + 25;
    return;
}
void Golf_Interaction_Ground(Elements *self, Elements *tar) {
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - GOLF_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - GOLF_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, GOLF_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    proj->durability --;
    proj->action_cooldown = GOLF_ACTION_COOLDOWN;
    return;
}
