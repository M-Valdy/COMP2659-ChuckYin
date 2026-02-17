#include "Chuck.h";

typedef struct {
    unsigned int x,y;
    int isGathered;
} Meats;

void initMeats(Meats* meats, unsigned int x, unsigned int y);
void isChuckCollidingWithMeats(Meats* meats, Chuck* chuck);