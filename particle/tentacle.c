#include "tentacle.h"

#define TANTACLE_IMG_PATH "assets/particles/tentacle.gif"
#define TANTACLE_DURATION 300

void Tentacle_Initialize(Particle *par) {
    par->gif        = algif_new_gif(TANTACLE_IMG_PATH, -1);
    par->width      = par->gif->width;
    par->height     = par->gif->height;
    par->duration   = TANTACLE_DURATION;
}