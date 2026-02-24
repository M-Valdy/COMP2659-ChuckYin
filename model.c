#include "model.h"

typedef struct {
    int x;
    int y;
} Coords;

/* @author Paolo */
static const Coords WALKERS_SPAWN_POINTS[15] = {
    {  24, 16 }, {  242, 16 }, { 453, 16 }, { 130, 48 }, { 350, 48 },
    { 133, 144 }, { 325, 144 }, { 527, 144 }, { 102, 176 }, { 397, 176 },
    {  141, 272 }, { 485, 272 }, { 60, 304 }, { 216, 304 }, { 340, 304 }
};

/* @author Paolo */
static const Coords SWIMMERS_SPAWN_POINTS[15] = {
    {  23, 208 }, {  67, 208 }, { 116, 208 }, { 253, 208 }, { 300, 208 },
    { 435, 208 }, { 483, 208 }, { 527, 208 }, { 2, 240 }, { 69, 240 },
    {  140, 240 }, { 217, 240 }, { 343, 240 }, { 418, 240 }, { 495, 240 }
};

/* @author Paolo 
    Initializes the roads. Since water objects are always 64 pixels below, might as well just use the same coordinates while adding 64
*/
void init_land(Model *model) {
    int i;
    int x;
    int y = 16;
    int count;
    int isDown;
    for (i = 0; i < 120; i++) {
        initWater(&model->water[i], x, y+64);
        initRoad(&model->road[i], x, y, isDown);
        x += 32;
        count++;
        if (count == 19) {
            count = 0;
            isDown++;
            if (isDown == 2) {
                y = 144;
            } else if (isDown == 4) {
                y = 272;
            } else {
                y += 32; /* go to lower half of the road (it's designed to be 64 pixels high, so just add 32 to get to the lower half) */ 
            }
            x = 0;
        }
    }
}

/* @author Paolo */
void init_women(Model *model) {
    int i;

    for (i = 0; i < 15; i++) {
        initWomenWalking(&model->womenWalking[i], WALKERS_SPAWN_POINTS[i].x, WALKERS_SPAWN_POINTS[i].y);
        initWomenSwimming(&model->womenSwimming[i], SWIMMERS_SPAWN_POINTS[i].x, SWIMMERS_SPAWN_POINTS[i].y); 
    }
}

/* @author Paolo */
void Model_init(Model *model) {
    model->gameOver = 0;
    model->crossCount = 0;
    init_land(model);
    init_women(model);
    initChuck(&model->chuck, 320, 350);
}

/* 
int main() {
    Model model;
    Model_init(&model);

    return 0;
}*/