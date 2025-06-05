#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro.h>
#include "menu.h"
#include <stdbool.h>
#include "sceneManager.h"

#define CHARACTER_COUNT 3
#define CHARACTER_SIZE 400
int player1_index = 0; 
int player2_index = 1; 
static ALLEGRO_BITMAP *background = NULL;
static ALLEGRO_BITMAP *characters[CHARACTER_COUNT] = {NULL};
// static ALLEGRO_FONT *font = NULL;
static ALLEGRO_BITMAP *tutorial_popup = NULL;
static bool popup_active = false;
static double last_toggle_time_t = 0; 
static double last_switch_time_p1 = 0;
static double last_switch_time_p2 = 0;

/* [Menu function] */

Scene *New_Menu(int label)
{
    Menu *pDerivedObj = (Menu *)malloc(sizeof(Menu));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    // Load pictures
    tutorial_popup = al_load_bitmap("assets/startframe/tutorial_popup.png");
    background = al_load_bitmap("assets/startframe/startframe_bg.jpg");
    characters[0] = al_load_bitmap("assets/startframe/trump.png");
    characters[1] = al_load_bitmap("assets/startframe/jinping.png");
    characters[2] = al_load_bitmap("assets/startframe/guodong.png");
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/theme_song.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = menu_update;
    pObj->Draw = menu_draw;
    pObj->Destroy = menu_destroy;
    return pObj;
}

void menu_update(Scene *self)
{
    double now = al_get_time();
    if (key_state[ALLEGRO_KEY_T] && now - last_toggle_time_t > 0.25) {
        popup_active = !popup_active;         // tutorial
        last_toggle_time_t = now;             
    }

    if (popup_active == false) {
        if (key_state[ALLEGRO_KEY_ENTER]) //start
        {
            selected_player1 = player1_index;
            selected_player2 = player2_index;
            // Randomly choose between player1_index and player2_index for selected_map
            if (rand() % 2 == 0)
                selected_map = player1_index;
            else
                selected_map = player2_index;
            self->scene_end = true;
            window = 1;
        }
        if (key_state[ALLEGRO_KEY_P]) {  //pause
            self->scene_end = true;
            window = Pause_L;
        }
        if (key_state[ALLEGRO_KEY_ESCAPE]) //esc
        {
            exit(0);
        }
        // Player1 use A/D 
        if (now - last_switch_time_p1 > 0.25) {
            if (key_state[ALLEGRO_KEY_A]) {
                player1_index = (player1_index - 1 + CHARACTER_COUNT) % CHARACTER_COUNT;
                last_switch_time_p1 = now;
            } else if (key_state[ALLEGRO_KEY_D]) {
                player1_index = (player1_index + 1) % CHARACTER_COUNT;
                last_switch_time_p1 = now;
            }
        }
        // Player2 use ←/→ 
        if (now - last_switch_time_p2 > 0.25) {
            if (key_state[ALLEGRO_KEY_LEFT]) {
                player2_index = (player2_index - 1 + CHARACTER_COUNT) % CHARACTER_COUNT;
                last_switch_time_p2 = now;
            } else if (key_state[ALLEGRO_KEY_RIGHT]) {
                player2_index = (player2_index + 1) % CHARACTER_COUNT;
                last_switch_time_p2 = now;
            }
        } 
    }
    
    return;
}

void menu_draw(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    al_draw_bitmap(background, 0, 0, 0); //draw background
    al_draw_bitmap(characters[player1_index], 130, 410, 0);//player1
    al_draw_bitmap(characters[player2_index], 1400, 410, 0); //player2
    if (popup_active == true) al_draw_bitmap(tutorial_popup, 400, 240, 0); //tutorial
    al_play_sample_instance(Obj->sample_instance);
}

void menu_destroy(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}
