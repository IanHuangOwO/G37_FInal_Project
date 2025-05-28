#include "physics.h"

#include "../element/character.h"
#include "../element/projectile.h"

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
    Character   *chara = (Character *)self->pDerivedObj;

    // Handle horizontal collisions (walls, ledges)
    Physics_Apply_Collision(
        &chara->vx,
        &chara->is_in_air,
        &chara->bounce_decay,
        self, 
        chara->hitbox,
        &chara->contact,

        _Character_update_position
    );

    // Apply vertical movement (gravity, ceiling/floor)
    Physics_Apply_Gravity(
        &chara->vy,
        &chara->is_in_air,
        &chara->bounce_decay,
        self,
        chara->hitbox,
        &chara->contact,
        _Character_update_position
    );
}

void Contact_Check_To_Projectile(Elements *self, bool collision) {
    Projectile  *proj = (Projectile *)(self->pDerivedObj);
    ElementVec  ground_elements = _Get_label_elements(scene, Ground_L);
    
    if (collision)
    {
        Contact_Compute_Hitbox(
            proj->hitbox, 
            &proj->contact, 
            &ground_elements
        );
    }
    else
    {
        proj->contact.wall_bot_y = -1;
        proj->contact.wall_top_y = -1;
        proj->contact.wall_bot_y = -1;
        proj->contact.wall_left_x = -1;
        proj->contact.wall_left_y = -1;
        proj->contact.wall_right_x = -1;
        proj->contact.wall_right_y = -1;
    }
}

void Movement_Physics_To_Projectile(Elements *self, bool collision, bool gravity) {
    Projectile  *proj = (Projectile *)(self->pDerivedObj);

    if (collision)
    {
        // Handle horizontal collisions (walls, ledges)
        Physics_Apply_Collision(
            &proj->vx,
            &proj->is_in_air,
            &proj->bounce_decay,
            self, 
            proj->hitbox,
            &proj->contact,
            _Projectile_update_position
        );
    }
    else
    {
        _Projectile_update_position(self, proj->vx, 0);
    }

    if (gravity) 
    {
        // Apply vertical movement (gravity, ceiling/floor)
        Physics_Apply_Gravity(
            &proj->vy,
            &proj->is_in_air,
            &proj->bounce_decay,
            self,
            proj->hitbox,
            &proj->contact,
            _Projectile_update_position
        );
    }
    else
    {
        _Projectile_update_position(self, 0, proj->vy);
    }
    
}