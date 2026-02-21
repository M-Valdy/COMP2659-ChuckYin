#include "tree.h";
#include "Chuck.h";

// @author Paolo
#define TREE_HEIGHT 32
const unsigned long tree_bitmap[TREE_HEIGHT] =
{
    0x0003C000, 
    0x001FF800, 
    0x007FFE00, 
    0x007FFE00, 
    0x00FFFF00, 
    0x00FFFF00, 
    0x00FFFF00, 
    0x00FFFF00, 
    0x00FFFF00, 
    0x00FFFF00, 
    0x00FFFF00, 
    0x00FFFF00, 
    0x00FFFF00, 
    0x00FFFF00, 
    0x007FFE00, 
    0x003FFC00,
    0x001FF800, 
    0x0007E000, 
    0x00018000, 
    0x00018000, 
    0x00018000, 
    0x00018000, 
    0x00018000, 
    0x00018000, 
    0x00018000, 
    0x00018000, 
    0x00018000, 
    0x00018000, 
    0x00018000, 
    0x0003C000, 
    0x0007E000, 
    0x000FF000
};

// @author Meagan
// Function to initialize a Tree
void initTree(Tree* tree, unsigned int x, unsigned int y) {
    tree->x = x;
    tree->y = y;
}

// @author Meagan
// Function to check for collision between Chuck and a Tree
void isTreeColliding(Tree* tree, Chuck* chuck) {
    if (chuck->x < tree->x + 12 && chuck->x + 12 > tree->x &&
        chuck->y < tree->y + 12 && chuck->y + 12 > tree->y) {
        // Set is colliding to 1 if there is a collision with the tree
        chuck->isColliding = 1;
    }
}