#ifndef END_H_INCLUDED
#define END_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include "scene.h"
/*
   [End object]
*/
typedef struct _End
{
    ALLEGRO_FONT *font;
    ALLEGRO_BITMAP *img_1, *img_2, *img_3;
    ALLEGRO_BITMAP *background;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    int title_x, title_y;
} End;
Scene *New_End(int label);
void end_update(Scene *self);
void end_draw(Scene *self);
void end_destroy(Scene *self);


#endif
