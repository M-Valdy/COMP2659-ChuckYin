#include "Chuck.h";

typedef struct {
    unsigned int x,y;
    int deltaX, deltaY;
    int isColliding;
    int isForward; // 1 = looking forward, 0 = looking backward
    int frameCount;
} WomenSwimming;


void initWomenSwimming(WomenSwimming* womenSwimming, unsigned int x, unsigned int y);
void updateWomenSwimming(WomenSwimming* womenSwimming);
void collisionWomenSwimming(WomenSwimming* womenSwimming, Chuck* chuck);
void render_womenSwimming(WomenSwimming* womenSwimming);