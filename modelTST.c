#include <stdio.h>
#include "model.h"
#include "cond.h"
#include "asynch.h"
#include "synch.h"

/* @author Paolo */
int main() {
    char userInput = '0';
    int i;
    int x;
    Model modelTestDriver;
    Model_init(&modelTestDriver);
    while (userInput == '0') {
        printf("================================================================================================\n");

        printf("Chuck's initial position: (%u, %u)\n", modelTestDriver.chuck.x, modelTestDriver.chuck.y);
        asynch_button_W(&modelTestDriver);
        updateChuck(&modelTestDriver.chuck); /* need to call updateChuck to see the change in position after starting to walk */
        printf("Chuck's position after moving up: (%u, %u)\n", modelTestDriver.chuck.x, modelTestDriver.chuck.y);
        asynch_button_A(&modelTestDriver);
        updateChuck(&modelTestDriver.chuck); /* need to call updateChuck to see the change in position after starting to walk */
        printf("Chuck's position after moving left: (%u, %u)\n", modelTestDriver.chuck.x, modelTestDriver.chuck.y);
        asynch_button_S(&modelTestDriver);
        updateChuck(&modelTestDriver.chuck); /* need to call updateChuck to see the change in position after starting to walk */
        printf("Chuck's position after moving down: (%u, %u)\n", modelTestDriver.chuck.x, modelTestDriver.chuck.y);
        asynch_button_D(&modelTestDriver);
        updateChuck(&modelTestDriver.chuck); /* need to call updateChuck to see the change in position after starting to walk */
        printf("Chuck's position after moving right: (%u, %u)\n", modelTestDriver.chuck.x, modelTestDriver.chuck.y);

        printf("================================================================================================\n");

        for (x = 0; x < 5; x++) {
            synch_update(&modelTestDriver);
            printf("Women walking positions after update:\n");
            for (i = 0; i < 15; i++) {
                printf("Woman %d: (%u, %u)\n", i, modelTestDriver.womenWalking[i].x, modelTestDriver.womenWalking[i].y);
            }
        }
        
        printf("================================================================================================\n");

        printf("Cross count currently: %d\n", modelTestDriver.crossCount);
        modelTestDriver.chuck.y = 8; /* Move Chuck to the top of the screen to simulate crossing */
        cond_update(&modelTestDriver);
        printf("Cross count after crossing: %d\n", modelTestDriver.crossCount);

        scanf(" %c", &userInput);
    } /* gcc -std=c89 -Wall -Wextra -pedantic modelTST.c model.c Chuck.c cond.c asynch.c synch.c w-walk.c w-swim.c road.c water.c -o modelTST.exe */
    return 0;
}