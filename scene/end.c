#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/mouse.h>
#include <allegro5/events.h>
#include "end.h"
#include "../global.h"
#include <stdbool.h>
/*
   [End function]
*/
Scene *New_End(int label)
{
    End *pDerivedObj = (End *)malloc(sizeof(End));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 20, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/end.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = 0;
    pDerivedObj->title_y = 0;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);    
    pDerivedObj->background = al_load_bitmap("assets/maps/white_house_background.png");
    pDerivedObj->img_1 = al_load_bitmap("assets/image/funnyend.png");
    pDerivedObj->img_2 = al_load_bitmap("assets/image/restart.png");
    pDerivedObj->img_3 = al_load_bitmap("assets/image/exit.png");
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = end_update;
    pObj->Draw = end_draw;
    pObj->Destroy = end_destroy;
    return pObj;
}
void end_update(Scene *self)
{
    End *Obj = ((End *)(self->pDerivedObj));
    ALLEGRO_MOUSE_STATE mouse_states;
    al_get_mouse_state(&mouse_states);

    int img_2_width = al_get_bitmap_width(Obj->img_2);
    int img_2_height = al_get_bitmap_height(Obj->img_2);
    int img_3_width = al_get_bitmap_width(Obj->img_3);
    int img_3_height = al_get_bitmap_height(Obj->img_3);

    int button2_x = WIDTH / 2 - img_2_width / 2;
    int button2_y = 600;
    int button3_x = WIDTH / 2 - img_3_width / 2;
    int button3_y = 750;

    if (mouse_states.buttons & 1) {
        if (mouse_states.x >= button2_x && mouse_states.x <= button2_x + img_2_width &&
            mouse_states.y >= button2_y && mouse_states.y <= button2_y + img_2_height) {
            self->scene_end = true;
            window = 0;
        }

        if (mouse_states.x >= button3_x && mouse_states.x <= button3_x + img_3_width &&
            mouse_states.y >= button3_y && mouse_states.y <= button3_y + img_3_height) {
            self->scene_end = true;
            window = -1;
        }
    }

    if (key_state[ALLEGRO_KEY_9]) {
        self->scene_end = true;
        window = 3;
    }
}
void end_draw(Scene *self)
{
    End *Obj = ((End *)(self->pDerivedObj));
    
    int center_x = WIDTH / 2;
    int img_1_width = al_get_bitmap_width(Obj->img_1);
    int img_2_width = al_get_bitmap_width(Obj->img_2);
    int img_3_width = al_get_bitmap_width(Obj->img_3);

    // int img_1_height = al_get_bitmap_height(Obj->img_1);
    // int img_2_height = al_get_bitmap_height(Obj->img_2);
    // int img_3_height = al_get_bitmap_height(Obj->img_3);

    // Draw background
    al_draw_bitmap(Obj->background, 0, 0, 0);

    // Dynamically center the images
    al_draw_bitmap(Obj->img_1, center_x - img_1_width / 2, 100, 0);
    al_draw_bitmap(Obj->img_2, center_x - img_2_width / 2, 600, 0);
    al_draw_bitmap(Obj->img_3, center_x - img_3_width / 2, 750, 0);

    // Save positions for click detection
    Obj->title_x = center_x; // used for input logic
    Obj->title_y = 0;

    al_play_sample_instance(Obj->sample_instance);
}
void end_destroy(Scene *self)
{
    End *Obj = ((End *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    al_destroy_bitmap(Obj->img_1);
    al_destroy_bitmap(Obj->img_2);
    al_destroy_bitmap(Obj->img_3);
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    free(Obj);
    free(self);
}