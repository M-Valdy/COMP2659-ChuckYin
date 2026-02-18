#include "tree.h";
#include "Chuck.h";


// Function to initialize a Tree
void initTree(Tree* tree, unsigned int x, unsigned int y) {
    tree->x = x;
    tree->y = y;
}


// Function to check for collision between Chuck and a Tree
void isTreeColliding(Tree* tree, Chuck* chuck) {
    if (chuck->x < tree->x + 12 && chuck->x + 12 > tree->x &&
        chuck->y < tree->y + 12 && chuck->y + 12 > tree->y) {
        // Set is colliding to 1 if there is a collision with the tree
        chuck->isColliding = 1;
    }
}

