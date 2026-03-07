#include <stdio.h>
#include "model.h"
#include "cond.h"
#include "asynch.h"
#include "synch.h"

/* @author Paolo */
void checkLand(Model *model){
    int k = 0;
    printf("================================================================================\n");
    for (k = 0; k < 20; k++) {   
        printf("Road[%d]: %d, %d.        Road[%d]: %d, %d.\n", k, model->road[k].x, model->road[k].y, k+20, model->road[k+20].x, model->road[k+20].y);
    }
    printf("================================================================================\n");
}

/* @author Paolo */
void checkSynch(Model *model) {
    int h = 0;
    printf("================================================================================\n");

    for (h = 0; h < 4; h++) {
        synch_update(model);
        printf("Walker/Swimmer after update:\n");
        printf("Walker [%d] x/y: (%d, %d)\n", 0, model->womenWalking[0].x, model->womenWalking[0].y);
        /*printf("Walker [%d] x/y: (%d, %d)\n", 1, model->womenWalking[1].x, model->womenWalking[1].y);
        printf("Walker [%d] x/y: (%d, %d)\n", 2, model->womenWalking[2].x, model->womenWalking[2].y);*/
        printf("Swimmer [%d] frameCount/isForward: (%d, %d)\n", 0, model->womenSwimming[0].frameCount, model->womenSwimming[0].isForward);
        /*printf("Swimmer [%d] frameCount/isForward: (%d, %d)\n", 1, model->womenSwimming[1].frameCount, model->womenSwimming[1].isForward);
        printf("Swimmer [%d] frameCount/isForward: (%d, %d)\n", 2, model->womenSwimming[2].frameCount, model->womenSwimming[2].isForward);*/
    }

    printf("================================================================================\n");
}

/* @author Paolo */
void checkAsynch(Model *model) {
    printf("================================================================================\n");

    printf("Chuck's initial position: (%d, %d)\n", model->chuck.x, model->chuck.y);
    asynch_button_W(model);
    updateChuck(&model->chuck); 
    printf("Chuck's position after moving up: (%d, %d)\n", model->chuck.x, model->chuck.y);
    asynch_button_A(model);
    updateChuck(&model->chuck); 
    printf("Chuck's position after moving left: (%d, %d)\n", model->chuck.x, model->chuck.y);
    asynch_button_S(model);
    updateChuck(&model->chuck); 
    printf("Chuck's position after moving down: (%d, %d)\n", model->chuck.x, model->chuck.y);
    asynch_button_D(model);
    updateChuck(&model->chuck); 
    printf("Chuck's position after moving right: (%d, %d)\n", model->chuck.x, model->chuck.y);

    printf("================================================================================\n");
}

/* @author Paolo */
void checkCond(Model *model) {
    printf("================================================================================\n");

    printf("Cross count currently: %d\n", model->crossCount);
    model->chuck.y = 8;
    cond_update(model);
    printf("Cross count after: %d\n", model->crossCount);
    printf("Current gameOver value:  %d\n", model->gameOver);
    printf("Chuck's Y coordinate is: %d\n", model->chuck.y);
    
    printf("================================================================================\n");
}

/* @author Paolo */
void checkCond2(Model *model) {
    printf("================================================================================\n");

    model->chuck.x = 50;
    printf("Chuck's current position: (%d, %d)\n", model->chuck.x, model->chuck.y);
    printf("Cross count before: %d\n", model->crossCount);
    model->womenWalking[0].x = model->chuck.x;
    model->womenWalking[0].y = model->chuck.y;
    cond_update(model);
    printf("Chuck->isColliding: %d\n", model->chuck.isColliding);
    cond_update(model);
    printf("Chuck's position after collision: (%d, %d)\n", model->chuck.x, model->chuck.y);
    printf("Cross count after: %d\n", model->crossCount);

    printf("================================================================================\n");
}

/* @author Paolo */
int main() {
    char userInput = 'a';
    Model modelTestDriver;
    Model_init(&modelTestDriver);
    while (userInput != '0') {
        printf(" [0] to exit.\n [1] to check land initialization coordinates.\n [2] to check if asynchronous events work.\n [3] to see if synchronous events work.\n [4] to check if crossing conditional works.\n [5] to check if collision conditional works.\n");
        scanf(" %c", &userInput);
        if (userInput == '1') {
            checkLand(&modelTestDriver);
        } else if (userInput == '2') {
            checkAsynch(&modelTestDriver);
        } else if (userInput == '3') {
            checkSynch(&modelTestDriver);
        } else if (userInput == '4') {
            checkCond(&modelTestDriver);
        } else if (userInput == '5') {
            checkCond2(&modelTestDriver);
        }
    }
    return 0;
}