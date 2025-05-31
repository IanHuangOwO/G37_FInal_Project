#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/mouse.h>
#include <allegro5/events.h>
#include "pause.h"
#include <stdbool.h>
#include <allegro5/allegro.h>
#include <stdio.h>
/*
   [End function]
*/
Scene *New_Pause(int label)
{
    Pause *pDerivedObj = (Pause *)malloc(sizeof(Pause));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 50, 0);
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/theme_song.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = 0;
    pDerivedObj->title_y = 0;
    pDerivedObj->volume_bar_x = 470;
    pDerivedObj->volume_bar_y = 200;
    pDerivedObj->volume_bar_width = 406;
    pDerivedObj->volume_bar_height = 64;
    pDerivedObj->volume = 1.0f;
    //pDerivedObj->volume_text[0] = 0;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pDerivedObj->background = al_load_bitmap("assets/maps/white_house_background.png");
    pDerivedObj->img_1 = al_load_bitmap("assets/image/volume.png");
    pDerivedObj->img_2 = al_load_bitmap("assets/image/volume_icon.png");
    pDerivedObj->img_3 = al_load_bitmap("assets/image/resume.png");
    pDerivedObj->img_4 = al_load_bitmap("assets/image/exit.png");
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = pause_update;
    pObj->Draw = pause_draw;
    pObj->Destroy = pause_destroy;
    return pObj;
}
void pause_update(Scene *self)
{
    Pause *Obj = ((Pause *)(self->pDerivedObj));
    ALLEGRO_MOUSE_STATE mouse_states;
    al_get_mouse_state(&mouse_states);
    if (mouse_states.buttons & 1)
    {
        if (mouse_states.x >= Obj->volume_bar_x &&
            mouse_states.y <= Obj->volume_bar_x + Obj->volume_bar_width &&
            mouse_states.y >= Obj->volume_bar_y &&
            mouse_states.y <= Obj->volume_bar_y + Obj->volume_bar_height)
        {
            Obj->volume = (float)(mouse_states.x - Obj->volume_bar_x) / Obj->volume_bar_width;
            if (Obj->volume < 0.0f) Obj->volume = 0.0f;
            if (Obj->volume > 1.0f) Obj->volume = 1.0f;
            al_set_mixer_gain(al_get_default_mixer(), Obj->volume);
        }

        // check if click the button
        if(mouse_states.x >= Obj->title_x+250 && mouse_states.x <= Obj->title_x+750 && 
            mouse_states.y >= Obj->title_y+350 && mouse_states.y <= Obj->title_y+470)
        {
            self->scene_end = true;
            window = 0; // change the scene to start frame
        }
        if(mouse_states.x >= Obj->title_x+250 && mouse_states.x <= Obj->title_x+750 &&
            mouse_states.y >= Obj->title_y+550 && mouse_states.y <= Obj->title_y+770)
        {
            self->scene_end = true;
            window = -1; // change the scene (quit)
        } 
    }
    return;
}
void pause_draw(Scene *self)
{
    Pause *Obj = ((Pause *)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    al_draw_bitmap(Obj->img_1, Obj->volume_bar_x-400, Obj->volume_bar_y, 0);
    al_draw_filled_rectangle(
        Obj->volume_bar_x, Obj->volume_bar_y,
        Obj->volume_bar_x + Obj->volume * Obj->volume_bar_width, Obj->volume_bar_y + Obj->volume_bar_height,
        al_map_rgb(0, 255, 0)
    );
    al_draw_bitmap(Obj->img_2, Obj->volume_bar_x, Obj->volume_bar_y, 0);
    al_draw_bitmap(Obj->img_3, Obj->title_x + 250, Obj->title_y + 350, 0);
    al_draw_bitmap(Obj->img_4, Obj->title_x + 250, Obj->title_y + 550, 0);  
    al_draw_textf(
        Obj->font,
        al_map_rgb(255, 255, 255),
        Obj-> volume_bar_x-320, Obj->volume_bar_y,
        0,
        "       : %d", (int)(Obj->volume * 100)
    ); 
    al_play_sample_instance(Obj->sample_instance);
}
void pause_destroy(Scene *self)
{
    Pause *Obj = ((Pause *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    // ALLEGRO_BITMAP *background = Obj->background;
    // al_destroy_bitmap(background);
    al_destroy_bitmap(Obj->img_1);
    al_destroy_bitmap(Obj->img_2);
    al_destroy_bitmap(Obj->img_3);
    al_destroy_bitmap(Obj->img_4);
    free(Obj);
    free(self);
}