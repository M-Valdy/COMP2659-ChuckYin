#include "Chuck.h";

typedef struct {
    unsigned int x,y;
    int deltaX, deltaY;
} WomenSwimming;


void initWomenSwimming(WomenSwimming* womenSwimming, unsigned int x, unsigned int y);
void updateWomenSwimming(WomenSwimming* womenSwimming);
void collisionWomenSwimming(WomenSwimming* womenSwimming, Chuck* chuck);