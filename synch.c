#include "synch.h"
#include "model.h"

/* @author Paolo */
void synch_update(Model *model) {
    int i;
    updateChuck(&model->chuck);

    for (i = 0; i < 15; i++) {
        updateWomenWalking(&model->womenWalking[i]);
        updateWomenSwimming(&model->womenSwimming[i]);
    }
    
}