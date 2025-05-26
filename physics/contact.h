// contact.h
#ifndef CONTACT_H
#define CONTACT_H

#include "../element/ground.h"

typedef struct ContactInfo {
    int wall_bot_y;      // top Y of tile directly below
    int wall_top_y;      // bottom Y of tile directly above
    int wall_left_x;     // right X of tile to the left
    int wall_right_x;    // left X of tile to the right
    int wall_left_y;     // top Y of tile to the left
    int wall_right_y;    // top Y of tile to the right
} ContactInfo;

// Computes contact info for a given element and ground tile layer
void Contact_Compute_Hitbox(
    Shape *hitbox, 
    ContactInfo *info, 
    ElementVec *ground_elements
);

#endif