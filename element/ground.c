#include "ground.h"
#include "../shapes/Rectangle.h"
#include <stdio.h>
#include <allegro5/allegro_primitives.h>

Elements *New_Ground(int who, int label)
{
    Ground *pDerivedObj = (Ground *)malloc(sizeof(Ground));
    Elements *pObj = New_Elements(label);
    
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;

    const char *image_path  = NULL;
    const char *mask_path   = NULL;

    if (who == 0)
    {
        image_path = "assets/maps/white_house_ground.png";
        mask_path  = "assets/maps/white_house_mask.txt";
    }
    else if (who == 1)
    {
        image_path = "assets/maps/tiananmen_square_ground.png";
        mask_path  = "assets/maps/tiananmen_square_mask.txt";
    } else 
    {
        image_path = "assets/maps/101_ground.png";
        mask_path  = "assets/maps/101_mask.txt";
    }

    // Load image
    ALLEGRO_BITMAP *original = al_load_bitmap(image_path);
    if (!original) {
        fprintf(stderr, "Failed to load image: %s\n", image_path);
        exit(1);
    }

    // Convert to writable format (important!)
    pDerivedObj->tileset = al_clone_bitmap(original);
    al_destroy_bitmap(original);

    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->tileset);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->tileset);

    // Load tile_mask from text file
    FILE *mask_file = fopen(mask_path, "r");
    if (!mask_file) {
        fprintf(stderr, "Failed to load mask file: %s\n", mask_path);
        exit(1);
    }

    int value;
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            fscanf(mask_file, "%d", &value);
            pDerivedObj->active[i][j] = (value == 1);
        }
    }
    fclose(mask_file);

    // Slice tilemap into individual tiles
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            int tx = j * TILE_WIDTH;
            int ty = i * TILE_HEIGHT;

            if (pDerivedObj->active[i][j]) {
                pDerivedObj->hitboxes[i][j] = New_Rectangle(
                    pDerivedObj->x + tx,
                    pDerivedObj->y + ty,
                    pDerivedObj->x + tx + TILE_WIDTH,
                    pDerivedObj->y + ty + TILE_HEIGHT
                );

            } else {
                pDerivedObj->hitboxes[i][j] = NULL;
            }
        }
    }

    // Assign to base class
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Ground_update;
    pObj->Interact = Ground_interact;
    pObj->Draw = Ground_draw;
    pObj->Destroy = Ground_destory;

    return pObj;
}
void Ground_update(Elements *self) {
    // No behavior for now
}
void Ground_interact(Elements *self) {
    // Interaction is handled externally (e.g., by projectile or character)
}
void Ground_draw(Elements *self) {
    Ground *Obj = (Ground *)(self->pDerivedObj);

    al_draw_bitmap(Obj->tileset, Obj->x, Obj->y, 0);
}
void Ground_destory(Elements *self) {
    Ground *Obj = (Ground *)(self->pDerivedObj);

    al_destroy_bitmap(Obj->tileset);

    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            if (Obj->hitboxes[i][j])
                free(Obj->hitboxes[i][j]);
        }
    }

    free(Obj);
    free(self);
}
void Ground_Erase_Tile(Ground *ground, int row, int col) {
    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS) return;
    if (!ground->active[row][col]) return;

    // Set target drawing to the tileset bitmap
    al_set_target_bitmap(ground->tileset);

    int tx = col * TILE_WIDTH;
    int ty = row * TILE_HEIGHT;

    // Set blend mode to replace pixels (no blending)
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);
    ALLEGRO_COLOR transparent = al_map_rgba(0, 0, 0, 0);
    al_draw_filled_rectangle(tx, ty, tx + TILE_WIDTH, ty + TILE_HEIGHT, transparent);
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
    al_set_target_backbuffer(al_get_current_display());

    // Remove hitbox
    if (ground->hitboxes[row][col]) {
        free(ground->hitboxes[row][col]);
        ground->hitboxes[row][col] = NULL;
    }

    ground->active[row][col] = 0;
}