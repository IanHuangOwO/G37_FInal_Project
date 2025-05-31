#include "winnie.h"
#include "winnie_explosion.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define WINNIE_IMG_PATH "assets/projectiles/winnie.gif"
#define WINNIE_DURABILITY 5
#define WINNIE_ACTION_COOLDOWN 30
#define WINNIE_BOUNCE_DECAY 0.7
#define WINNIE_COLLISION true
#define WINNIE_GRAVITY true

void Winnie_Initialize(Projectile *proj) 
{
    proj->gif               = algif_new_gif(WINNIE_IMG_PATH, -1);
    proj->width             = proj->gif->width;
    proj->height            = proj->gif->height;
    proj->durability        = WINNIE_DURABILITY;
    proj->action_cooldown   = 0;
    proj->bounce_decay      = WINNIE_BOUNCE_DECAY;
    proj->collision         = WINNIE_COLLISION;
    proj->gravity           = WINNIE_GRAVITY;
    proj->hitbox            = New_Circle(proj->x + proj->width / 2,
                                        proj->y + proj->height / 2,
                                        min(proj->width, proj->height) / 2 - 16);
}
void Winnie_Interaction_Character(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    Character *chara = (Character *)tar->pDerivedObj;
    
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - WINNIE_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - WINNIE_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, WINNIE_EXPLOSION, proj->player);
    _Register_elements(scene, explode);
    al_play_sample_instance(proj->sounds[SOUND_BOMB]);
    
    chara->vy = -proj->vy * 0.8;
    _Character_update_position(tar, 1, 1);

    proj->durability --;
    proj->action_cooldown = WINNIE_ACTION_COOLDOWN;
    return;
}
void Winnie_Interaction_Ground(Elements *self, Elements *tar) {
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - WINNIE_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - WINNIE_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, WINNIE_EXPLOSION, proj->player);
    _Register_elements(scene, explode);
    al_play_sample_instance(proj->sounds[SOUND_BOMB]);

    proj->durability --;
    proj->action_cooldown = WINNIE_ACTION_COOLDOWN;
    return;
}