#include "cashier.h";
#include "Chuck.h";

#define CASHIER_HEIGHT 16
int cashier_bitmap[CASHIER_HEIGHT] =
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

void initCashier(Cashier* cashier, unsigned int x, unsigned int y) {
    cashier->x = x;
    cashier->y = y;
    cashier->hasInteracted = 0;
    cashier->canInteractWith = 0;
}

void isCashierColliding(Cashier* cashier, Chuck* chuck) {
    // TO DO tomorrow
    // if ( ChuckCollidingWithCashier && cashier->canInteractWith == 1) { cashier->hasInteracted = 1 }
}

void canCheckout(Cashier* cashier, Chuck* chuck) {
    // TO DO tomorrow
    // if (fruits->isGathered && meats->isGathered && breads->isGathered) { cashier->canInteractWith = 1 }
}