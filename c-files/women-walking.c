#include "women-walking.h";
#include "raster.h";

// @author Paolo
#define WALKER_HEIGHT 32
const unsigned long womenWalking_bitmap[WALKER_HEIGHT] =
{
    0xFFFFFFFF, 
    0xFFE007FF, 
    0xFF8181FF, 
    0xFF0E70FF, 
    0xFF1008FF, 
    0xFE20047F, 
    0xFE40027F, 
    0xFC80013F, 
    0xFD1818BF, 
    0xFD1818BF, 
    0xFE00007F, 
    0xFC00003F, 
    0xFC00003F, 
    0xFC03C03F, 
    0xFC00003F, 
    0xF900009F,
    0xFB8001DF, 
    0xF3E007CF, 
    0xE7F00FE7, 
    0xFFC003FF, 
    0xFF8001FF, 
    0xFF9009FF, 
    0xFF9009FF, 
    0xFF9009FF, 
    0xFF9009FF, 
    0xFF9009FF, 
    0xFF93C9FF, 
    0xFFF3CFFF, 
    0xFFF3CFFF, 
    0xFFF3CFFF, 
    0xFFF3CFFF, 
    0xFFFFFFFF
};

// @author Meagan
void initWomenWalking(WomenWalking* womenWalking, unsigned int x, unsigned int y) {
    womenWalking->x = x;
    womenWalking->y = y;
    womenWalking->deltaX = 0;
    womenWalking->deltaY = 0;
}

// @author Meagan
void updateWomenWalking(WomenWalking* womenWalking) {
    // Update the position of the walking woman based on her deltaX and deltaY
    while ((womenWalking->deltaX != 0 || womenWalking->deltaY != 0) 
    && px_in_bounds(womenWalking->x, womenWalking->y)) {
        womenWalking->x += womenWalking->deltaX;
        womenWalking->y += womenWalking->deltaY;
    }
}

// @author Meagan
void collisionWomenWalking(WomenWalking* womenWalking, Chuck* chuck) {
    if (womenWalking->x == chuck->x && womenWalking->y == chuck->y) {
        // womenWalking collides with Chuck, stop movement
        womenWalking->deltaX = 0;
        womenWalking->deltaY = 0;
        chuck->isWalking = 0; // Stop Chuck from walking
        chuck->isColliding = 1; // Set collision flag for Chuck
    }
}

// @author Paolo
void render_womenWalking(WomenWalking* womenWalking) {
    // TO DO
}