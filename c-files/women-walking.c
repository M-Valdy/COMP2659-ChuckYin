#include "women-walking.h";
#include "raster.h";

void initWomenWalking(WomenWalking* womenWalking, unsigned int x, unsigned int y) {
    womenWalking->x = x;
    womenWalking->y = y;
    womenWalking->deltaX = 0;
    womenWalking->deltaY = 0;
}

void updateWomenWalking(WomenWalking* womenWalking) {
    // Update the position of the walking woman based on her deltaX and deltaY
    while ((womenWalking->deltaX != 0 || womenWalking->deltaY != 0) 
    && px_in_bounds(womenWalking->x, womenWalking->y)) {
        womenWalking->x += womenWalking->deltaX;
        womenWalking->y += womenWalking->deltaY;
    }
}

void collisionWomenWalking(WomenWalking* womenWalking, Chuck* chuck) {
    if (womenWalking->x == chuck->x && womenWalking->y == chuck->y) {
        // womenWalking collides with Chuck, stop movement
        womenWalking->deltaX = 0;
        womenWalking->deltaY = 0;
        chuck->isWalking = 0; // Stop Chuck from walking
        chuck->isColliding = 2; // Set collision flag for Chuck
    }
}