#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "character.h"
#include "ground.h"
#include "projectile.h"
#include "../scene/sceneManager.h"
#include "../shapes/Rectangle.h"
#include "../physics/physics.h"
#include "../algif5/algif.h"
#include "../scene/gamescene.h"
#include <stdio.h>
#include <stdbool.h>
/*
   [Character function]
*/

#define JUMP_VELOCITY -8.0f
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
    pDerivedObj->vx = 0;
    pDerivedObj->vy = 0; 
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->dir = true; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = STOP;
    pDerivedObj->is_in_air = false;
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
    
    Contact_Check_To_Character(self);  

    // Determine if standing on the ground using contact info
    bool grounded = (chara->contact.wall_bot_y != -1 && chara->y + chara->height == chara->contact.wall_bot_y);
    chara->is_in_air = !grounded;
    
    // Jump if grounded and key is pressed
    if (key_state[ALLEGRO_KEY_W] && grounded) {
        chara->vy = JUMP_VELOCITY;
        chara->is_in_air = true;
    }

    // Horizontal movement
    if (key_state[ALLEGRO_KEY_A]) {
        chara->dir = false;
        chara->vx = -MOVE_SPEED;  // ← store velocity, not move directly
        if (chara->state != ATK) chara->state = MOVE;
    } else if (key_state[ALLEGRO_KEY_D]) {
        chara->dir = true;
        chara->vx = MOVE_SPEED;
        if (chara->state != ATK) chara->state = MOVE;
    } else {
        chara->vx = 0;
        if (chara->state != ATK) chara->state = STOP;
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

    Movement_Physics_To_Character(self);
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
    Character *chara = ((Character *)(self->pDerivedObj));
    al_destroy_sample_instance(chara->atk_Sound);
    for (int i = 0; i < 3; i++)
        algif_destroy_animation(chara->gif_status[i]);
    free(chara->hitbox);
    free(chara);
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

void Character_interact(Elements *self) {}