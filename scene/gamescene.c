#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_ttf.h>
#include <math.h>
#include "gamescene.h"
#include "../element/element.h"
#include "../element/character.h"
#include "../element/ground.h"
#include "../element/floor.h"
#include "../element/projectile.h"
/*
   [GameScene function]
*/
Scene *New_GameScene(int label, int player1_who, int player2_who, int backgorund_who)
{
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);

    // setting derived object member
    if (backgorund_who == 0) pDerivedObj->background = al_load_bitmap("assets/maps/white_house_background.png");
    else if (backgorund_who == 1) pDerivedObj->background = al_load_bitmap("assets/maps/tiananmen_square_background.png");
    
    pDerivedObj->game_start_timer = 480;
    pDerivedObj->round_start_timer = ROUND_START_TIME;
    pDerivedObj->attack_start_timer = -1;
    pDerivedObj->round_who = Player1_L;
    pObj->pDerivedObj = pDerivedObj;

    // register element
    _Register_elements(pObj, New_Ground(backgorund_who, Ground_L));
    _Register_elements(pObj, New_Character(player1_who, Player1_L));
    _Register_elements(pObj, New_Character(player2_who, Player2_L));
    _Register_elements(pObj, New_Floor(Floor_L));

    // Load sound
    ALLEGRO_SAMPLE *song;
    song = al_load_sample("assets/sound/bgm.mp3");
    al_reserve_samples(20);
    pDerivedObj->bgm = al_create_sample_instance(song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->bgm, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->bgm, al_get_default_mixer());
    al_set_sample_instance_gain(pDerivedObj->bgm, 0.05);

    // Load sound
    song = al_load_sample("assets/sound/countdown.wav");
    al_reserve_samples(20);
    pDerivedObj->count = al_create_sample_instance(song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->count, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->count, al_get_default_mixer());
    al_set_sample_instance_gain(pDerivedObj->count, 0.2);

    // setting derived object function
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    return pObj;
}
void game_scene_update(Scene *self)
{
    // update every element
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Update(ele);
    }
    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Interact(ele);
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }

    if (key_state[ALLEGRO_KEY_0])
    {
        self->scene_end = true;
        window = 2;
    }
}
void game_scene_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene *pObj = ((GameScene *)(self->pDerivedObj));
    al_draw_bitmap(pObj->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }

    _game_round_engine(self);

    _draw_player_stats(self, Player1_L, 200, 900, false);   // Player 1, left to right
    _draw_player_stats(self, Player2_L, 1220, 900, true);   // Player 2, right to left

    _draw_attack_indicator(self, Player1_L); // gray triangle for c1
    _draw_attack_indicator(self, Player2_L); // gray triangle for c1

    al_play_sample_instance(pObj->bgm);
}
void game_scene_destroy(Scene *self)
{
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}
void _game_round_engine(Scene *self) {
    GameScene *pObj = ((GameScene *)(self->pDerivedObj));
    Elements *player_1 = _Get_label_elements(self, Player1_L).arr[0];
    Elements *player_2 = _Get_label_elements(self, Player2_L).arr[0];
    Character *c1 = (Character *)(player_1->pDerivedObj);
    Character *c2 = (Character *)(player_2->pDerivedObj);

    if (pObj->game_start_timer > 0) {
        ALLEGRO_BITMAP *number;
        if (pObj->game_start_timer >= 360) {
            number = al_load_bitmap("assets/numbers/3.png");
        } else if (pObj->game_start_timer < 360 && pObj->game_start_timer >= 240) {
            number = al_load_bitmap("assets/numbers/2.png");
        } else if (pObj->game_start_timer < 240 && pObj->game_start_timer >= 120) {
            number = al_load_bitmap("assets/numbers/1.png");
        } else {
            number = al_load_bitmap("assets/words/gamestart.png");
        }
        al_draw_bitmap(number, 960 - al_get_bitmap_width(number) / 2, 200 - al_get_bitmap_height(number) / 2, 0);
        c1->player_now = -1;
        c2->player_now = -1;
        pObj->game_start_timer --;
    } else if (pObj->game_start_timer == 0) {
        c1->player_now = Player1_L;
        c2->player_now = Player1_L;
        pObj->game_start_timer --;
        al_play_sample_instance(pObj->count);
    } else {
        if (c1->was_charging || c2->was_charging) {
            al_stop_sample_instance(pObj->count);
            ALLEGRO_BITMAP *number;
            if (pObj->round_start_timer >= 300) {
                if (pObj->round_who == Player1_L) number = al_load_bitmap("assets/words/player1sturn.png");
                else number = al_load_bitmap("assets/words/player2sturn.png");
            } else if (pObj->round_start_timer < 300 && pObj->round_start_timer >= 240) {
                number = al_load_bitmap("assets/numbers/5.png");
            } else if (pObj->round_start_timer < 240 && pObj->round_start_timer >= 180) {
                number = al_load_bitmap("assets/numbers/4.png");
            } else if (pObj->round_start_timer < 180 && pObj->round_start_timer >= 120) {
                number = al_load_bitmap("assets/numbers/3.png");
            } else if (pObj->round_start_timer < 120 && pObj->round_start_timer >= 60) {
                number = al_load_bitmap("assets/numbers/2.png");
            } else {
                number = al_load_bitmap("assets/numbers/1.png");
            }
            al_draw_bitmap(number, 960 - al_get_bitmap_width(number) / 2, 200 - al_get_bitmap_height(number) / 2, 0);
            pObj->attack_start_timer = ATTACK_START_TIME;
        } else {
            if (pObj->attack_start_timer >= 0) {
                if (pObj->attack_start_timer == 0) {
                    pObj->round_start_timer = 0;
                }
                c1->player_now = -1;
                c2->player_now = -1;

                pObj->attack_start_timer --;
            } else {
                ALLEGRO_BITMAP *number;
                if (pObj->round_start_timer > 0) {
                    if (pObj->round_start_timer >= 300) {
                        if (pObj->round_who == Player1_L) number = al_load_bitmap("assets/words/player1sturn.png");
                        else number = al_load_bitmap("assets/words/player2sturn.png");
                    } else if (pObj->round_start_timer < 300 && pObj->round_start_timer >= 240) {
                        number = al_load_bitmap("assets/numbers/5.png");
                    } else if (pObj->round_start_timer < 240 && pObj->round_start_timer >= 180) {
                        al_play_sample_instance(pObj->count);
                        number = al_load_bitmap("assets/numbers/4.png");
                    } else if (pObj->round_start_timer < 180 && pObj->round_start_timer >= 120) {
                        number = al_load_bitmap("assets/numbers/3.png");
                    } else if (pObj->round_start_timer < 120 && pObj->round_start_timer >= 60) {
                        number = al_load_bitmap("assets/numbers/2.png");
                    } else {
                        number = al_load_bitmap("assets/numbers/1.png");
                    }
                    al_draw_bitmap(number, 960 - al_get_bitmap_width(number) / 2, 200 - al_get_bitmap_height(number) / 2, 0);
                    pObj->round_start_timer --;
                } else {
                    if (pObj->round_who == Player1_L) {
                        c1->player_now = Player2_L;
                        c2->player_now = Player2_L;
                        pObj->round_who = Player2_L;
                    } else {
                        c1->player_now = Player1_L;
                        c2->player_now = Player1_L;
                        pObj->round_who = Player1_L;
                    }
                    pObj->round_start_timer = ROUND_START_TIME;
                }
            }
        }
    }
}
void _draw_player_stats(Scene *self, int label, int x, int y, bool flip) {
    GameScene *pObj = ((GameScene *)(self->pDerivedObj));
    Elements *player = _Get_label_elements(self, label).arr[0];
    Character *c = (Character *)(player->pDerivedObj);

    if (c->hp <= 0) {
        al_play_sample_instance(c->sounds[SOUND_DEATH]);

        while (al_get_sample_instance_playing(c->sounds[SOUND_DEATH])) {
            al_rest(0.01); // sleep for 10ms to prevent CPU overuse
        }

        self->scene_end = true;
        window = 2;
    }

    char text_buffer[32];
    float hp    = (float)c->hp        / HP_MAX * 500.0f;
    float exp   = (float)c->atk_level / EXP_MAX * 490.0f;
    float furry = (float)c->atk_furry / FURRY_MAX * 490.0f;
    float power = (float)c->atk_power / ATTACK_POWER_MAX * 190.0f;

    int w_bar = 500, h_bar = 30;
    int w_power = 50;

    // HP Bar
    al_draw_filled_rounded_rectangle(x - 5, y - 5, x + w_bar + 5, y + h_bar + 5, 10, 10, al_map_rgb(50, 50, 50));
    al_draw_filled_rounded_rectangle(x, y, x + w_bar, y + h_bar, 8, 8, al_map_rgb(100, 100, 100));
    if (!flip)
        al_draw_filled_rounded_rectangle(x, y, x + hp, y + h_bar, 8, 8, al_map_rgb(255, 105, 180));
    else
        al_draw_filled_rounded_rectangle(x + w_bar - hp, y, x + w_bar, y + h_bar, 8, 8, al_map_rgb(255, 105, 180));
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), x + 10, y + 2, ALLEGRO_ALIGN_LEFT, "Reputation");
    sprintf(text_buffer, "%d / %d", c->hp, HP_MAX);
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), x + w_bar - 10, y + 2, ALLEGRO_ALIGN_RIGHT, text_buffer);

    y += 40;

    // EXP Bar
    al_draw_filled_rounded_rectangle(x - 5, y - 5, x + w_bar + 5, y + h_bar + 5, 10, 10, al_map_rgb(50, 50, 50));
    al_draw_filled_rounded_rectangle(x, y, x + w_bar, y + h_bar, 8, 8, al_map_rgb(100, 100, 100));
    if (!flip)
        al_draw_filled_rounded_rectangle(x, y, x + exp + 10, y + h_bar, 8, 8, al_map_rgb(50,205,50));
    else
        al_draw_filled_rounded_rectangle(x + w_bar - exp - 10, y, x + w_bar, y + h_bar, 8, 8, al_map_rgb(127,255,0));
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), x + 10, y + 2, ALLEGRO_ALIGN_LEFT, "Supporter");
    sprintf(text_buffer, "%d / %d", c->atk_level, EXP_MAX);
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), x + w_bar - 10, y + 2, ALLEGRO_ALIGN_RIGHT, text_buffer);

    y += 40;

    // Furry Bar
    al_draw_filled_rounded_rectangle(x - 5, y - 5, x + w_bar + 5, y + h_bar + 5, 10, 10, al_map_rgb(50, 50, 50));
    al_draw_filled_rounded_rectangle(x, y, x + w_bar, y + h_bar, 8, 8, al_map_rgb(100, 100, 100));
    if (!flip)
        al_draw_filled_rounded_rectangle(x, y, x + furry + 10, y + h_bar, 8, 8, al_map_rgb(255,140,0));
    else
        al_draw_filled_rounded_rectangle(x + w_bar - furry - 10, y, x + w_bar, y + h_bar, 8, 8, al_map_rgb(255,140,0));
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), x + 10, y + 2, ALLEGRO_ALIGN_LEFT, "Furry");
    sprintf(text_buffer, "%d / %d", c->atk_furry, FURRY_MAX);
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), x + w_bar - 10, y + 2, ALLEGRO_ALIGN_RIGHT, text_buffer);

    // Power Bar (Vertical)
    int px = (!flip) ? x - 130 : x + w_bar + 70;
    al_draw_filled_rounded_rectangle(px - 5, 800, px + w_power + 5, 1010, 10, 10, al_map_rgb(50, 50, 50));
    al_draw_filled_rounded_rectangle(px, 805, px + w_power, 1005, 8, 8, al_map_rgb(100, 100, 100));
    al_draw_filled_rounded_rectangle(px, 995 - power, px + w_power, 1005, 8, 8, al_map_rgb(255,215,0));
}
void _draw_attack_indicator(Scene *self, int label) {
    Elements *player = _Get_label_elements(self, label).arr[0];
    Character *chara = (Character *)(player->pDerivedObj);
    float angle_deg = chara->atk_angle;
    
    if (!chara->dir) angle_deg = 180.0f - angle_deg;
    float angle_rad = angle_deg * (3.14159f / 180.0f);
    float power_scale = chara->atk_power * 5; // you can scale this further if needed

    int x = chara->x + chara->width / 2;
    int y = chara->y + chara->height / 2 - 16;
    if (!chara->dir) x -= 48;
    else x += 48;

    // tip of the triangle (direction of attack)
    float tip_x = x + cos(angle_rad) * power_scale;
    float tip_y = y + sin(angle_rad) * power_scale;

    // base width of the triangle
    float offset = 4.0; // you can adjust this for wider/narrower indicators

    // perpendicular angle for base
    float perp_angle = angle_rad + 3.14159f / 2;
    float base_x1 = x + cos(perp_angle) * offset;
    float base_y1 = y + sin(perp_angle) * offset;
    float base_x2 = x - cos(perp_angle) * offset;
    float base_y2 = y - sin(perp_angle) * offset;

    al_draw_filled_triangle(
        tip_x, tip_y,    // tip of triangle
        base_x1, base_y1, // base left
        base_x2, base_y2, // base right
        al_map_rgb(220, 20, 60)
    );
}