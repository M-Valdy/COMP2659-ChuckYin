#include "cond.h"

/* @author Paolo  did the function bodies*/
void cond_update(Model *model) {
    int i;
    int h;
    
    if (model->chuck.isColliding == 1) {
        stopWalking(&model->chuck);
        play_touch_edge();
        model->chuck.isColliding = 0;
    } else if (model->chuck.isColliding == 2) {
        model->oldCrossCount = model->crossCount;
        play_women_collide();
        model->crossCount = 0;
        initChuck(&model->chuck, 320, 350); /* Reset Chuck to starting position to bottom middle of screen */
        model->chuck.deathCounter++;
    }
    /* Paolo's note: i didn't spend that much time trying to optimize this i just wanted it to work for now*/
    for (h = 0; h < 120; h++) { 
        isRoadCollidingChuck(&model->road[h], &model->chuck);
    }

    for (i = 0; i < 15; i++) {
        collisionWomenWalking(&model->womenWalking[i], &model->chuck);
    }
    
    for (i = 0; i < 30; i++) {
        collisionWomenSwimming(&model->womenSwimming[i], &model->chuck);
    }
    for (i = 0; i < 30; i++) {
        isWaterColliding(&model->water[i], &model->chuck);
    }
    
    if (model->chuck.y <= 16) { /* Send Chuck back to spawn point to cross again */
        model->crossCount++;
        initChuck(&model->chuck, 320, 350);
    }
    /* Chuck needs to cross the roads 5 times */
    if (model->crossCount == 4) { 
        model->gameOver = 1;
        play_chuck_win();
        model->oldCrossCount = model->crossCount;
        model->crossCount = 0;
    }

    /* TO DO: for loop for water col now*/
}