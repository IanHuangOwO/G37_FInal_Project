#include "particle.h"
#include "../particle/ultimate.h"
#include "../particle/tentacle.h"

/*
   [particle function]
*/
Elements *New_Particle(int label, int x, int y, int who)
{
    Particle *pDerivedObj = (Particle *)malloc(sizeof(Particle));
    Elements *pObj = New_Elements(label);
    // setting who
    switch (who) {
        case ULTIMATE:
            Ultimate_Initialize(pDerivedObj);
            break;
        case TENTACLE:
            Tentacle_Initialize(pDerivedObj);
            break;
        default:
            // Optional: handle unknown values
            fprintf(stderr, "Unknown 'who' value: %d\n", who);
            break;
    }
    pDerivedObj->who = label;
    pDerivedObj->x = x - pDerivedObj->width / 2;
    pDerivedObj->y = y - pDerivedObj->height / 2;;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Particle_update;
    pObj->Interact = Particle_interact;
    pObj->Draw = Particle_draw;
    pObj->Destroy = Particle_destory;
    return pObj;
}
void Particle_update(Elements *self) {
    Particle *par = ((Particle *)(self->pDerivedObj));
    if (par->duration == 0) {
        self->dele = true;
    } else if (par->duration > 0) {
        par->duration --;
    }
}
void Particle_interact(Elements *self) {}
void Particle_draw(Elements *self)
{
    Particle *par = ((Particle *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(par->gif, al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, par->x, par->y, 0);
    }
}
void Particle_destory(Elements *self)
{
    Particle *par = ((Particle *)(self->pDerivedObj));
    algif_destroy_animation(par->gif);
    free(par);
    free(self);
}