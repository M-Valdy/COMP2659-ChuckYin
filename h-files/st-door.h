#include "Chuck.h";
#include "cashier.h";

typedef struct {
    unsigned int x,y;
} StoreDoor;

void initStoreDoor(StoreDoor* storeDoor, unsigned int x, unsigned int y);
void goNextLevel(StoreDoor* storeDoor, Chuck* chuck, cashier* cashier);