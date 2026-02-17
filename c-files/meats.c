#include "meats.h";
#include "Chuck.h";

#define MEATS_HEIGHT 16
int meats_bitmap[MEATS_HEIGHT] =
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

void initMeats(Meats* meats, unsigned int x, unsigned int y) {
    meats->x = x;
    meats->y = y;
    meats->isGathered = 0;
}

void isChuckCollidingWithMeats(Meats* meats, Chuck* chuck) {
    // TO DO tomorrow
    // if (chuck is colliding with meats) { fruits->isGathered = 1 }
}