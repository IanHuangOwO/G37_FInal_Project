#include "tariff.h"
#include "tariff_explosion.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define TARIFF_IMG_PATH "assets/projectiles/tariff.gif"
#define TARIFF_DURABILITY 100
#define TARIFF_ACTION_COOLDOWN 15
#define TARIFF_BOUNCE_DECAY 0
#define TARIFF_COLLISION false
#define TARIFF_GRAVITY true

void Tariff_Initialize(Projectile *proj) 
{
    proj->gif               = algif_new_gif(TARIFF_IMG_PATH, -1);
    proj->width             = proj->gif->width;
    proj->height            = proj->gif->height;
    proj->durability        = TARIFF_DURABILITY;
    proj->action_cooldown   = 0;
    proj->bounce_decay      = TARIFF_BOUNCE_DECAY;
    proj->collision         = TARIFF_COLLISION;
    proj->gravity           = TARIFF_GRAVITY;
    proj->hitbox            = New_Circle(proj->x + proj->width / 2,
                                        proj->y + proj->height / 2,
                                        min(proj->width, proj->height) / 2 - 16);
}
void Tariff_Interaction_Character(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - TARIFF_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - TARIFF_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, TARIFF_EXPLOSION, proj->player);
    _Register_elements(scene, explode);
    al_play_sample_instance(proj->sounds[SOUND_BOMB]);

    proj->durability --;
    proj->action_cooldown = TARIFF_ACTION_COOLDOWN;
    return;
}
void Tariff_Interaction_Ground(Elements *self, Elements *tar) {
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - TARIFF_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - TARIFF_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, TARIFF_EXPLOSION, proj->player);
    _Register_elements(scene, explode);
    al_play_sample_instance(proj->sounds[SOUND_BOMB]);

    proj->durability --;
    proj->action_cooldown = TARIFF_ACTION_COOLDOWN;
    return;
}