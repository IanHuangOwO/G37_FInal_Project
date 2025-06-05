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
    pDerivedObj->volume_bar_x = 900;
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
    pDerivedObj->background = al_load_bitmap("assets/maps/tiananmen_square_background.png");
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

    int screen_w = al_get_display_width(al_get_current_display());
    int screen_h = al_get_display_height(al_get_current_display());
    int center_x = screen_w / 2;

    int img3_w = al_get_bitmap_width(Obj->img_3);
    int img3_h = al_get_bitmap_height(Obj->img_3);
    int img4_w = al_get_bitmap_width(Obj->img_4);
    int img4_h = al_get_bitmap_height(Obj->img_4);

    int resume_x = center_x - img3_w / 2;
    int resume_y = screen_h / 2 + 50;
    int exit_x = center_x - img4_w / 2;
    int exit_y = screen_h / 2 + 200;

    // Handle volume bar click
    if (mouse_states.buttons & 1)
    {
        if (mouse_states.x >= Obj->volume_bar_x &&
            mouse_states.x <= Obj->volume_bar_x + Obj->volume_bar_width &&
            mouse_states.y >= Obj->volume_bar_y &&
            mouse_states.y <= Obj->volume_bar_y + Obj->volume_bar_height)
        {
            Obj->volume = (float)(mouse_states.x - Obj->volume_bar_x) / Obj->volume_bar_width;
            if (Obj->volume < 0.0f) Obj->volume = 0.0f;
            if (Obj->volume > 1.0f) Obj->volume = 1.0f;
            al_set_mixer_gain(al_get_default_mixer(), Obj->volume);
        }

        // Resume button click
        if (mouse_states.x >= resume_x && mouse_states.x <= resume_x + img3_w &&
            mouse_states.y >= resume_y && mouse_states.y <= resume_y + img3_h)
        {
            self->scene_end = true;
            window = 0;
        }

        // Exit button click
        if (mouse_states.x >= exit_x && mouse_states.x <= exit_x + img4_w &&
            mouse_states.y >= exit_y && mouse_states.y <= exit_y + img4_h)
        {
            self->scene_end = true;
            exit(0);
        }
    }
}
void pause_draw(Scene *self)
{
    Pause *Obj = ((Pause *)(self->pDerivedObj));

    int center_x = WIDTH / 2;

    int img3_w = al_get_bitmap_width(Obj->img_3);
    int img4_w = al_get_bitmap_width(Obj->img_4);
    int bar_img_w = al_get_bitmap_width(Obj->img_1);

    // Save title_x for button positioning
    Obj->title_x = center_x;
    Obj->title_y = 0;

    // Draw background
    al_draw_bitmap(Obj->background, 0, 0, 0);

    // Draw volume label (left of bar)
    al_draw_bitmap(Obj->img_1, Obj->volume_bar_x - bar_img_w - 100, Obj->volume_bar_y, 0);

    // Draw volume fill bar
    al_draw_filled_rounded_rectangle(
        Obj->volume_bar_x, Obj->volume_bar_y,
        Obj->volume_bar_x + Obj->volume * Obj->volume_bar_width,
        Obj->volume_bar_y + Obj->volume_bar_height,
        10, 10, al_map_rgb(0, 255, 0)
    );

    // Draw volume icon
    al_draw_bitmap(Obj->img_2, Obj->volume_bar_x, Obj->volume_bar_y, 0);

    // Draw resume button
    al_draw_bitmap(Obj->img_3, center_x - img3_w / 2, HEIGHT / 2 + 50, 0);

    // Draw exit button
    al_draw_bitmap(Obj->img_4, center_x - img4_w / 2, HEIGHT / 2 + 200, 0);

    // Draw volume text
    al_draw_textf(
        Obj->font,
        al_map_rgb(255, 255, 255),
        Obj->volume_bar_x + Obj->volume_bar_width + 10,
        Obj->volume_bar_y + 10,
        0,
        "%d", (int)(Obj->volume * 100)
    );

    al_play_sample_instance(Obj->sample_instance);
}

void pause_destroy(Scene *self)
{
    Pause *Obj = ((Pause *)(self->pDerivedObj));
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    al_destroy_bitmap(Obj->img_1);
    al_destroy_bitmap(Obj->img_2);
    al_destroy_bitmap(Obj->img_3);
    al_destroy_bitmap(Obj->img_4);
    free(Obj);
    free(self);
}