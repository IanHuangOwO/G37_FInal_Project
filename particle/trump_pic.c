#include "trump_pic.h"

#define TRUMP_PIC_IMG_PATH "assets/particles/trump_pic.gif"
#define TRUMP_PIC_DURATION 300

void Trump_Pic_Initialize(Particle *par) {
    par->gif        = algif_new_gif(TRUMP_PIC_IMG_PATH, -1);
    par->width      = par->gif->width;
    par->height     = par->gif->height;
    par->duration   = TRUMP_PIC_DURATION;
}