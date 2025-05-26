#include "gravity.h"

#define GRAVITY           10
#define TERMINAL_VELOCITY 100

void Physics_Apply_Gravity(float              *vy,
                           bool               *in_air,
                           Elements           *self,
                           Shape              *hitbox,
                           const ContactInfo  *contact,
                           void (*update_pos)(Elements*, int, int))
{
    if (!vy || !in_air || !self || !hitbox || !contact || !update_pos)
        return;

    float dt = 1.0f / FPS;
    int move_y = (int)(*vy);

    int top        = (int)(hitbox->get_top(hitbox));
    int bottom     = (int)(hitbox->get_bottom(hitbox));
    int next_top   = top + move_y;
    int next_bottom= bottom + move_y;

    if (*in_air) {
        // ─── Ceiling collision ───
        if (*vy < 0 && contact->wall_top_y != -1 && next_top <= contact->wall_top_y) {
            int new_y = contact->wall_top_y;
            update_pos(self, 0, new_y - top);  // Align top
            *vy = 0;
            return;
        }

        // ─── Floor collision ───
        if (*vy > 0 && contact->wall_bot_y != -1 && next_bottom >= contact->wall_bot_y) {
            int new_y = contact->wall_bot_y - (bottom - top);  // Align bottom
            update_pos(self, 0, new_y - top);
            *vy = 0;
            *in_air = false;
            return;
        }

        // ─── No collision: apply movement ───
        update_pos(self, 0, move_y);

        if (*vy < TERMINAL_VELOCITY)
            *vy += GRAVITY * dt;
    }
    else {
        // ─── Start falling if no ground below ───
        if (contact->wall_bot_y == -1 || bottom < contact->wall_bot_y) {
            *in_air = true;
            *vy = GRAVITY * dt;
        }
    }
}