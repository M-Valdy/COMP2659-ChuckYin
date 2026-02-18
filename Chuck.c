#include "Chuck.h";

// function for initializing Chuck's position and state
void initChuck(Chuck* chuck, unsigned int x, unsigned int y) {
    chuck->x = x;
    chuck->y = y;
    chuck->isWalking = 0;
    chuck->isColliding = 0;
    chuck->deltaX = 0;
    chuck->deltaY = 0;
}

// function for starting Chuck's walking in a specified direction
void startWalking(Chuck* chuck, int deltaX, int deltaY) {
    chuck->isWalking = 1;
    chuck->deltaX = deltaX;
    chuck->deltaY = deltaY;
}

// function for updating Chuck's position based on his walking state
void updateChuck(Chuck* chuck) {
    if (chuck->isWalking) {
        chuck->x += chuck->deltaX;
        chuck->y += chuck->deltaY;
    }
}

// function for stopping Chuck's walking
void stopWalking(Chuck* chuck) {
    chuck->isWalking = 0;
    chuck->deltaX = 0;
    chuck->deltaY = 0;
}



