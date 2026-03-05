#include "asynch.h"

/* @author Paolo */
void asynch_button_W(Model *model) {
    startWalking(&model->chuck, 0, -10); /* Move Chuck up */
}

/* @author Paolo */
void asynch_button_A(Model *model) {
    startWalking(&model->chuck, -10, 0); /* Move Chuck left */ 
}

/* @author Paolo */
void asynch_button_S(Model *model) {
    startWalking(&model->chuck, 0, 10); /* Move Chuck down */ 
}

/* @author Paolo */
void asynch_button_D(Model *model) {
    startWalking(&model->chuck, 10, 0); /* Move Chuck right */
}