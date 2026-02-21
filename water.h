#ifndef WATER_H
#define WATER_H

typedef struct {
    unsigned int x,y;
} Water;

void initWater(Water* water, unsigned int x, unsigned int y);
void isWaterColliding(Water* water, Chuck* chuck);

#endif
