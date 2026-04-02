#include "asynch.h"

/* @author Paolo */
void asynch_button_W(Model *model) {
    if (model->chuck.y-CHUCK_SPEED > 0) {
        startWalking(&model->chuck, 0, -1*CHUCK_SPEED); /* Move Chuck up */ 
        /*play_chuck_walking();*/
    } else {
        /*model->chuck.y = 0; */
        stopWalking(&model->chuck);
    }
}

/* @author Paolo */
void asynch_button_A(Model *model) {
    if (model->chuck.x-CHUCK_SPEED > 0 ) {
        startWalking(&model->chuck, -1*CHUCK_SPEED, 0); /* Move Chuck left */ 
        /*play_chuck_walking();*/
    } else {
        /*model->chuck.x = 0; */
        stopWalking(&model->chuck);
    }
}

/* @author Paolo */
void asynch_button_S(Model *model) {
    if (model->chuck.y+CHUCK_SPEED < 400) {
        startWalking(&model->chuck, 0, CHUCK_SPEED); /* Move Chuck down */ 
        /*play_chuck_walking();*/
    } else {
        /*model->chuck.y = 400-CHUCK_HEIGHT; */
        stopWalking(&model->chuck);
    }
}

/* @author Paolo */
void asynch_button_D(Model *model) {
    if (model->chuck.x+CHUCK_SPEED < 640) {
        startWalking(&model->chuck, CHUCK_SPEED, 0); /* Move Chuck right */   
        /*play_chuck_walking(); */
    } else {
        /*model->chuck.x = 640-CHUCK_HEIGHT;*/
        stopWalking(&model->chuck);
    }
}

/* @author Paolo */
void asynch_button_X(Model *model) {
    stopWalking(&model->chuck); /* Stop Chuck from moving */
}

/* @author Paolo */
void asynch_button_P(Model *model) {
    model->gameOver = 3;
    stop_sound();
}