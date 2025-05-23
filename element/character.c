#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "character.h"
#include "ground.h"
#include "projectile.h"
#include "../scene/sceneManager.h"
#include "../shapes/Rectangle.h"
#include "../algif5/algif.h"
#include "../scene/gamescene.h"
#include <stdio.h>
#include <stdbool.h>
/*
   [Character function]
*/

#define GRAVITY 1000.0f
#define JUMP_VELOCITY -1000.0f
#define MOVE_SPEED     5

Elements *New_Character(int label)
{
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load character images
    char state_string[3][10] = {"idle", "run", "attack"};
    for (int i = 0; i < 3; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/chara_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of character
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = 300;
    pDerivedObj->y = 0;
    pDerivedObj->vy = 0; 
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->dir = true; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->is_jumping = false;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Draw = Character_draw;
    pObj->Update = Character_update;
    pObj->Interact = Character_interact;
    pObj->Destroy = Character_destory;
    return pObj;
}
void Character_update(Elements *self) {
    Character *chara = (Character *)self->pDerivedObj;

    // Jump trigger
    if (key_state[ALLEGRO_KEY_W] && _Character_is_standing_on_ground(self)) {
        chara->vy = JUMP_VELOCITY;
        chara->is_jumping = true;
    }

    // Horizontal movement
    if (key_state[ALLEGRO_KEY_A]) {
        chara->dir = false;
        _Character_update_position(self, -MOVE_SPEED, 0);
        if (chara->state != ATK) chara->state = MOVE;
    } else if (key_state[ALLEGRO_KEY_D]) {
        chara->dir = true;
        _Character_update_position(self, MOVE_SPEED, 0);
        if (chara->state != ATK) chara->state = MOVE;
    } else if (!chara->is_jumping && chara->state != ATK) {
        chara->state = STOP;
    }

    // Jump physics
    if (chara->is_jumping) {
        float dt = 1.0f / FPS;
        chara->vy += GRAVITY * dt;
        _Character_update_position(self, 0, (int)(chara->vy * dt));

        if (_Character_is_standing_on_ground(self)) {
            chara->vy = 0;
            chara->is_jumping = false;
            if (chara->state != ATK) chara->state = STOP;
        }
    }

    if (key_state[ALLEGRO_KEY_SPACE] && chara->state != ATK) {
    chara->state = ATK;
    chara->new_proj = false;

    // reset animation
    if (chara->gif_status[ATK]) {
        chara->gif_status[ATK]->display_index = 0;
        chara->gif_status[ATK]->done = false;
    }
    }

    if (chara->state == ATK) {
        if (chara->gif_status[ATK]->display_index == 2 && !chara->new_proj) {
            Elements *pro = chara->dir
                ? New_Projectile(Projectile_L, chara->x + chara->width - 100, chara->y + 10, 5)
                : New_Projectile(Projectile_L, chara->x - 50, chara->y + 10, -5);
            _Register_elements(scene, pro);
            chara->new_proj = true;
        }

        if (chara->gif_status[ATK]->done) {
            chara->state = STOP;
            chara->new_proj = false;
        }
    }
}
void Character_draw(Elements *self)
{
    // with the state, draw corresponding image
    Character *chara = ((Character *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
    }
    if (chara->state == ATK && chara->gif_status[chara->state]->display_index == 2)
    {
        al_play_sample_instance(chara->atk_Sound);
    }
}
void Character_destory(Elements *self)
{
    Character *Obj = ((Character *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 3; i++)
        algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Character_update_position(Elements *self, int dx, int dy)
{
    Character *chara = ((Character *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void Character_interact(Elements *self)
{
    Character *chara = (Character *)(self->pDerivedObj);

    // Prevent forward movement if wall in front is 2+ tiles high
    // if (_Character_is_blocked_by_wall(self) && chara->state == MOVE) {
    //     chara->state = STOP;
    //     return;
    // }

    // Handle vertical collisions (upward push)
    ElementVec ground_elements = _Get_label_elements(scene, Ground_L);

    for (int i = 0; i < ground_elements.len; i++) {
        Ground *ground = (Ground *)(ground_elements.arr[i]->pDerivedObj);

        for (int r = 0; r < MAP_ROWS; r++) {
            for (int c = 0; c < MAP_COLS; c++) {
                if (!ground->active[r][c]) continue;

                Shape *tile_hitbox = ground->hitboxes[r][c];
                if (tile_hitbox->overlap(tile_hitbox, chara->hitbox)) {
                    _Character_update_position(self, 0, -1);
                    return;
                }
            }
        }
    }

    // Apply gravity if not on ground
    if (!_Character_is_standing_on_ground(self)) {
        _Character_update_position(self, 0, 3);
    }
}

bool _Character_is_standing_on_ground(Elements *self) {
    Character *chara = (Character *)(self->pDerivedObj);
    ElementVec ground_elements = _Get_label_elements(scene, Ground_L);

    for (int i = 0; i < ground_elements.len; i++) {
        Ground *ground = (Ground *)(ground_elements.arr[i]->pDerivedObj);

        for (int r = 0; r < MAP_ROWS; r++) {
            for (int c = 0; c < MAP_COLS; c++) {
                if (!ground->active[r][c]) continue;

                Shape *tile_hitbox = ground->hitboxes[r][c];

                int char_bottom = chara->y + chara->height;
                int tile_top = tile_hitbox->get_top(tile_hitbox);
                int char_left = chara->x;
                int char_right = chara->x + chara->width;
                int tile_left = tile_hitbox->get_left(tile_hitbox);
                int tile_right = tile_hitbox->get_right(tile_hitbox);

                bool horizontally_aligned = !(char_right <= tile_left || char_left >= tile_right);
                bool directly_above = char_bottom <= tile_top && tile_top - char_bottom <= 1;

                if (horizontally_aligned && directly_above) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool _Character_is_blocked_by_wall(Elements *self) {
    Character *chara = (Character *)(self->pDerivedObj);
    ElementVec ground_elements = _Get_label_elements(scene, Ground_L);

    int check_x = chara->dir
        ? chara->x + chara->width + 1  // one pixel to the right
        : chara->x - 1;                // one pixel to the left

    int look_col = check_x / TILE_WIDTH;

    for (int i = 0; i < ground_elements.len; i++) {
        Ground *ground = (Ground *)(ground_elements.arr[i]->pDerivedObj);

        if (look_col < 0 || look_col >= MAP_COLS)
            continue;

        int solid_count = 0;

        for (int r = 0; r < MAP_ROWS; r++) {
            if (!ground->active[r][look_col]) continue;

            int tile_y = r * TILE_HEIGHT;

            // Only count if the tile overlaps character's body vertically
            if (tile_y <= chara->y + chara->height &&
                tile_y + TILE_HEIGHT >= chara->y) {
                solid_count++;
            }
        }

        if (solid_count >= 2)
            return true;
    }

    return false;
}