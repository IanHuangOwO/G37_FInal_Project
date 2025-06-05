#include "icewall.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define ICEWALL_IMG_PATH "assets/projectiles/ice_wall.gif"
#define ICEWALL_BOUNCE_DECAY 0
#define ICEWALL_COLLISION true
#define ICEWALL_GRAVITY false

void IceWall_Initialize(Projectile *proj)
{
    proj->gif               = algif_new_gif(ICEWALL_IMG_PATH, -1);
    proj->width             = ICEWALL_WIDTH;
    proj->height            = ICEWALL_HEIGHT;
    proj->durability        = 1; // one-time wall
    proj->duration          = ICEWALL_DURATION;
    proj->bounce_decay      = ICEWALL_BOUNCE_DECAY;
    proj->collision         = ICEWALL_COLLISION;
    proj->gravity           = ICEWALL_GRAVITY;
    proj->hitbox            = New_Rectangle(
                                proj->x,
                                proj->y,
                                proj->x + ICEWALL_WIDTH,
                                proj->y + ICEWALL_HEIGHT);
}

void IceWall_Interaction_Character(Elements *self, Elements *tar)
{
    // Do nothing — wall blocks but doesn't explode
    (void)self;
    (void)tar;
}

void IceWall_Interaction_Ground(Elements *self, Elements *tar)
{
    // Do nothing — ice wall remains in place
    (void)self;
    (void)tar;
}