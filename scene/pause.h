#ifndef PAUSE_H_INCLUDED
#define PAUSE_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include "scene.h"
/*
   [Pause object]
*/
typedef struct _Pause
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_BITMAP *background;
    ALLEGRO_BITMAP *img_1, *img_2, *img_3, *img_4;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    ALLEGRO_MOUSE_STATE mouse_states;
    int title_x, title_y;
    int volume_bar_x, volume_bar_y, volume_bar_width, volume_bar_height;
    float volume;
    char volume_text[];
} Pause;
Scene *New_Pause(int label);
void pause_update(Scene *self);
void pause_draw(Scene *self);
void pause_destroy(Scene *self);

#endif