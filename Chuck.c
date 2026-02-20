#include "Chuck.h"
#include "water.h"

/*
    @author Paolo
    This is the bitmap that contains the dimensions of the Chuck sprite
    which will be used for rendering and collision detection
*/
#define CHUCK_HEIGHT 32
const unsigned long Chuck_bitmap[CHUCK_HEIGHT] =
{
    0x00000000, 
    0x003FFC00, 
    0x007FFE00, 
    0x00FFFF00, 
    0x01E3C780, 
    0x03DC3BC0, 
    0x03BFFDC0, 
    0x037FFEC0, 
    0x0367E6C0, 
    0x0367E6C0, 
    0x037FFEC0, 
    0x02FFFF40, 
    0x01FFFF80, 
    0x01FC3F80, 
    0x00FFFF00, 
    0x00FFFF00,
    0x007FFE00, 
    0x001FF800, 
    0x000FF000, 
    0x003FFC00, 
    0x007FFE00, 
    0x006FF600, 
    0x006FF600, 
    0x006FF600, 
    0x006FF600, 
    0x006FF600, 
    0x006C3600, 
    0x000C3000, 
    0x000C3000, 
    0x000C3000, 
    0x000C3000, 
    0x00000000
};

// @author Meagan
// function for initializing Chuck's position and state
void initChuck(Chuck* chuck, unsigned int x, unsigned int y) {
    chuck->x = x;
    chuck->y = y;
    chuck->isWalking = 0;
    chuck->isColliding = 0;
    chuck->deltaX = 0;
    chuck->deltaY = 0;
    chuck->canMoveLeft = 1;
    chuck->canMoveRight = 1;
    chuck->canMoveUp = 1;
    chuck->canMoveDown = 1;
}

// @author Meagan
// function for starting Chuck's walking in a specified direction
void startWalking(Chuck* chuck, int deltaX, int deltaY) {
    chuck->isWalking = 1;
    chuck->deltaX = deltaX;
    chuck->deltaY = deltaY;
}

// @author Meagan & Paolo
// function for updating Chuck's position based on his walking state
void updateChuck(Chuck* chuck) {
    if (chuck->isWalking) {
        // check if he's allowed to move there first.
        if (chuck->canMoveRight == 0 && chuck->deltaX > 0) {
            chuck->deltaX = 0;  
        }
        if (chuck->canMoveLeft == 0 && chuck->deltaX < 0) {
            chuck->deltaX = 0;
        }
        if (chuck->canMoveUp == 0 && chuck->deltaY < 0) {
            chuck->deltaY = 0;
        }
        if (chuck->canMoveDown == 0 && chuck->deltaY > 0) {
            chuck->deltaY = 0;
        }

        chuck->x += chuck->deltaX;
        chuck->y += chuck->deltaY;
    }
}

// @author Meagan
// function for stopping Chuck's walking
void stopWalking(Chuck* chuck) {
    chuck->isWalking = 0;
    chuck->deltaX = 0;
    chuck->deltaY = 0;
}

// @author Paolo
// if Chuck's right edge is touching the left edge of the water, then can't move right
void checkRightCollision(Chuck* chuck, Water* water) {
    if (chuck->x + 32 == water->x) { 
        chuck->canMoveRight = 0;
    } else {
        chuck->canMoveRight = 1;
    }
}

// @author Paolo 
// if Chuck's left edge is touching the right edge of the water, then can't move right
void checkLeftCollision(Chuck* chuck, Water* water) {
    if (chuck->x == water->x + 32) { 
        chuck->canMoveLeft = 0;
    } else {
        chuck->canMoveLeft = 1;
    }
}

// @author Paolo
// if Chuck's top edge is touching the bottom edge of the water, then can't move up   
void checkUpCollision(Chuck* chuck, Water* water) {
    if (chuck->y == water->y - 32) { 
        chuck->canMoveUp = 0;
    } else {
        chuck->canMoveUp = 1;
    }
}

// @author Paolo
// if Chuck's bottom edge is touching the top edge of the water, then can't move down
void checkDownCollision(Chuck* chuck, Water* water) {
    if (chuck->y - CHUCK_HEIGHT == water->y) { 
        chuck->canMoveDown = 0;
    } else {
        chuck->canMoveDown = 1;
    }
}

