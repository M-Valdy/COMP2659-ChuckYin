#include "Chuck.h";

typedef struct {
    unsigned int x,y;
} Tree;

void initTree(Tree* tree, unsigned int x, unsigned int y);
void isTreeColliding(Tree* tree, Chuck* chuck);