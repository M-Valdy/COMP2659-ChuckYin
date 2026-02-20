#include "events.h"
#include "asynch.h"
#include "synch.h"
#include "cond.h"

void event_handler(Model *model) {
    int gameOver = 0; // Placeholder for game over condition

    while (gameOver == 0) {
        asynch_button_W(model);
        asynch_button_A(model);
        asynch_button_S(model);
        asynch_button_D(model);
        synch_update(model);
        cond_update(model);
    }
}