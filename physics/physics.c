#include "physics.h"

#include "../element/character.h"
#include "../physics/gravity.h"
#include "../physics/collision.h"
#include "../scene/sceneManager.h"

void Contact_Check_To_Character(Elements *self) {
    Character   *chara = (Character *)(self->pDerivedObj);
    ElementVec  ground_elements = _Get_label_elements(scene, Ground_L);
    
    Contact_Compute_Hitbox(
        chara->hitbox, 
        &chara->contact, 
        &ground_elements
    );
}

void Movement_Physics_To_Character(Elements *self) {
    Character *chara = (Character *)self->pDerivedObj;

    // Handle horizontal collisions (walls, ledges)
    Physics_Apply_Collision(
        &chara->vx,
        &chara->is_in_air,
        self, 
        chara->hitbox,
        &chara->contact,
        _Character_update_position
    );

    // Apply vertical movement (gravity, ceiling/floor)
    Physics_Apply_Gravity(
        &chara->vy,
        &chara->is_in_air,
        self,
        chara->hitbox,
        &chara->contact,
        _Character_update_position
    );
}