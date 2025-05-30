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
Scene *New_GameScene(int label)
{
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/maps/white_house_background.png");
    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_Ground(White_House, Ground_L));
    _Register_elements(pObj, New_Character(Trump, Player1_L));
    _Register_elements(pObj, New_Character(JinPing, Player2_L));
    _Register_elements(pObj, New_Floor(Floor_L));
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

    // Assume player 1 and player 2 Elements are labeled Player1_L and Player2_L
    Elements *p1 = _Get_label_elements(self, Player1_L).arr[0];
    Elements *p2 = _Get_label_elements(self, Player2_L).arr[0];

    Character *c1 = (Character *)(p1->pDerivedObj);
    Character *c2 = (Character *)(p2->pDerivedObj);

    // Player 1
    char text_buffer[32];
    float hp_p1 = (float)c1->hp / HP_MAX * 500.0f;
    float exp_p1 = (float)c1->atk_level / EXP_MAX * 490.0f;
    float furry_p1 = (float)c1->atk_furry / FURRY_MAX * 490.0f;
    float power_p1 = (float)c1->atk_power / ATTACK_POWER_MAX * 190.0f;

    al_draw_filled_rounded_rectangle(195, 895, 705, 925, 10, 10, al_map_rgb(50, 50, 50));
    al_draw_filled_rounded_rectangle(200, 900, 700, 920, 8, 8, al_map_rgb(100, 100, 100));
    al_draw_filled_rounded_rectangle(200, 900, 200 + hp_p1, 920, 8, 8, al_map_rgb(255, 105, 180));
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), 210, 902, ALLEGRO_ALIGN_LEFT, "Reputation");
    sprintf(text_buffer, "%d / %d", c1->hp, HP_MAX);
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), 680, 902, ALLEGRO_ALIGN_RIGHT, text_buffer);

    al_draw_filled_rounded_rectangle(195, 935, 705, 965, 10, 10, al_map_rgb(50, 50, 50));
    al_draw_filled_rounded_rectangle(200, 940, 700, 960, 8, 8, al_map_rgb(100, 100, 100));
    al_draw_filled_rounded_rectangle(200, 940, 210 + exp_p1, 960, 8, 8, al_map_rgb(50,205,50));
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), 210, 942, ALLEGRO_ALIGN_LEFT, "Supporter");
    sprintf(text_buffer, "%d / %d", c1->atk_level, EXP_MAX);
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), 680, 942, ALLEGRO_ALIGN_RIGHT, text_buffer);

    al_draw_filled_rounded_rectangle(195, 975, 705, 1005, 10, 10, al_map_rgb(50, 50, 50));
    al_draw_filled_rounded_rectangle(200, 980, 700, 1000, 8, 8, al_map_rgb(100, 100, 100));
    al_draw_filled_rounded_rectangle(200, 980, 210 + furry_p1, 1000, 8, 8, al_map_rgb(255,140,0));
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), 210, 982, ALLEGRO_ALIGN_LEFT, "Furry");
    sprintf(text_buffer, "%d / %d", c1->atk_furry, FURRY_MAX);
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), 680, 982, ALLEGRO_ALIGN_RIGHT, text_buffer);

    al_draw_filled_rounded_rectangle(70, 800, 125, 1010, 10, 10, al_map_rgb(50, 50, 50));
    al_draw_filled_rounded_rectangle(75, 805, 120, 1005, 8, 8, al_map_rgb(100, 100, 100));
    al_draw_filled_rounded_rectangle(75, 995 - power_p1, 120, 1005, 8, 8, al_map_rgb(255,215,0));

    // Player 2
    float hp_p2    = (float)c2->hp / HP_MAX * 500.0f;
    float exp_p2   = (float)c2->atk_level / EXP_MAX * 490.0f;
    float furry_p2 = (float)c2->atk_furry / FURRY_MAX * 490.0f;
    float power_p2 = (float)c2->atk_power / ATTACK_POWER_MAX * 190.0f;

    // HP Bar
    al_draw_filled_rounded_rectangle(1215, 895, 1725, 925, 10, 10, al_map_rgb(50, 50, 50));
    al_draw_filled_rounded_rectangle(1220, 900, 1720, 920, 8, 8, al_map_rgb(100, 100, 100));
    al_draw_filled_rounded_rectangle(1720 - hp_p2, 900, 1720, 920, 8, 8, al_map_rgb(255,105,180));
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), 1600, 902, ALLEGRO_ALIGN_LEFT, "Reputation");
    sprintf(text_buffer, "%d / %d", c2->hp, HP_MAX);
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), 1240, 902, ALLEGRO_ALIGN_LEFT, text_buffer);

    // Exp Bar
    al_draw_filled_rounded_rectangle(1215, 935, 1725, 965, 10, 10, al_map_rgb(50, 50, 50));
    al_draw_filled_rounded_rectangle(1220, 940, 1720, 960, 8, 8, al_map_rgb(100, 100, 100));
    al_draw_filled_rounded_rectangle(1710 - exp_p2, 940, 1720, 960, 8, 8, al_map_rgb(127,255,0));
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), 1600, 942, ALLEGRO_ALIGN_LEFT, "Supporter");
    sprintf(text_buffer, "%d / %d", c2->atk_level, ATTACK_POWER_MAX);
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), 1240, 942, ALLEGRO_ALIGN_LEFT, text_buffer);

    // Furry Bar
    al_draw_filled_rounded_rectangle(1215, 975, 1725, 1005, 10, 10, al_map_rgb(50, 50, 50));
    al_draw_filled_rounded_rectangle(1220, 980, 1720, 1000, 8, 8, al_map_rgb(100, 100, 100));
    al_draw_filled_rounded_rectangle(1710 - furry_p2, 980, 1720, 1000, 8, 8, al_map_rgb(255,140,0));
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), 1600, 982, ALLEGRO_ALIGN_LEFT, "Furry");
    sprintf(text_buffer, "%d / %d", c2->atk_furry, FURRY_MAX);
    al_draw_text(pObj->font, al_map_rgb(255, 255, 255), 1240, 982, ALLEGRO_ALIGN_LEFT, text_buffer);

    // Power Bar (Vertical)
    al_draw_filled_rounded_rectangle(1800, 800, 1855, 1010, 10, 10, al_map_rgb(50, 50, 50));
    al_draw_filled_rounded_rectangle(1805, 805, 1850, 1005, 8, 8, al_map_rgb(100, 100, 100));
    al_draw_filled_rounded_rectangle(1805, 995 - power_p2, 1850, 1005, 8, 8, al_map_rgb(255,215,0));

    draw_attack_indicator(p1, al_map_rgb(220,20,60)); // gray triangle for c1
    draw_attack_indicator(p2, al_map_rgb(220,20,60)); // gray triangle for c1
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
void draw_attack_indicator(Elements *p1, ALLEGRO_COLOR color) {
    Character *chara = (Character *)(p1->pDerivedObj);
    float angle_deg = chara->atk_angle;
    
    if (!chara->dir) angle_deg = 180.0f - angle_deg;
    float angle_rad = angle_deg * (3.14159f / 180.0f);
    float power_scale = chara->atk_power * 5; // you can scale this further if needed

    int x = chara->x + chara->width / 2;
    int y = chara->y + chara->height / 2 - 16;
    if (!chara->dir) {
        x -= 48;
    } else {
        x += 48;
    }

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
        color
    );
}