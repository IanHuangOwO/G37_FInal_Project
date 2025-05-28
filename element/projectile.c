#include "projectile.h"
#include "ground.h"
#include "character.h"
#include "../shapes/Circle.h"
#include "../physics/physics.h"
#include "../scene/gamescene.h" // for element label
#include "../scene/sceneManager.h" // for scene variable
#include "../projectiles/golf.h"
#include "../projectiles/golf_explosion.h"
#include "../projectiles/twitter.h"
#include "../projectiles/twitter_explosion.h"
#include <math.h>
/*
   [Projectile function]
*/

Elements *New_Projectile(int label, int x, int y, float angle_deg, float power, int who, int player)
{
    Projectile *pDerivedObj = (Projectile *)malloc(sizeof(Projectile));
    Elements *pObj = New_Elements(label);

    // Calculate vx and vy from angle and power
    float angle_rad = angle_deg * (3.14159f / 180.0f);
    float vx = cosf(angle_rad) * power;
    float vy = sinf(angle_rad) * power;

    if (who == GOLF)                    Golf_Initialize(pDerivedObj);
    else if (who == GOLF_EXPLOSION)     Golf_Explosion_Initialize(pDerivedObj);
    else if (who == TWITTER)            Twitter_Initialize(pDerivedObj);
    else if (who == TWITTER_EXPLOSION)  Twitter_Explosion_Initialize(pDerivedObj);
    
    pDerivedObj->who = who;
    pDerivedObj->player = player;
    pDerivedObj->width = pDerivedObj->gif->width;
    pDerivedObj->height = pDerivedObj->gif->height;
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->vx = vx;
    pDerivedObj->vy = vy;
    pDerivedObj->is_in_air = true;

    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);

    // Setup projectile behavior
    pObj->inter_obj[pObj->inter_len++] = Ground_L;
    pObj->inter_obj[pObj->inter_len++] = Player1_L;
    pObj->inter_obj[pObj->inter_len++] = Player2_L;
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Projectile_update;
    pObj->Interact = Projectile_interact;
    pObj->Draw = Projectile_draw;
    pObj->Destroy = Projectile_destory;

    return pObj;
}
void Projectile_update(Elements *self)
{
    Projectile *proj = ((Projectile *)(self->pDerivedObj));

    Contact_Check_To_Projectile(self, proj->collision);
    if (proj->durability <= 0) {
        if (proj->who == GOLF_EXPLOSION && !proj->gif->done) return; 
        if (proj->who == TWITTER_EXPLOSION && !proj->gif->done) return; 
        self->dele = true;
        return;  // Don't update physics during explosion
    }
    if (proj->action_cooldown > 0) proj->action_cooldown --;

    Movement_Physics_To_Projectile(self, proj->collision, proj->gravity);
}
void _Projectile_update_position(Elements *self, int dx, int dy)
{
    Projectile *proj = ((Projectile *)(self->pDerivedObj));
    proj->x += dx;
    proj->y += dy;
    Shape *hitbox = proj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void Projectile_interact(Elements *self)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);

    if (proj->durability <= 0 || proj->action_cooldown > 0) return;

    for (int j = 0; j < self->inter_len; j++) {
        int inter_label = self->inter_obj[j];
        ElementVec labelEle = _Get_label_elements(scene, inter_label);

        for (int i = 0; i < labelEle.len; i++) {
            Elements *target = labelEle.arr[i];

            if ((proj->player == 1 && inter_label == Player2_L) ||
                (proj->player == 2 && inter_label == Player1_L)) {
                _Projectile_interact_Character(self, target);
            }

            if (inter_label == Ground_L) {
                _Projectile_interact_Ground(self, target);
            }
        }
    }
    
}
void Projectile_draw(Elements *self)
{
    Projectile *Obj = ((Projectile *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(Obj->gif, al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, Obj->x, Obj->y, 0);
    }
}
void Projectile_destory(Elements *self)
{
    Projectile *proj = ((Projectile *)(self->pDerivedObj));
    algif_destroy_animation(proj->gif);
    free(proj->hitbox);
    free(proj);
    free(self);
}
void _Projectile_interact_Character(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    Character *chara = (Character *)(tar->pDerivedObj);

    if (!proj->hitbox->overlap(proj->hitbox, chara->hitbox)) return;

    if (proj->who == GOLF) Golf_Interaction_Character(self, tar);
    else if (proj->who == GOLF_EXPLOSION) Golf_Explosion_Interaction_Character(self, tar);
    else if (proj->who == TWITTER) Twitter_Interaction_Character(self, tar);
    else if (proj->who == TWITTER_EXPLOSION) Twitter_Explosion_Interaction_Character(self, tar);
}
void _Projectile_interact_Ground(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    Ground *ground = (Ground *)tar->pDerivedObj;

    // Convert to tile indices
    int left   = (int)(proj->hitbox->get_left(proj->hitbox)) / TILE_WIDTH - 20;
    int right  = (int)(proj->hitbox->get_right(proj->hitbox)) / TILE_WIDTH + 20;
    int top    = (int)(proj->hitbox->get_top(proj->hitbox)) / TILE_HEIGHT - 20;
    int bottom = (int)(proj->hitbox->get_bottom(proj->hitbox)) / TILE_HEIGHT + 20;

    // Clamp to map bounds
    if (left < 0) left = 0;
    if (right >= MAP_COLS) right = MAP_COLS - 1;
    if (top < 0) top = 0;
    if (bottom >= MAP_ROWS) bottom = MAP_ROWS - 1;

    for (int i = top; i <= bottom; i++) {
        for (int j = left; j <= right; j++) {
            if (!ground->active[i][j]) continue;
            if (ground->hitboxes[i][j]->overlap(ground->hitboxes[i][j], proj->hitbox)) {
                goto collision;
            }
        }
    }
    return;
    collision: {
        if (proj->who == GOLF) Golf_Interaction_Ground(self, tar);
        else if (proj->who == GOLF_EXPLOSION) Golf_Explosion_Interaction_Ground(self, tar);
        else if (proj->who == TWITTER) Twitter_Interaction_Ground(self, tar);
        else if (proj->who == TWITTER_EXPLOSION) Twitter_Explosion_Interaction_Ground(self, tar);
    }
}
