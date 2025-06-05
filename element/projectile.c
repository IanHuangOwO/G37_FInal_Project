#include "projectile.h"
#include "ground.h"
#include "character.h"
#include "../shapes/Circle.h"
#include "../physics/physics.h"
#include "../scene/gamescene.h" // for element label
#include "../scene/sceneManager.h" // for scene variable
#include "../projectiles/maga.h"
#include "../projectiles/maga_explosion.h"
#include "../projectiles/dump_truck.h"
#include "../projectiles/dump_truck_explosion.h"
#include "../projectiles/poop.h"
#include "../projectiles/poop_explosion.h"
#include "../projectiles/deport.h"
#include "../projectiles/deport_explosion.h"
#include "../projectiles/crown.h"
#include "../projectiles/crown_explosion.h"
#include "../projectiles/winnie.h"
#include "../projectiles/winnie_explosion.h"
#include "../projectiles/tank.h"
#include "../projectiles/tank_explosion.h"
#include "../projectiles/baby.h"
#include "../projectiles/baby_explosion.h"
#include "../projectiles/tornado.h"
#include "../projectiles/tornado_explosion.h"

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

    pDerivedObj->who = who;
    pDerivedObj->player = player;
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->vx = vx;
    pDerivedObj->vy = vy;
    pDerivedObj->is_in_air = true;
    pDerivedObj->special_action = 0;

    switch (who) {
        case MAGA:
            Maga_Initialize(pDerivedObj);
            break;
        case MAGA_EXPLOSION:
            Maga_Explosion_Initialize(pDerivedObj);
            break;
        case DUMP_TRUCK:
            Dump_Truck_Initialize(pDerivedObj);
            break;
        case DUMP_TRUCK_EXPLOSION:
            Dump_Truck_Explosion_Initialize(pDerivedObj);
            break;
        case POOP:
            Poop_Initialize(pDerivedObj);
            break;
        case POOP_EXPLOSION:
            Poop_Explosion_Initialize(pDerivedObj);
            break;
        case DEPORT:
            Deport_Initialize(pDerivedObj);
            break;
        case DEPORT_EXPLOSION:
            Deport_Explosion_Initialize(pDerivedObj);
            break;
        case CROWN:
            Crown_Initialize(pDerivedObj);
            break;
        case CROWN_EXPLOSION:
            Crown_Explosion_Initialize(pDerivedObj);
            break;
        case WINNIE:
            Winnie_Initialize(pDerivedObj);
            break;
        case WINNIE_EXPLOSION:
            Winnie_Explosion_Initialize(pDerivedObj);
            break;
        case TANK:
            Tank_Initialize(pDerivedObj);
            break;
        case TANK_EXPLOSION:
            Tank_Explosion_Initialize(pDerivedObj);
            break;
        case BABY:
            Baby_Initialize(pDerivedObj);
            break;
        case BABY_EXPLOSION:
            Baby_Explosion_Initialize(pDerivedObj);
            break;
        case TORNADO:
            Tornado_Initialize(pDerivedObj);
            break;
        case TORNADO_EXPLOSION:
            Tornado_Explosion_Initialize(pDerivedObj);
            break;
        default:
            // Optional: handle unknown values
            fprintf(stderr, "Unknown 'who' value: %d\n", who);
            break;
    }
    const char *sound_files[1] = {
        "bomb.mp3"
    };

    for (int i = 0; i < 1; i++) {
        char sound_path[64];
        snprintf(sound_path, sizeof(sound_path), "assets/sound/%s", sound_files[i]);

        ALLEGRO_SAMPLE *sample = al_load_sample(sound_path);
        if (sample) {
            pDerivedObj->sounds[i] = al_create_sample_instance(sample);
            al_set_sample_instance_playmode(pDerivedObj->sounds[i], ALLEGRO_PLAYMODE_ONCE);
            al_attach_sample_instance_to_mixer(pDerivedObj->sounds[i], al_get_default_mixer());
        } else {
            pDerivedObj->sounds[i] = NULL;
            fprintf(stderr, "Failed to load sound: %s\n", sound_path);
        }
    }
    
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
        if (proj->who == MAGA_EXPLOSION && !proj->gif->done) return; 
        if (proj->who == DUMP_TRUCK_EXPLOSION && !proj->gif->done) return;
        if (proj->who == POOP_EXPLOSION && !proj->gif->done) return;
        if (proj->who == DEPORT_EXPLOSION && !proj->gif->done) return;
        if (proj->who == CROWN_EXPLOSION && !proj->gif->done) return;
        if (proj->who == WINNIE_EXPLOSION && !proj->gif->done) return;
        if (proj->who == TANK_EXPLOSION && !proj->gif->done) return;
        self->dele = true;
        return;  // Don't update physics during explosion
    }

    if (proj->special_action <= 0 && proj->who == TANK) {
        int center_x = (int)(proj->hitbox->center_x(proj->hitbox)) - proj->width / 2;
        int center_y = (int)(proj->hitbox->center_y(proj->hitbox))  - proj->height / 2;
        Elements *explode = New_Projectile(Projectile_L, center_x, center_y, (float) proj->gif->display_index * 20, 7, POOP, proj->player);
        _Register_elements(scene, explode);
        proj->special_action = 15;
    }

    if (proj->action_cooldown > 0) proj->action_cooldown --;
    if (proj->special_action > 0) proj->special_action --;

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

    if (proj->durability < 1 || proj->action_cooldown > 0) return;

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

    switch (proj->who) {
        case MAGA:
            Maga_Interaction_Character(self, tar);
            break;
        case MAGA_EXPLOSION:
            Maga_Explosion_Interaction_Character(self, tar);
            break;
        case DUMP_TRUCK:
            Dump_Truck_Interaction_Character(self, tar);
            break;
        case DUMP_TRUCK_EXPLOSION:
            Dump_Truck_Explosion_Interaction_Character(self, tar);
            break;
        case POOP:
            Poop_Interaction_Character(self, tar);
            break;
        case POOP_EXPLOSION:
            Poop_Explosion_Interaction_Character(self, tar);
            break;
        case DEPORT:
            Deport_Interaction_Character(self, tar);
            break;
        case DEPORT_EXPLOSION:
            Deport_Explosion_Interaction_Character(self, tar);
            break;
        case CROWN:
            Crown_Interaction_Character(self, tar);
            break;
        case CROWN_EXPLOSION:
            Crown_Explosion_Interaction_Character(self, tar);
            break;
        case WINNIE:
            Winnie_Interaction_Character(self, tar);
            break;
        case WINNIE_EXPLOSION:
            Winnie_Explosion_Interaction_Character(self, tar);
            break;
        case TANK:
            Tank_Interaction_Character(self, tar);
            break;
        case TANK_EXPLOSION:
            Tank_Explosion_Interaction_Character(self, tar);
            break;
        case BABY:
            Baby_Interaction_Character(self, tar);
            break;
        case BABY_EXPLOSION:
            Baby_Explosion_Interaction_Character(self, tar);
            break;
        case TORNADO:
            Tornado_Interaction_Character(self, tar);
            break;
        case TORNADO_EXPLOSION:
            Tornado_Explosion_Interaction_Character(self, tar);
            break;
        default:
            // Optional: handle unknown projectiles
            fprintf(stderr, "Unknown projectile type: %d\n", proj->who);
            break;
    }
}
void _Projectile_interact_Ground(Elements *self, Elements *tar)
{
    Projectile *proj = (Projectile *)(self->pDerivedObj);
    Ground *ground = (Ground *)tar->pDerivedObj;

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

    for (int i = top; i <= bottom; i++) {
        for (int j = left; j <= right; j++) {
            if (!ground->hitboxes[i][j]) continue;
            if (ground->hitboxes[i][j]->overlap(ground->hitboxes[i][j], proj->hitbox)) {
                goto collision;
            }
        }
    }
    return;
    collision: {
        switch (proj->who) {
            case MAGA:
                Maga_Interaction_Ground(self, tar);
                break;
            case MAGA_EXPLOSION:
                Maga_Explosion_Interaction_Ground(self, tar);
                break;
            case DUMP_TRUCK:
                Dump_Truck_Interaction_Ground(self, tar);
                break;
            case DUMP_TRUCK_EXPLOSION:
                Dump_Truck_Explosion_Interaction_Ground(self, tar);
                break;
            case POOP:
                Poop_Interaction_Ground(self, tar);
                break;
            case POOP_EXPLOSION:
                Poop_Explosion_Interaction_Ground(self, tar);
                break;
            case DEPORT:
                Deport_Interaction_Ground(self, tar);
                break;
            case DEPORT_EXPLOSION:
                Deport_Explosion_Interaction_Ground(self, tar);
                break;
            case CROWN:
                Crown_Interaction_Ground(self, tar);
                break;
            case CROWN_EXPLOSION:
                Crown_Explosion_Interaction_Ground(self, tar);
                break;
            case WINNIE:
                Winnie_Interaction_Ground(self, tar);
                break;
            case WINNIE_EXPLOSION:
                Winnie_Explosion_Interaction_Ground(self, tar);
                break;
            case TANK:
                Tank_Interaction_Ground(self, tar);
                break;
            case TANK_EXPLOSION:
                Tank_Explosion_Interaction_Ground(self, tar);
                break;
            case BABY:
                Baby_Interaction_Ground(self, tar);
                break;
            case BABY_EXPLOSION:
                Baby_Explosion_Interaction_Ground(self, tar);
                break;
            case TORNADO:
                Tornado_Interaction_Ground(self, tar);
                break;
            case TORNADO_EXPLOSION:
                Tornado_Explosion_Interaction_Ground(self, tar);
                break;
            default:
                // Optional: handle unknown projectiles
                fprintf(stderr, "Unknown projectile type: %d\n", proj->who);
                break;
        }
    }
}
