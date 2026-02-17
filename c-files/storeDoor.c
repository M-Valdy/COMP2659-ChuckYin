#include "storeDoor.h";
#include "cashier.h";
#include "Chuck.h";

#define STOREDOOR_HEIGHT 16
int storeDoor_bitmap[STOREDOOR_HEIGHT] =
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

void initStoreDoor(StoreDoor* storeDoor, unsigned int x, unsigned int y) {
    storeDoor->x = x;
    storeDoor->y = y;
}

void goNextLevel(StoreDoor* storeDoor, Chuck* chuck, cashier* cashier) {
    // TO DO tomorrow
    // if (ChuckCollidingWithDoor && cashier->hasInteractedWith == 1) { go next level :D }
}