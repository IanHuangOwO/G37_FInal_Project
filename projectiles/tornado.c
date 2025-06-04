#include "tornado.h"
#include "tornado_explosion.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "../algif5/algif.h"

#define TORNADO_IMG_PATH "assets/projectiles/TORNADO.gif"
#define TORNADO_DURABILITY 1
#define TORNADO_ACTION_COOLDOWN 30
#define TORNADO_BOUNCE_DECAY 0
#define TORNADO_COLLISION false
#define TORNADO_GRAVITY true

void Tornado_Initialize(Projectile *proj) 
{
    proj->gif               = algif_new_gif(TORNADO_IMG_PATH, -1);
    proj->width             = proj->gif->width;
    proj->height            = proj->gif->height;
    proj->durability        = TORNADO_DURABILITY;
    proj->action_cooldown   = 0;
    proj->bounce_decay      = TORNADO_BOUNCE_DECAY;
    proj->collision         = TORNADO_COLLISION;
    proj->gravity           = TORNADO_GRAVITY;
    proj->hitbox            = New_Circle(proj->x + proj->width / 2,
                                        proj->y + proj->height / 2,
                                        min(proj->width, proj->height) / 2 - 16);
    proj->update            = Tornado_Update;

}
void Tornado_Interaction_Character(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - TORNADO_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - TORNADO_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, TORNADO_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    al_play_sample_instance(proj->sounds[SOUND_BOMB]);

    proj->durability --;
    proj->action_cooldown = TORNADO_ACTION_COOLDOWN;
    return;
}
void Tornado_Interaction_Ground(Elements *self, Elements *tar) {
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - TORNADO_EXPLOSION_WIDTH / 2;
    int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - TORNADO_EXPLOSION_HEIGHT / 2;

    Elements *explode = New_Projectile(Projectile_L, center_x, center_y, 0, 0, TORNADO_EXPLOSION, proj->player);
    _Register_elements(scene, explode);

    al_play_sample_instance(proj->sounds[SOUND_BOMB]);

    proj->durability --;
    proj->action_cooldown = TORNADO_ACTION_COOLDOWN;
    return;
}

void Tornado_Update(Elements *self)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);

    // update gif
    if (proj->gif && !proj->gif->done) {
        algif_update_gif(proj->gif, al_get_time());
    }

    // move
    proj->x += proj->vx;
    proj->y += proj->vy;

    // update hitbox position
    if (proj->hitbox) {
        proj->hitbox->move_to(proj->hitbox, 
                              proj->x + proj->width / 2, 
                              proj->y + proj->height / 2);
    }

    // destroy terrain on the moving path
    Tornado_Destroy_Ground_At_Hitbox(proj->hitbox, proj->player);

    // update blood
    if (proj->action_cooldown > 0) {
        proj->action_cooldown--;
    }

    proj->durability--;
    
}
