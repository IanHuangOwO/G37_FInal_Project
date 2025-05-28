#ifndef GROUND_H_INCLUDED
#define GROUND_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h"
#include "../shapes/Shape.h"

#define TILE_WIDTH 16
#define TILE_HEIGHT 16
#define MAP_COLS (1920 / 16)
#define MAP_ROWS (1080 / 16)

typedef struct _Ground {
    int x, y;
    int width, height;
    ALLEGRO_BITMAP *tileset;
    ALLEGRO_BITMAP *tiles[MAP_ROWS][MAP_COLS];
    bool active[MAP_ROWS][MAP_COLS];
    Shape *hitboxes[MAP_ROWS][MAP_COLS];
} Ground;

Elements *New_Ground(int who, int label);

void Ground_update(Elements *self);
void Ground_interact(Elements *self);
void Ground_draw(Elements *self);
void Ground_destory(Elements *self);

#endif