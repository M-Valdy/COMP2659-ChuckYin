#include "women-swimming.h";
#include "raster.h";
#include "Chuck.h";


void initWomenSwimming(WomenSwimming* womenSwimming, unsigned int x, unsigned int y) {
    womenSwimming->x = x;
    womenSwimming->y = y;
    womenSwimming->deltaX = 0;
    womenSwimming->deltaY = 0;
}

void updateWomenSwimming(WomenSwimming* womenSwimming) {
    while ((womenSwimming->deltaX != 0 || womenSwimming->deltaY != 0) 
    && px_in_bounds(womenSwimming->x, womenSwimming->y)) {
        womenSwimming->x += womenSwimming->deltaX;
        womenSwimming->y += womenSwimming->deltaY;
    }
}

void collisionWomenSwimming(WomenSwimming* womenSwimming, Chuck* chuck) {
    if (womenSwimming->x == chuck->x && womenSwimming->y == chuck->y) {
        // womenSwimming collides with Chuck, stop movement
        womenSwimming->deltaX = 0;
        womenSwimming->deltaY = 0;
        chuck->isWalking = 0; // Stop Chuck from walking
        chuck->isColliding = 2; // Set collision flag for Chuck
    }
}