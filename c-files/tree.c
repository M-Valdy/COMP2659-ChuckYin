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
void initTree(Tree* tree, unsigned int x, unsigned int y) {
    tree->x = x;
    tree->y = y;
}

// @author Meagan
void isTreeColliding(Tree* tree, Chuck* chuck) {
    if (chuck->x < tree->x + 32 && chuck->x + 32 > tree->x &&
        chuck->y < tree->y + 32 && chuck->y + 32 > tree->y) {
        // Collision detected, handle it here
        chuck->isColliding = 1;
    }
}

// @author Paolo
void render_tree(Tree* Tree) {
    // TO DO
}