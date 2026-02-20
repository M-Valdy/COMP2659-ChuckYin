#include "w-swim.h";
#include "raster.h";
#include "Chuck.h";

// @author Paolo
#define SWIMMER_HEIGHT 32
const unsigned long womenSwimming_forward_bitmap[SWIMMER_HEIGHT] =
{
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x001FF800, 
    0x003FFC00, 
    0x007FFE00, 
    0x01FFFF80, 
    0x03FFFFC0, 
    0x03FFFFC0, 
    0x03FFFFC0, 
    0x07FFFFE0, 
    0x0FC7E3F0, 
    0x0F8001F0,
    0x0F8001F0, 
    0x0F0000F0, 
    0x0D1818B0, 
    0x1D1818B8, 
    0x1D0000B8, 
    0x1F0000F8, 
    0x1F0000F8, 
    0x3F0000FC, 
    0x7F83C1FE, 
    0xFFC003FF, 
    0xFFE007FF, 
    0xFFF00FFF, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000
};

// @author Paolo
const unsigned long womenSwimming_backward_bitmap[SWIMMER_HEIGHT] =
{
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x001FF800, 
    0x003FFC00, 
    0x007FFE00, 
    0x01FFFF80, 
    0x03FFFFC0, 
    0x07FFFFE0, 
    0x07FFFFE0, 
    0x07FFFFE0, 
    0x0FFFFFF0, 
    0x0FFFFFF0,
    0x0FFFFFF0, 
    0x0FFFFFF0, 
    0x0FFFFFF0, 
    0x1FFFFFF8, 
    0x1FFFFFF8, 
    0x1FFFFFF8, 
    0x1FFFFFF8, 
    0x3FFFFFFC, 
    0x7FFFFFFE, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000
};

// @author Meagan
void initWomenSwimming(WomenSwimming* womenSwimming, unsigned int x, unsigned int y) {
    womenSwimming->x = x;
    womenSwimming->y = y;
    womenSwimming->deltaX = 0;
    womenSwimming->deltaY = 0;
}

// @author Meagan & Paolo
void updateWomenSwimming(WomenSwimming* womenSwimming) {
    /*while ((womenSwimming->deltaX != 0 || womenSwimming->deltaY != 0) 
    && px_in_bounds(womenSwimming->x, womenSwimming->y)) {
        womenSwimming->x += womenSwimming->deltaX;
        womenSwimming->y += womenSwimming->deltaY;
    }*/ 
    womenSwimming->frameCount++;
    if (womenSwimming->frameCount == 70 && womenSwimming->isForward == 1) {
        womenSwimming->isForward = 0; // Switch to backward bitmap after 70 frames
    } else if (womenSwimming->frameCount == 70 && womenSwimming->isForward == 0) {
        womenSwimming->isForward = 1; // Switch to forward bitmap after 70 frames
    }
    
    
}

// @author Meagan
void collisionWomenSwimming(WomenSwimming* womenSwimming, Chuck* chuck) {
    if (womenSwimming->x == chuck->x && womenSwimming->y == chuck->y && womenSwimming->isForward == 1) {
        // womenSwimming collides with Chuck, stop movement
        womenSwimming->deltaX = 0;
        womenSwimming->deltaY = 0;
        chuck->isWalking = 0; // Stop Chuck from walking
        chuck->isColliding = 2; // Set collision flag for Chuck
        womenSwimming->isColliding = 1;
    }
}

// @author Paolo
void render_womenSwimming(WomenSwimming* womenSwimming) {
    // TO DO
}