#include "jingping_pic.h"

#define JINGPING_PIC_IMG_PATH "assets/particles/jingping_pic.gif"
#define JINGPING_PIC_DURATION 300

void JingPing_Pic_Initialize(Particle *par) {
    par->gif        = algif_new_gif(JINGPING_PIC_IMG_PATH, -1);
    par->width      = par->gif->width;
    par->height     = par->gif->height;
    par->duration   = JINGPING_PIC_DURATION;
}