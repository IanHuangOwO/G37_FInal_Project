#include "ultimate.h"

#define ULTIMATE_IMG_PATH "assets/particle/ultimate.gif"
#define ULTIMATE_DURATION -1

void Ultimate_Initialize(Particle *par) {
    par->gif        = algif_new_gif(ULTIMATE_IMG_PATH, -1);
    par->width      = par->gif->width;
    par->height     = par->gif->height;
    par->duration   = ULTIMATE_DURATION;
}