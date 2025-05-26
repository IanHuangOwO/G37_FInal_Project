// gravity.h

#ifndef GRAVITY_H
#define GRAVITY_H

#include "../physics/contact.h"

void Physics_Apply_Gravity(
    float   *p_vy,
    bool    *p_in_air,
    Elements *self,
    Shape *hitbox,
    const ContactInfo *contact,
    void (*update_pos)(Elements*, int, int)
);

#endif