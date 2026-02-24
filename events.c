#include "events.h"

void event_handler(Model *model) {
    while (model->gameOver == 0) {
        asynch_button_W(model);
        asynch_button_A(model);
        asynch_button_S(model);
        asynch_button_D(model);
        
        synch_update(model);
        cond_update(model);
    }
}