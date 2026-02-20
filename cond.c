#include "cond.h"

// @author Paolo
void cond_update(Model *model) {
    if (model->chuck.isColliding == 1) {
        stopWalking(&model->chuck);
    } else if (model->chuck.isColliding == 2) {
        initChuck(&model->chuck, 320, 350); // Reset Chuck to starting position to bottom middle of screen
    }

    for (int i = 0; i < 15; i++) {
        collisionWomenWalking(&model->womenWalking[i], &model->chuck);
        collisionWomenSwimming(&model->womenSwimming[i], &model->chuck);
    }
    // no collision detection needed for water, just prevent Chuck from walking into it instead
    // because Chuck wont be able to get on women swimming since he will die if water collision is chuck.isColliding == 2
    
    // TO DO: conditional event for winning... (getting to end goal)
}