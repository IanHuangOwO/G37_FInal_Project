#include "jail.h"

#define JAIL_IMG_PATH "assets/projectiles/jail.gif"
#define JAIL_DURABILITY 100000
#define JAIL_ACTION_COOLDOWN 0
#define JAIL_DAMAGE 100
#define JAIL_BOUNCE_DECAY 0
#define JAIL_COLLISION false
#define JAIL_GRAVITY true

void Jail_Initialize(Projectile *proj) 
{
    proj->gif               = algif_new_gif(JAIL_IMG_PATH, -1);
    proj->width             = proj->gif->width;
    proj->height            = proj->gif->height;
    proj->durability        = JAIL_DURABILITY;
    proj->action_cooldown   = 0;
    proj->bounce_decay      = JAIL_BOUNCE_DECAY;
    proj->collision         = JAIL_COLLISION;
    proj->gravity           = JAIL_GRAVITY;
    proj->hitbox            = New_Circle(proj->x + proj->width / 2,
                                         proj->y + proj->height / 2,
                                         min(proj->width, proj->height) / 2);
}
void Jail_Interaction_Character(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)self->pDerivedObj;

    proj->gif->display_index = 0;
    proj->gif->done = false;

    Character_Hurt(tar, JAIL_DAMAGE);

    proj->durability = 0;
    proj->action_cooldown = JAIL_ACTION_COOLDOWN + 30;
}
void Jail_Interaction_Ground(Elements *self, Elements *tar) 
{
    Projectile *proj = (Projectile *)self->pDerivedObj;
    Ground *ground = (Ground *)tar->pDerivedObj;

    proj->gif->display_index = 0;
    proj->gif->done = false;

    // Convert to tile indices
    int left   = (int)(proj->hitbox->get_left(proj->hitbox)) / TILE_WIDTH;
    int right  = (int)(proj->hitbox->get_right(proj->hitbox)) / TILE_WIDTH;
    int top    = (int)(proj->hitbox->get_top(proj->hitbox)) / TILE_HEIGHT;
    int bottom = (int)(proj->hitbox->get_bottom(proj->hitbox)) / TILE_HEIGHT;

    // Clamp to map bounds
    if (left < 0) left = 0;
    if (right >= MAP_COLS) right = MAP_COLS - 1;
    if (top < 0) top = 0;
    if (bottom >= MAP_ROWS) bottom = MAP_ROWS - 1;

    int deactivated_count = 0;

    for (int i = top; i <= bottom; i++) {
        for (int j = left; j <= right; j++) {
            if (!ground->active[i][j]) continue;
            if (ground->hitboxes[i][j]->overlap(ground->hitboxes[i][j], proj->hitbox)) {
                Ground_Erase_Tile(ground, i, j);
                deactivated_count++;
            }
        }
    }

    // Level up the player's character
    int target_label = (proj->player == 1) ? Player1_L : Player2_L;
    ElementVec players = _Get_label_elements(scene, target_label);

    for (int i = 0; i < players.len; i++) {
        Character_Level(players.arr[i], deactivated_count);  // Level up by the number of deactivated tiles
    }

    proj->durability -= deactivated_count;
    proj->action_cooldown = JAIL_ACTION_COOLDOWN;
}