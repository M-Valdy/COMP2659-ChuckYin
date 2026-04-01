#include "synch.h"
#include "model.h"
#include "raster.h"

/* @author Paolo */
void synch_update(Model *model) {
    int i;
    updateChuck(&model->chuck);
    stopWalking(&model->chuck);
    for (i = 0; i < 30; i++) {
        if (i < 15) {
            updateWomenWalking(&model->womenWalking[i]);
        }
        updateWomenSwimming(&model->womenSwimming[i]);
    }
    
}