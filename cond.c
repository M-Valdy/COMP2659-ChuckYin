#include "cond.h"

/* @author Paolo */
void cond_update(Model *model) {
    int i;
    
    if (model->chuck.isColliding == 1) {
        stopWalking(&model->chuck);
        model->chuck.isColliding = 0;
    } else if (model->chuck.isColliding == 2) {
        model->crossCount = 0;
        initChuck(&model->chuck, 320, 350); /* Reset Chuck to starting position to bottom middle of screen */
    }

    for (i = 0; i < 15; i++) {
        collisionWomenWalking(&model->womenWalking[i], &model->chuck);
        collisionWomenSwimming(&model->womenSwimming[i], &model->chuck);
    }
    /* no collision detection needed for water, just prevent Chuck from walking into it instead
       because Chuck wont be able to get on women swimming since he will die if water collision is chuck.isColliding == 2 */
    
    if (model->chuck.y <= 16) { /* Send Chuck back to spawn point to cross again */
        model->crossCount++;
        initChuck(&model->chuck, 320, 350);
    }
    if (model->crossCount == 4) { /* Chuck needs to cross the roads 5 times */
        model->gameOver = 1;
        model->crossCount = 0;
    }
}