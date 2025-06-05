#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "character.h"
#include "projectile.h"
#include "particle.h"
#include "../character/trump.h"
#include "../character/jinping.h"
#include "../character/guodong.h"
#include "../scene/sceneManager.h"
#include "../shapes/Rectangle.h"
#include "../physics/physics.h"
#include "../algif5/algif.h"
#include "../scene/gamescene.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
/*
   [Character function]
*/

Elements *New_Character(int who, int label)
{
    Character *pDerivedObj = (Character *)malloc(sizeof(Character));
    Elements *pObj = New_Elements(label);

    // Load character assets based on `who`
    if (who == 0)       Trump_Load_Assets(pDerivedObj);
    else if (who == 1)  JinPing_Load_Assets(pDerivedObj);
    else                GuoDong_Load_Assets(pDerivedObj);

    // initial the geometric information of character
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    if (label == 1) pDerivedObj->x = 200;
    else pDerivedObj->x = 1720;
    pDerivedObj->y = 150;
    pDerivedObj->vx = 0;
    pDerivedObj->vy = 0; 
    pDerivedObj->bounce_decay = 0;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);

    // initial the animation component
    pDerivedObj->who = who;
    pDerivedObj->player = label;
    pDerivedObj->state = IDLE;
    if (label == 1) pDerivedObj->dir = true;
    else pDerivedObj->dir = false;
    pDerivedObj->is_in_air = false;

    // Default attack parameters
    pDerivedObj->atk_power = 10.0f;
    pDerivedObj->atk_angle = -45.0f;
    pDerivedObj->atk_level = 0;
    pDerivedObj->atk_furry = 0;
    pDerivedObj->charging = true;
    pDerivedObj->was_charging = false;
    pDerivedObj->hp = HP_MAX;
    pDerivedObj->hurt_cooldown = 0;
    pDerivedObj->new_proj = false;
    pDerivedObj->ultimate = false;
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
    // if (((key_state[ALLEGRO_KEY_W] && self->label == 1) || (key_state[ALLEGRO_KEY_UP] && self->label == 2)) && grounded) {
    //     chara->vy = -8f;
    //     chara->is_in_air = true;
    // }

    if (chara->player_now == chara->player) {
        // Arrage Angle 
        if ((key_state[ALLEGRO_KEY_W] && self->label == 1) || (key_state[ALLEGRO_KEY_UP] && self->label == 2)) {
            chara->atk_angle -= ATTACK_ANGLE_CHARGE_SPEED;
            if (chara->atk_angle < ATTACK_ANGLE_MIN) chara->atk_angle = ATTACK_ANGLE_MAX;
            // printf("\rPlayer: %d Angle: %f", chara->player, -chara->atk_angle);
        } 
        else if ((key_state[ALLEGRO_KEY_S] && self->label == 1) || (key_state[ALLEGRO_KEY_DOWN] && self->label == 2)) {
            chara->atk_angle += ATTACK_ANGLE_CHARGE_SPEED;
            if (chara->atk_angle > ATTACK_ANGLE_MAX) chara->atk_angle = ATTACK_ANGLE_MAX;
            // printf("\rPlayer: %d Angle: %f", chara->player, -chara->atk_angle);
        }

        // Horizontal movement
        if ((key_state[ALLEGRO_KEY_A] && self->label == 1) || (key_state[ALLEGRO_KEY_LEFT] && self->label == 2)) {
            chara->dir = false;
            chara->vx = chara->atk_level > 0 ? -MOVE_SPEED : 0;  // ← store velocity, not move directly
            chara->atk_level -= chara->atk_level > 0 ? 5 : 0;
            if (chara->state != ATK) chara->state = MOVE;
        } else if ((key_state[ALLEGRO_KEY_D] && self->label == 1) || (key_state[ALLEGRO_KEY_RIGHT] && self->label == 2)) {
            chara->dir = true;
            chara->vx = chara->atk_level > 0 ? MOVE_SPEED : 0;
            chara->atk_level -= chara->atk_level > 0 ? 5 : 0;
            if (chara->state != ATK) chara->state = MOVE;
        } else {
            chara->vx = 0;
            if (chara->state != ATK) chara->state = IDLE;
        }

        if (((key_state[ALLEGRO_KEY_Q] && self->label == 1) || (key_state[ALLEGRO_KEY_SLASH] && self->label == 2)) && chara->state == IDLE) {
            al_play_sample_instance(chara->sounds[SOUND_ATTACK_CHARGING]);
            if (chara->charging) {
                chara->atk_power += ATTACK_POWER_CHARGE_SPEED;
                if (chara->atk_power >= ATTACK_POWER_MAX) {
                    chara->atk_power = ATTACK_POWER_MAX;
                    chara->charging = false;  // Start going down
                }
            } else {
                chara->atk_power -= ATTACK_POWER_CHARGE_SPEED;
                if (chara->atk_power <= ATTACK_POWER_MIN) {
                    chara->atk_power = ATTACK_POWER_MIN;
                    chara->charging = true;  // Start going up
                }
            }
            chara->was_charging = true;
        } else {
            if (chara->was_charging) {
                al_stop_sample_instance(chara->sounds[SOUND_ATTACK_CHARGING]);
                chara->state = ATK;
                chara->new_proj = false;
                
                // reset animation
                if (chara->gif_status[ATK]) {
                    chara->gif_status[ATK]->display_index = 0;
                    chara->gif_status[ATK]->done = false;
                }
                chara->was_charging = false;
            }
        }

        if (((key_state[ALLEGRO_KEY_E] && self->label == 1) || (key_state[ALLEGRO_KEY_COMMA] && self->label == 2)) && chara->atk_furry < FURRY_MAX && chara->ultimate == false) {
            chara->ultimate = true;
            chara->draw_ultimate = false;
        }
    }

    if (chara->state == ATK) {
        if (chara->gif_status[ATK]->display_index == 2 && !chara->new_proj) {
            Character_Attack(self);
            chara->atk_power = 10.0f;
        }

        if (chara->gif_status[ATK]->done) {
            chara->state = IDLE;
            chara->new_proj = false;
        }
    }

    if (chara->hurt_cooldown > 0) chara->hurt_cooldown--;

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
    if (chara->ultimate == true && chara->draw_ultimate == false)
    {
        Elements *par = New_Particle(Particle_L, chara->x + chara->width / 2, chara->y - 128, ULTIMATE);
        _Register_elements(scene, par);
        chara->draw_ultimate = true;
    }
}
void Character_destory(Elements *self)
{
    Character *chara = ((Character *)(self->pDerivedObj));
    // al_destroy_sample_instance(chara->sounds[SOUND_ATTACK_1]);
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

void Character_Attack(Elements *self) {
    Character *chara = (Character *)self->pDerivedObj;
    if (chara->who == 0)        Trump_Attack(self);
    else if (chara->who == 1)   JinPing_Attack(self);
    else                        GuoDong_Attack(self);
}
void Character_Hurt(Elements *self, int damage) {
    Character *chara = (Character *)self->pDerivedObj;
    // Skip if in invincibility cooldown
    if (chara->hurt_cooldown > 0) return;
    
    // Apply damage
    chara->hp -= damage;
    if (chara->hp < 0) chara->hp = 0;
    
    // Trigger hurt animation
    chara->state = HURT;
    chara->gif_status[HURT]->display_index = 0;
    chara->gif_status[HURT]->done = false;

    // Set cooldown
    chara->hurt_cooldown = 60;

    // Gain Furry
    Character_Furry(self, damage);

    al_play_sample_instance(chara->sounds[SOUND_HURT]);

    // printf("\nPlayer: %d Hp: %d\n", chara->player, chara->hp);
}
void Character_Furry(Elements *self, int amount) 
{
    Character *chara = (Character *)self->pDerivedObj;
    chara->atk_furry += amount;
    if (chara->atk_furry >= FURRY_MAX) chara->atk_furry = FURRY_MAX;
    //  printf("\nPlayer: %d Furry: %d\n", chara->player, chara->atk_furry);
}
void Character_Level(Elements *self, int amount)
{
    Character *chara = (Character *)self->pDerivedObj;
    chara->atk_level += amount;
    if (chara->atk_level >= EXP_MAX) chara->atk_level = EXP_MAX;
    // printf("\nPlayer: %d Level: %d\n", chara->player, chara->atk_level);
}