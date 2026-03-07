#include "asynch.h"

/* @author Paolo */
void asynch_button_W(Model *model) {
    startWalking(&model->chuck, 0, -6); /* Move Chuck up */
}

/* @author Paolo */
void asynch_button_A(Model *model) {
    startWalking(&model->chuck, -6, 0); /* Move Chuck left */ 
}

/* @author Paolo */
void asynch_button_S(Model *model) {
    startWalking(&model->chuck, 0, 6); /* Move Chuck down */ 
}

/* @author Paolo */
void asynch_button_D(Model *model) {
    startWalking(&model->chuck, 6, 0); /* Move Chuck right */
}

/* @author Paolo */
void asynch_button_X(Model *model) {
    stopWalking(&model->chuck); /* Stop Chuck from moving */
}

/* @author Paolo */
void asynch_button_P(Model *model) {
    model->gameOver = 1;
}