#include "synch.h"
#include "model.h"

void synch_update(Model *model) {
    updateChuck(&model->chuck);
    for (int i = 0; i < 15; i++) {
        updateWomenWalking(&model->womenWalking[i]);
        updateWomenSwimming(&model->womenSwimming[i]);
    }
    
}