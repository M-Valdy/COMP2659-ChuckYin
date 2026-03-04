#include <stdio.h>
#include "model.h"
#include "cond.h"
#include "asynch.h"
#include "synch.h"
#include "renderer.h"

/* @author Paolo */
int main() {
    void *base = Physbase();
    char userInput = 'h';
    Model renderTestDriver;
    Model_init(&renderTestDriver);
    while (userInput != '0') {
        synch_update(&renderTestDriver);
        cond_update(&renderTestDriver);
        master_render(&renderTestDriver, base);
        scanf(" %c", &userInput);
        if (userInput == 'w') {
            asynch_button_W(&renderTestDriver);
        } else if (userInput == 'a') {
            asynch_button_A(&renderTestDriver);
        } else if (userInput == 's') {
            asynch_button_S(&renderTestDriver);
        } else if (userInput == 'd') {
            asynch_button_D(&renderTestDriver);
        }
        clear_screen(base);
    }
    return 0;
}