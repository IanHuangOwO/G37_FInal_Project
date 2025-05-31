#include "crown.h"
#include "crown_explosion.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define CROWN_IMG_PATH "assets/projectiles/crown.gif"
#define CROWN_DURABILITY 1
#define CROWN_ACTION_COOLDOWN 30
#define CROWN_BOUNCE_DECAY 0
#define CROWN_COLLISION false
#define CROWN_GRAVITY true

void Crown_Initialize(Projectile *proj) 
{
    proj->gif               = algif_new_gif(CROWN_IMG_PATH, -1);
    proj->width             = proj->gif->width;
    proj->height            = proj->gif->height;
    proj->durability        = CROWN_DURABILITY;
    proj->action_cooldown   = 0;
    proj->bounce_decay      = CROWN_BOUNCE_DECAY;
    proj->collision         = CROWN_COLLISION;
    proj->gravity           = CROWN_GRAVITY;
    proj->hitbox            = New_Circle(proj->x + proj->width / 2,
                                        proj->y + proj->height / 2,
                                        min(proj->width, proj->height) / 2 - 16);
}
void Crown_Interaction_Character(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - CROWN_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - CROWN_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, CROWN_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    al_play_sample_instance(proj->sounds[SOUND_BOMB]);

    proj->durability --;
    proj->action_cooldown = CROWN_ACTION_COOLDOWN;
    return;
}
void Crown_Interaction_Ground(Elements *self, Elements *tar) {
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - CROWN_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - CROWN_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, CROWN_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    al_play_sample_instance(proj->sounds[SOUND_BOMB]);

    proj->durability --;
    proj->action_cooldown = CROWN_ACTION_COOLDOWN;
    return;
}