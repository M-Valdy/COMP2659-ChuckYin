#ifndef ROAD_H
#define ROAD_H

#include "types.h"

#define ROAD_HEIGHT 32
extern const UINT32 road_bitmap_upper[ROAD_HEIGHT];
extern const UINT32 road_bitmap_lower[ROAD_HEIGHT];

typedef struct {
    unsigned int x,y;
    int isLower;
} Road;

void initRoad(Road* road, UINT16 x, UINT16 y, int z);

#endif
