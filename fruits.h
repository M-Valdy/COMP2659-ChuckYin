#include "Chuck.h";

typedef struct {
    unsigned int x,y;
    int isGathered;
} Fruits;

void initFruits(Fruits* fruits, unsigned int x, unsigned int y);
void isChuckCollidingWithFruits(Fruits* fruits, Chuck* chuck);