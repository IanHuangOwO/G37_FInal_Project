#include "twitter.h"

#define TWITTER_IMG_PATH "assets/projectiles/golf.gif"
#define TWITTER_DURABILITY 1
#define TWITTER_ACTION_COOLDOWN 5
#define TWITTER_BOUNCE_DECAY 0
#define TWITTER_COLLISION true
#define TWITTER_GRAVITY true

void Twitter_Initialize(Projectile *proj) 
{
    proj->gif = algif_new_gif(TWITTER_IMG_PATH, -1);
    proj->durability        = TWITTER_DURABILITY;
    proj->action_cooldown   = 0;
    proj->bounce_decay      = TWITTER_BOUNCE_DECAY;
    proj->collision         = TWITTER_COLLISION;
    proj->gravity           = TWITTER_GRAVITY;
}
void Twitter_Interaction_Character(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - TWITTER_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - TWITTER_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, TWITTER_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    proj->durability --;
    proj->action_cooldown = TWITTER_ACTION_COOLDOWN + 25;
    return;
}
void Twitter_Interaction_Ground(Elements *self, Elements *tar) {
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - TWITTER_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - TWITTER_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, TWITTER_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    proj->durability --;
    proj->action_cooldown = TWITTER_ACTION_COOLDOWN;
    return;
}
