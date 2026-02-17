#include "storeAisle.h";
#include "Chuck.h";

#define STOREAISLE_HEIGHT 16
int storeAisle_bitmap[STOREAISLE_HEIGHT] =
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

void initStoreAisle(StoreAisle* storeAisle, unsigned int x, unsigned int y) {
    storeAisle->x = x;
    storeAisle->y = y;
}

void isChuckCollidingWithStoreAisle(Chuck* chuck, StoreAisle* storeAisle) {
    // TO DO tomorrow
    // if (Chuck trying to move into the Store Aisle from the left/right/up/down) { prevent Chuck from going into Store Aisle }
}