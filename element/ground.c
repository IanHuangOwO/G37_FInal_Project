#include "ground.h"
#include "../shapes/Rectangle.h"
#include <stdio.h>

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
        image_path = "assets/map/white_house_ground.png";
        mask_path  = "assets/map/white_house_mask.txt";
    }
    else if (who == 1)
    {
        image_path = "assets/map/tiananmen_square_ground.png";
        mask_path  = "assets/map/tiananmen_square_mask.txt";
    }

    // Load image
    pDerivedObj->tileset = al_load_bitmap(image_path);
    if (!pDerivedObj->tileset) {
        fprintf(stderr, "Failed to load image: %s\n", image_path);
        exit(1);
    }

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

            pDerivedObj->tiles[i][j] = al_create_sub_bitmap(
                pDerivedObj->tileset, tx, ty, TILE_WIDTH, TILE_HEIGHT
            );

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

    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            if (!Obj->active[i][j]) continue;

            al_draw_bitmap(
                Obj->tiles[i][j],
                Obj->x + j * TILE_WIDTH,
                Obj->y + i * TILE_HEIGHT,
                0
            );
        }
    }
}
void Ground_destory(Elements *self) {
    Ground *Obj = (Ground *)(self->pDerivedObj);

    al_destroy_bitmap(Obj->tileset);

    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            if (Obj->tiles[i][j])
                al_destroy_bitmap(Obj->tiles[i][j]);

            if (Obj->hitboxes[i][j])
                free(Obj->hitboxes[i][j]);
        }
    }

    free(Obj);
    free(self);
}