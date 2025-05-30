#include "floor.h"
#include "character.h"
#include "projectile.h"
#include "../scene/gamescene.h" // for element label
#include "../scene/sceneManager.h" // for scene variable
#include "../shapes/Rectangle.h"
#include <stdio.h>
#include <allegro5/allegro_primitives.h>

/*
   [floor function]
*/
Elements *New_Floor(int label)
{
    Floor *pDerivedObj = (Floor *)malloc(sizeof(Floor));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = NULL; // No image used, we draw a rectangle
    pDerivedObj->width = 4000;
    pDerivedObj->height = 10;
    pDerivedObj->x = -1500;
    pDerivedObj->y = 1100;
    pDerivedObj->hitbox = New_Rectangle(
        pDerivedObj->x, 
        pDerivedObj->y, 
        pDerivedObj->x + pDerivedObj->width, 
        pDerivedObj->y + pDerivedObj->height
    );

    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Player1_L;
    pObj->inter_obj[pObj->inter_len++] = Player2_L;
    pObj->inter_obj[pObj->inter_len++] = Projectile_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Floor_draw;
    pObj->Update = Floor_update;
    pObj->Interact = Floor_interact;
    pObj->Destroy = Floor_destory;

    return pObj;
}

void Floor_update(Elements *ele) {}

void Floor_interact(Elements *self)
{
    for (int j = 0; j < self->inter_len; j++) {
        int inter_label = self->inter_obj[j];
        ElementVec labelEle = _Get_label_elements(scene, inter_label);

        for (int i = 0; i < labelEle.len; i++) {
            Elements *target = labelEle.arr[i];
            if (inter_label == Player2_L || inter_label == Player1_L) {
                _Floor_interact_Character(self, target);
            }

            if (inter_label == Projectile_L) {
                _Floor_interact_Ground(self, target);
            }
        }
    }
}

void _Floor_interact_Character(Elements *self, Elements *tar)
{
    Floor *floor = (Floor *)(self->pDerivedObj);
    Character *chara = (Character *)(tar->pDerivedObj);

    // Check rectangle collision
    if (floor->hitbox->overlap(floor->hitbox, chara->hitbox))
    {
        chara->hp = 0;
    }
}
void _Floor_interact_Ground(Elements *self, Elements *target)
{
    Floor *floor = (Floor *)(self->pDerivedObj);
    Projectile *proj = (Projectile *)(target->pDerivedObj);

    // Check rectangle collision
    if (floor->hitbox->overlap(floor->hitbox, proj->hitbox))
    {
        proj->durability = 0;
    }
}
void Floor_draw(Elements *self)
{
    Floor *Obj = ((Floor *)(self->pDerivedObj));
    al_draw_filled_rectangle(
        Obj->x,
        Obj->y,
        Obj->x + Obj->width,
        Obj->y + Obj->height,
        al_map_rgb(128, 128, 128)
    );
}

void Floor_destory(Elements *self)
{
    Floor *Obj = ((Floor *)(self->pDerivedObj));
    if (Obj->img)
        al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
