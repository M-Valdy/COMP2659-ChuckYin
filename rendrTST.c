#include <stdio.h>
#include "model.h"
#include "cond.h"
#include "asynch.h"
#include "synch.h"
#include "renderer.h"
#include <osbind.h>

/* @author Paolo */
int main() {
    int i = 0;
    void *base = Physbase();
    char userInput = 'h';
    Model renderTestDriver;
    Model_init(&renderTestDriver);
    clear_screen(base);
    
    /*render_road(base, renderTestDriver.road[0].y, renderTestDriver.road[0].x, &renderTestDriver.road[0]);*/
    for (i = 0; i < 120; i++) {
        render_water(base, renderTestDriver.water[i].y, renderTestDriver.water[i].x, &renderTestDriver.water[i]);
        render_road(base, renderTestDriver.road[i].y, renderTestDriver.road[i].x, &renderTestDriver.road[i]);
    }
    for (i = 0; i < 15; i++) {
        render_WomenWalking(base, renderTestDriver.womenWalking[i].y, renderTestDriver.womenWalking[i].x, &renderTestDriver.womenWalking[i]);
        render_women_swimming(base, renderTestDriver.womenSwimming[i].y, renderTestDriver.womenSwimming[i].x, &renderTestDriver.womenSwimming[i]);
    }
    render_Chuck(base, renderTestDriver.chuck.y, renderTestDriver.chuck.x, &renderTestDriver.chuck);
    /*
    while (userInput != '0') {
        clear_screen(base);
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
    }*/
    return 0;
}