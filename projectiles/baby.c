#include "baby.h"
#include "baby_explosion.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define BABY_IMG_PATH "assets/projectiles/BABY.gif"
#define BABY_DURABILITY 1
#define BABY_ACTION_COOLDOWN 30
#define BABY_BOUNCE_DECAY 0
#define BABY_COLLISION false
#define BABY_GRAVITY true

void Baby_Initialize(Projectile *proj) 
{
    proj->gif               = algif_new_gif(BABY_IMG_PATH, -1);
    proj->width             = proj->gif->width;
    proj->height            = proj->gif->height;
    proj->durability        = BABY_DURABILITY;
    proj->action_cooldown   = 0;
    proj->bounce_decay      = BABY_BOUNCE_DECAY;
    proj->collision         = BABY_COLLISION;
    proj->gravity           = BABY_GRAVITY;
    proj->hitbox            = New_Circle(proj->x + proj->width / 2,
                                        proj->y + proj->height / 2,
                                        min(proj->width, proj->height) / 2 - 16);
}
void Baby_Interaction_Character(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - BABY_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - BABY_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, BABY_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    al_play_sample_instance(proj->sounds[SOUND_BOMB]);

    proj->durability --;
    proj->action_cooldown = BABY_ACTION_COOLDOWN;
    return;
}
void Baby_Interaction_Ground(Elements *self, Elements *tar) {
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - BABY_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - BABY_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, BABY_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    al_play_sample_instance(proj->sounds[SOUND_BOMB]);

    proj->durability --;
    proj->action_cooldown = BABY_ACTION_COOLDOWN;
    return;
}