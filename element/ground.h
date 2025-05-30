#ifndef GROUND_H_INCLUDED
#define GROUND_H_INCLUDED

#include "element.h"
#include "../scene/gamescene.h"
#include "../shapes/Shape.h"

#define TILE_WIDTH 2
#define TILE_HEIGHT 2
#define MAP_COLS (1920 / 2)
#define MAP_ROWS (1080 / 2)

typedef struct _Ground {
    int x, y;
    int width, height;
    ALLEGRO_BITMAP *tileset;
    ALLEGRO_BITMAP *tiles[MAP_ROWS][MAP_COLS];
    bool active[MAP_ROWS][MAP_COLS];
    bool dirty[MAP_ROWS][MAP_COLS];
    Shape *hitboxes[MAP_ROWS][MAP_COLS];
} Ground;

Elements *New_Ground(int who, int label);

void Ground_update(Elements *self);
void Ground_interact(Elements *self);
void Ground_draw(Elements *self);
void Ground_destory(Elements *self);
void Ground_Erase_Tile(Ground *ground, int i, int j);

#endif