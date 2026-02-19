#include "water.h";
#include "Chuck.h";

// @author Paolo
#define WATER_HEIGHT 32
const unsigned long water_bitmap[WATER_HEIGHT] =
{
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000,
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000,
};

// @author Meagan
void initWater(Water* water, unsigned int x, unsigned int y) {
    water->x = x;
    water->y = y;
}

// @author Meagan
void isWaterColliding(Water* water, Chuck* chuck) {
    if (chuck->x < water->x + 32 && chuck->x + 32 > water->x &&
        chuck->y < water->y + 32 && chuck->y + 32 > water->y) {
        // Collision detected, handle it here
        chuck->isColliding = 1;
    }
}

// @author Paolo
void render_water(Water* water) {
    // TO DO
}   