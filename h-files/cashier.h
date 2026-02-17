#include "Chuck.h";

typedef struct {
    unsigned int x,y;
    int hasInteracted;
    int canInteractWith;
} Cashier;

void initCashier(Cashier* cashier, unsigned int x, unsigned int y);
void isCashierColliding(Cashier* cashier, Chuck* chuck);
void canCheckout(Cashier* cashier, Chuck* chuck);