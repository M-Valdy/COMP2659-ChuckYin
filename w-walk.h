#include "Chuck.h";

typedef struct {
    unsigned int x,y;
    int deltaX, deltaY;
} WomenWalking;

void initWomenWalking(WomenWalking* womenWalking, unsigned int x, unsigned int y);
void updateWomenWalking(WomenWalking* womenWalking);
void collisionWomenWalking(WomenWalking* womenWalking, Chuck* chuck);