#include "w-walk.h"
#include "raster.h"
#include "Chuck.h"

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

// @author Meagan & Paolo
void updateWomenWalking(WomenWalking* womenWalking) {
    // Update the position of the walking woman based on her deltaX and deltaY
    /*while ((womenWalking->deltaX != 0 || womenWalking->deltaY != 0) 
    && px_in_bounds(womenWalking->x, womenWalking->y)) {
        womenWalking->x += womenWalking->deltaX;
        womenWalking->y += womenWalking->deltaY;
    }*/

    if (womenWalking->x + 32 >= 640) {
        womenWalking->deltaX = -1; // Move left
    } else if (womenWalking->x <= 0) {
        womenWalking->deltaX = 1; // Move right
    }

    womenWalking->x += womenWalking->deltaX;
}

// @author Meagan
void collisionWomenWalking(WomenWalking* womenWalking, Chuck* chuck) {
    if (womenWalking->x == chuck->x && womenWalking->y == chuck->y) {
        // womenWalking collides with Chuck, stop movement
        womenWalking->deltaX = 0;
        womenWalking->deltaY = 0;
        stopWalking(chuck); // Stop Chuck from walking
        chuck->isColliding = 2; // Set death collision flag for Chuck
    }
}