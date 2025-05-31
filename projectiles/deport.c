#include "deport.h"
#include "deport_explosion.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define DEPORT_IMG_PATH "assets/projectiles/deport.gif"
#define DEPORT_DURABILITY 1
#define DEPORT_ACTION_COOLDOWN 30
#define DEPORT_BOUNCE_DECAY 0
#define DEPORT_COLLISION false
#define DEPORT_GRAVITY true

void Deport_Initialize(Projectile *proj) 
{
    proj->gif               = algif_new_gif(DEPORT_IMG_PATH, -1);
    proj->width             = proj->gif->width;
    proj->height            = proj->gif->height;
    proj->durability        = DEPORT_DURABILITY;
    proj->action_cooldown   = 0;
    proj->bounce_decay      = DEPORT_BOUNCE_DECAY;
    proj->collision         = DEPORT_COLLISION;
    proj->gravity           = DEPORT_GRAVITY;
    proj->hitbox            = New_Circle(proj->x + proj->width / 2,
                                        proj->y + proj->height / 2,
                                        min(proj->width, proj->height) / 2 - 16);
}
void Deport_Interaction_Character(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    Character *chara = (Character *)tar->pDerivedObj;
    
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - DEPORT_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - DEPORT_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, DEPORT_EXPLOSION, proj->player);
    _Register_elements(scene, explode);
    
    chara->vy = -proj->vy * 0.8;
    _Character_update_position(tar, 1, 1);

    al_play_sample_instance(proj->sounds[SOUND_BOMB]);

    proj->durability --;
    proj->action_cooldown = DEPORT_ACTION_COOLDOWN;
    return;
}
void Deport_Interaction_Ground(Elements *self, Elements *tar) {
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - DEPORT_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - DEPORT_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, DEPORT_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    al_play_sample_instance(proj->sounds[SOUND_BOMB]);

    proj->durability --;
    proj->action_cooldown = DEPORT_ACTION_COOLDOWN;
    return;
}