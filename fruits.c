#include "fruits.h";
#include "Chuck.h";

#define FRUITS_HEIGHT 16
int fruits_bitmap[FRUITS_HEIGHT] =
{
    0x0000, 
    0x0000, 
    0x0000, 
    0x0000, 
    0x0000, 
    0x0000, 
    0x0000, 
    0x0000, 
    0x0000, 
    0x0000, 
    0x0000, 
    0x0000, 
    0x0000, 
    0x0000, 
    0x0000, 
    0x0000 
}; // TO DO tomorrow

void initFruits(Fruits* fruits, unsigned int x, unsigned int y) {
    fruits->x = x;
    fruits->y = y;
    fruits->isGathered = 0;
}

void isChuckCollidingWithFruits(Fruits* fruits, Chuck* chuck) {
    // TO DO tomorrow

    // comment from Meagan: are you gonna add a collision state for Chuck? 
    // like isColliding = 1 for obstacle collision, isColliding = 0 for no collision, 
    // and isColliding = 2 for death collision?. Or are you adding another one

    // if (chuck is colliding with fruits) { fruits->isGathered = 1 }
}