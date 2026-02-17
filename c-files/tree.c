#include "tree.h";
#include "Chuck.h";

void initTree(Tree* tree, unsigned int x, unsigned int y) {
    tree->x = x;
    tree->y = y;
}

void isTreeColliding(Tree* tree, Chuck* chuck) {
    if (chuck->x < tree->x + 32 && chuck->x + 32 > tree->x &&
        chuck->y < tree->y + 32 && chuck->y + 32 > tree->y) {
        // Collision detected, handle it here
        chuck->isColliding = 1;
    }
}

