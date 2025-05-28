#include "collision.h"

void Physics_Apply_Collision(float             *vx, 
                             bool              *in_air,
                             float             *bounce_decay,
                             Elements          *self, 
                             Shape             *hitbox,
                             const ContactInfo *contact,
                             void (*update_pos)(Elements*, int, int)
                            ) 
{
    if (!vx || !self || !hitbox || !contact || !update_pos)
        return;

    int move_x = (int)(*vx);
    if (move_x == 0) return;

    int original_x   = (int)(hitbox->get_left(hitbox));
    int right_edge   = (int)(hitbox->get_right(hitbox));
    int bottom       = (int)(hitbox->get_bottom(hitbox));
    int top          = (int)(hitbox->get_top(hitbox));
    int height       = bottom - top;

    int next_left    = original_x + move_x;
    int next_right   = right_edge + move_x;

    // ─── Moving RIGHT ───
    if (move_x > 0 &&
        contact->wall_right_x != -1 &&
        contact->wall_right_x >= right_edge &&
        contact->wall_right_x <= next_right) 
    {
        int wall_height = bottom - contact->wall_right_y;

        if (wall_height >= height / 2) {
            int new_x = contact->wall_right_x - (right_edge - original_x);
            update_pos(self, new_x - original_x, 0);
            *vx = -*vx * *bounce_decay;
            if (fabs(*vx) < 0.5f) *vx = 0.0f;
        } else if (!*in_air && wall_height > 0) {
            update_pos(self, move_x, -wall_height);  // Step up
        }
    }

    // ─── Moving LEFT ───
    else if (move_x < 0 &&
             contact->wall_left_x != -1 &&
             contact->wall_left_x <= original_x &&
             contact->wall_left_x >= next_left) 
    {
        int wall_height = bottom - contact->wall_left_y;

        if (wall_height >= height / 2) {
            int new_x = contact->wall_left_x;
            update_pos(self, new_x - original_x, 0);
            *vx = -*vx * *bounce_decay;
            if (fabs(*vx) < 0.5f) *vx = 0.0f;
        } else if (!*in_air && wall_height > 0) {
            update_pos(self, move_x, -wall_height);
        }
    }

    // ─── No wall: just move ───
    else {
        update_pos(self, move_x, 0);
    }
}