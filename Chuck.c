#include "Chuck.h";

// @author Paolo
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
}

// @author Meagan
// function for starting Chuck's walking in a specified direction
void startWalking(Chuck* chuck, int deltaX, int deltaY) {
    chuck->isWalking = 1;
    chuck->deltaX = deltaX;
    chuck->deltaY = deltaY;
}

// @author Meagan
// function for updating Chuck's position based on his walking state
void updateChuck(Chuck* chuck) {
    if (chuck->isWalking) {
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
void render_Chuck(Chuck* chuck) {
    // TO DO
}

