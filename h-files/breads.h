#include "Chuck.h";

#define BREADS_HEIGHT 16 // added this for my bitmap tester
extern int breads_bitmap[BREADS_HEIGHT]; // added this for my bitmap tester 

typedef struct {
    unsigned int x,y;
    int isGathered;
} Breads;

void initBreads(Breads* breads, unsigned int x, unsigned int y);
void isChuckCollidingWithBreads(Breads* breads, Chuck* chuck);