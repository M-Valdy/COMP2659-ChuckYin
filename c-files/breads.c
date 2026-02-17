#include "breads.h";
#include "Chuck.h";

#define BREADS_HEIGHT 16
int breads_bitmap[BREADS_HEIGHT] =
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

void initBreads(Breads* breads, unsigned int x, unsigned int y) {
    breads->x = x;
    breads->y = y;
    breads->isGathered = 0;
}

void isChuckCollidingWithBreads(Breads* breads, Chuck* chuck) {
    // TO DO tomorrow
    // if (chuck is colliding with breads) { breads->isGathered = 1 }
}