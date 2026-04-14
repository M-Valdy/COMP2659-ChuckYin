#include "synch.h"

/* @author Paolo */
void synch_update(Model *model) {
    int i;
    updateChuck(&model->chuck);
    updateMouse(&model->mouse);
    stopWalking(&model->chuck);
    for (i = 0; i < NUM_SWIMMERS; i++) {
        updateWomenSwimming(&model->womenSwimming[i]);
    }
    for (i = 0; i < NUM_WALKERS; i++) {
        updateWomenWalking(&model->womenWalking[i]);
    }
}