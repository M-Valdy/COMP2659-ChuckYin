#include "water.h";
#include "Chuck.h";


// Function to initialize water
void initWater(Water* water, unsigned int x, unsigned int y) {
    water->x = x;
    water->y = y;
}

// Function to check if Chuck goes into the water (might change later)
void isWaterColliding(Water* water, Chuck* chuck) {
    if (chuck->x < water->x + 32 && chuck->x + 32 > water->x &&
        chuck->y < water->y + 32 && chuck->y + 32 > water->y) {
        // Collision detected, change Chuck's state to death collision
        chuck->isColliding = 2;
    }
}