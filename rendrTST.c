#include <stdio.h>
#include "model.h"
#include "cond.h"
#include "asynch.h"
#include "synch.h"
#include "renderer.h"

/* @author Paolo */
int main() {
    void *base = Physbase();
    char userInput = 'hi';
    int i;
    int x;
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
    } /* gcc -std=c89 -Wall -Wextra -pedantic rendrTST.c model.c Chuck.c cond.c asynch.c synch.c w-walk.c w-swim.c road.c water.c RAST_ASM.s -o rendrTST.exe */
    return 0;
}