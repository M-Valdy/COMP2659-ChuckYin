#include "Chuck.h";

void initChuck(Chuck* chuck, unsigned int x, unsigned int y) {
    chuck->x = x;
    chuck->y = y;
    chuck->isWalking = 0;
    chuck->deltaX = 0;
    chuck->deltaY = 0;
}


void startWalking(Chuck* chuck, int deltaX, int deltaY) {
    chuck->isWalking = 1;
    chuck->deltaX = deltaX;
    chuck->deltaY = deltaY;
}

void updateChuck(Chuck* chuck) {
    if (chuck->isWalking) {
        chuck->x += chuck->deltaX;
        chuck->y += chuck->deltaY;
    }
}

void stopWalking(Chuck* chuck) {
    chuck->isWalking = 0;
    chuck->deltaX = 0;
    chuck->deltaY = 0;
}



