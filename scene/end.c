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
    if (mouse_states.buttons & 1)
    {
        if(mouse_states.x >= Obj->title_x+250 && mouse_states.x <= Obj->title_x+750 && mouse_states.y >= Obj->title_y+500 && mouse_states.y <= Obj->title_y+620){
            self->scene_end = true;
            window = 0; // change the scene to start frame
        }
        if(mouse_states.x >= Obj->title_x+250 && mouse_states.x <= Obj->title_x+750 &&mouse_states.y >= Obj->title_y+650 && mouse_states.y <= Obj->title_y+770){
            self->scene_end = true;
            window = -1; // change the scene (quit)
        } 
    }
    
    if (key_state[ALLEGRO_KEY_9])
    {
        self->scene_end = true;
        window = 3;
    }
    
    return;
}
void end_draw(Scene *self)
{
    End *Obj = ((End *)(self->pDerivedObj));
    al_draw_bitmap(Obj->background, 0, 0, 0);
    al_draw_bitmap(Obj->img_1, Obj->title_x + 150, Obj->title_y + 10, 0);
    al_draw_bitmap(Obj->img_2, Obj->title_x + 250, Obj->title_y + 500, 0);
    al_draw_bitmap(Obj->img_3, Obj->title_x + 250, Obj->title_y + 650, 0);
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