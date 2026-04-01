#include "cond.h"

/* @author Paolo */
void cond_update(Model *model) {
    int i;
    int h;
    
    /* This is probably gonna be for if youre walking on the edge now */
    if (model->chuck.isColliding == 1) {
        stopWalking(&model->chuck);
        model->chuck.isColliding = 0;
    } else if (model->chuck.isColliding == 2) {
        model->oldCrossCount = model->crossCount;
        model->crossCount = 0;
        /*model->chuck.oldx = model->chuck.x;
        model->chuck.oldy = model->chuck.y;*/
        initChuck(&model->chuck, 320, 350); /* Reset Chuck to starting position to bottom middle of screen */
        model->chuck.deathCounter++;
    }
    /* Paolo's note: i didn't spend that much time trying to optimize this i just wanted it to work for now*/

    for (i = 0; i < 15; i++) {
        collisionWomenWalking(&model->womenWalking[i], &model->chuck);
    }
    /*for (h = 0; h < 120; h++) { 
        for (i = 0; i < 15; i++) {
            collisionWomenWalking(&model->womenWalking[i], &model->chuck);
            if (&model->road[h].y == &model->womenWalking[i].y) {
                isRoadCollidingWalker(&model->road[h], &model->womenWalking[i]);
            }
        }
        isRoadCollidingChuck(&model->road[h], &model->chuck);
    }*/
    
    for (i = 0; i < 30; i++) {
        collisionWomenSwimming(&model->womenSwimming[i], &model->chuck);
    }
    
    if (model->chuck.y <= 16) { /* Send Chuck back to spawn point to cross again */
        model->crossCount++;
        initChuck(&model->chuck, 320, 350);
    }
    /* Chuck needs to cross the roads 5 times */
    if (model->crossCount == 4) { 
        model->gameOver = 1;
        model->oldCrossCount = model->crossCount;
        model->crossCount = 0;
    }

    /* TO DO: for loop for water col now*/
}