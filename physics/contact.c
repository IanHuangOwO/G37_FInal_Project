#include "contact.h"

void Contact_Compute_Hitbox(Shape *hitbox, ContactInfo *info, ElementVec *ground_elements) {
    if (!hitbox || !info || !ground_elements) return;

    float top    = hitbox->get_top(hitbox);
    float bottom = hitbox->get_bottom(hitbox);
    float left   = hitbox->get_left(hitbox);
    float right  = hitbox->get_right(hitbox);

    info->wall_top_y = -1;
    info->wall_bot_y = -1;
    info->wall_left_x = -1;
    info->wall_left_y = -1;
    info->wall_right_x = -1;
    info->wall_right_y = -1;

    bool floor_found = false;
    bool ceil_found = false;
    bool left_found = false;
    bool right_found = false;

    for (int i = 0; i < ground_elements->len; ++i) {
        Ground *ground = (Ground *)(ground_elements->arr[i]->pDerivedObj);

        // ───── Ceiling ─────
        if (!ceil_found) {
            int row_start = (int)((top - 1) / TILE_HEIGHT);
            if (row_start >= MAP_ROWS) row_start = MAP_ROWS - 1;
            if (row_start < 0) row_start = 0;

            int col_start = (int)(left / TILE_WIDTH);
            int col_end   = (int)((right - 1) / TILE_WIDTH);
            if (col_start < 0) col_start = 0;
            if (col_end >= MAP_COLS) col_end = MAP_COLS - 1;

            for (int row = row_start; row >= 0; --row) {
                for (int col = col_start; col <= col_end; ++col) {
                    if (!ground->active[row][col]) continue;
                    Shape *tile = ground->hitboxes[row][col];
                    info->wall_top_y = tile->get_bottom(tile);
                    ceil_found = true;
                    goto try_floor;
                }
            }
        }

    try_floor:

        // ───── Floor ─────
        if (!floor_found) {
            int row_start = (int)(bottom / TILE_HEIGHT);
            if (row_start < 0) row_start = 0;

            int col_start = (int)(left / TILE_WIDTH);
            int col_end   = (int)((right - 1) / TILE_WIDTH);
            if (col_start < 0) col_start = 0;
            if (col_end >= MAP_COLS) col_end = MAP_COLS - 1;

            for (int row = row_start; row < MAP_ROWS; ++row) {
                for (int col = col_start; col <= col_end; ++col) {
                    if (!ground->active[row][col]) continue;
                    Shape *tile = ground->hitboxes[row][col];
                    info->wall_bot_y = tile->get_top(tile);
                    floor_found = true;
                    goto try_left_wall;
                }
            }
        }

    try_left_wall:

        // ───── Left Wall (left-most + top-most) ─────
        if (!left_found) {
            int row_start = (int)(top / TILE_HEIGHT);
            int row_end   = (int)((bottom - 1) / TILE_HEIGHT);
            if (row_start < 0) row_start = 0;
            if (row_end >= MAP_ROWS) row_end = MAP_ROWS - 1;

            for (int col = (int)((left - 1) / TILE_WIDTH); col >= 0; --col) {
                for (int row = row_start; row <= row_end; ++row) {
                    if (!ground->active[row][col]) continue;
                    Shape *tile = ground->hitboxes[row][col];
                    info->wall_left_x = tile->get_right(tile);
                    info->wall_left_y = tile->get_top(tile);
                    left_found = true;
                    goto try_right_wall;
                }
            }
        }

    try_right_wall:

        // ───── Right Wall (right-most + top-most) ─────
        if (!right_found) {
            int row_start = (int)(top / TILE_HEIGHT);
            int row_end   = (int)((bottom - 1) / TILE_HEIGHT);
            if (row_start < 0) row_start = 0;
            if (row_end >= MAP_ROWS) row_end = MAP_ROWS - 1;

            for (int col = (int)(right / TILE_WIDTH); col < MAP_COLS; ++col) {
                for (int row = row_start; row <= row_end; ++row) {
                    if (!ground->active[row][col]) continue;
                    Shape *tile = ground->hitboxes[row][col];
                    info->wall_right_x = tile->get_left(tile);
                    info->wall_right_y = tile->get_top(tile);
                    right_found = true;
                    goto check_exit;
                }
            }
        }

    check_exit:
        if (floor_found && ceil_found && left_found && right_found)
            break;
    }
}