#include "ice_wall.h"
#include "../element/character.h"
#include "../shapes/Rectangle.h"

#define ICE_WALL_PATH "assets/projectiles/ice_wall.gif"

void IceWall_Initialize(Projectile *proj)
{
    proj->gif = algif_new_gif(ICE_WALL_PATH, -1);
    proj->width = ICE_WALL_WIDTH;
    proj->height = ICE_WALL_HEIGHT;
    proj->durability = 1;
    proj->gravity = false;
    proj->bounce_decay = 0;
    proj->collision = true;
    proj->is_in_air = false;
    proj->anime_time = 5 * FPS;
    proj->duration = 5 * FPS;
    proj->hitbox = New_Rectangle(proj->x, proj->y, proj->width, proj->height);
}

void IceWall_Interaction_Character(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)self->pDerivedObj;
    Character *chara = (Character *)tar->pDerivedObj;

    if (!proj->hitbox->overlap(proj->hitbox, chara->hitbox))
        return;

    int dx = chara->vx > 0 ? -1 : 1;
    chara->x += dx * 10;
    chara->hitbox->update_center_x(chara->hitbox, dx * 10);

    chara->vx = 0;
}