#ifndef COLLISION_H
#define COLLISION_H

#include "../physics/contact.h"

// Checks and applies sideways collision
// Stops movement if wall is too high, else steps up onto the wall
void Physics_Apply_Collision(
    float             *vx,
    bool              *in_air,
    Elements          *self, 
    Shape       *hitbox,
    const ContactInfo *contact,
    void (*update_pos)(Elements*, int, int)
);

#endif