#include "water.h";
#include "Chuck.h";

void initWater(Water* water, unsigned int x, unsigned int y) {
    water->x = x;
    water->y = y;
}

void isWaterColliding(Water* water, Chuck* chuck) {
    if (chuck->x < water->x + 32 && chuck->x + 32 > water->x &&
        chuck->y < water->y + 32 && chuck->y + 32 > water->y) {
        // Collision detected, handle it here
        chuck->isColliding = 1;
    }
}