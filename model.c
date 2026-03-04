#include "model.h"
#include "raster.h"

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

/*
    @author Paolo
    This is the bitmap that contains the dimensions of the Chuck sprite
    which will be used for rendering and collision detection
*/
const UINT8 Chuck_bitmap[CHUCK_HEIGHT] =
{
    0x00000000, 
    0x003FFC00, 
    0x007FFE00, 
    0x00FFFF00, 
    0x01E3C780, 
    0x03DC3BC0, 
    0x03BFFDC0, 
    0x037FFEC0, 
    0x0367E6C0, 
    0x0367E6C0, 
    0x037FFEC0, 
    0x02FFFF40, 
    0x01FFFF80, 
    0x01FC3F80, 
    0x00FFFF00, 
    0x00FFFF00,
    0x007FFE00, 
    0x001FF800, 
    0x000FF000, 
    0x003FFC00, 
    0x007FFE00, 
    0x006FF600, 
    0x006FF600, 
    0x006FF600, 
    0x006FF600, 
    0x006FF600, 
    0x006C3600, 
    0x000C3000, 
    0x000C3000, 
    0x000C3000, 
    0x000C3000, 
    0x00000000
};

/* @author Paolo */
const UINT16 womenWalking_bitmap[WALKER_HEIGHT] =
{
    0x07c0,
    0x0fe0,
    0x1ef0,
    0x3c78,
    0x3ab8,
    0x3828,
    0x2928,
    0xb7d9,
    0xe283,
    0xffff,
    0x0280,
    0x0f80,
    0x0fe0,
    0x0fe0,
    0x440,
    0x440
};

/* @author Paolo */
const UINT16 womenSwimming_forward_bitmap[SWIMMER_HEIGHT] =
{
    0x1ff8,
    0x3ffc,
    0x7ffe,
    0xffff,
    0xffff,
    0xc813,
    0xc423,
    0xc243,
    0xcdb3,
    0xcc33,
    0xc003,
    0xcff3,
    0xdffb,
    0xdffb,
    0xdffb,
    0xc003
};

/* @author Paolo */
const UINT16 womenSwimming_backward_bitmap[SWIMMER_HEIGHT] =
{
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x001FF800, 
    0x003FFC00, 
    0x007FFE00, 
    0x01FFFF80, 
    0x03FFFFC0, 
    0x07FFFFE0, 
    0x07FFFFE0, 
    0x07FFFFE0, 
    0x0FFFFFF0, 
    0x0FFFFFF0,
    0x0FFFFFF0, 
    0x0FFFFFF0, 
    0x0FFFFFF0, 
    0x1FFFFFF8, 
    0x1FFFFFF8, 
    0x1FFFFFF8, 
    0x1FFFFFF8, 
    0x3FFFFFFC, 
    0x7FFFFFFE, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000
};

/* @author Paolo */
const UINT32 road_bitmap_upper[ROAD_HEIGHT] =
{
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF,
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF,
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0x00000000, 
};

/* @author Paolo */
const UINT32 road_bitmap_lower[ROAD_HEIGHT] =
{
    0x00000000,
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF,
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF,
    0xFFFFFFFF  
};

const UINT32 water_bitmap[WATER_HEIGHT] =
{
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000,
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000,
};

/* @author Meagan
function for initializing Chuck's position and state */
void initChuck(Chuck* chuck, unsigned int x, unsigned int y) {
    chuck->x = x;
    chuck->y = y;
    chuck->isWalking = 0;
    chuck->isColliding = 0;
    chuck->deltaX = 0;
    chuck->deltaY = 0;
    chuck->canMoveLeft = 1;
    chuck->canMoveRight = 1;
    chuck->canMoveUp = 1;
    chuck->canMoveDown = 1;
}

/* @author Meagan & Paolo */
/* function for starting Chuck's walking in a specified direction */
void startWalking(Chuck* chuck, int deltaX, int deltaY) {
    chuck->isWalking = 1;
    chuck->deltaX = deltaX;
    chuck->deltaY = deltaY;
    if (chuck->deltaX > 0) { /* moving right */
        chuck->canMoveLeft = 1; /* can move left if currently moving right */
    } else if (chuck->deltaX < 0) { /* moving left */
        chuck->canMoveRight = 1; /* can move right if currently moving left */
    }
    if (chuck->deltaY > 0) { /* moving down */
        chuck->canMoveUp = 1; /* can move up if currently moving down */
    } else if (chuck->deltaY < 0) { /* moving up */
        chuck->canMoveDown = 1; /* can move down if currently moving up */
    }
}

/* @author Meagan & Paolo
function for updating Chuck's position based on his walking state */
void updateChuck(Chuck* chuck) {
    if (chuck->isWalking) {
        /* check if he's allowed to move there first. */
        if (chuck->canMoveRight == 0 && chuck->deltaX > 0) {
            chuck->deltaX = 0;  
        }
        if (chuck->canMoveLeft == 0 && chuck->deltaX < 0) {
            chuck->deltaX = 0;
        }
        if (chuck->canMoveUp == 0 && chuck->deltaY < 0) {
            chuck->deltaY = 0;
        }
        if (chuck->canMoveDown == 0 && chuck->deltaY > 0) {
            chuck->deltaY = 0;
        }

        chuck->x += chuck->deltaX;
        chuck->y += chuck->deltaY;
    }
}

/* @author Meagan
function for stopping Chuck's walking */
void stopWalking(Chuck* chuck) {
    chuck->isWalking = 0;
    chuck->deltaX = 0;
    chuck->deltaY = 0;
}

/* @author Paolo 
// if Chuck's right edge is touching the left edge of the water, then can't move right
// if Chuck's left edge is touching the right edge of the water, then can't move right */
void checkXCollision(Chuck* chuck, Water* water) {
    if (chuck->x + 32 == water->x) { 
        chuck->canMoveRight = 0;
    } else {
        chuck->canMoveRight = 1;
    }
    if (chuck->x == water->x + 32) { 
        chuck->canMoveLeft = 0;
    } else {
        chuck->canMoveLeft = 1;
    }
}

/* @author Paolo
// if Chuck's top edge is touching the bottom edge of the water, then can't move up
// if Chuck's bottom edge is touching the top edge of the water, then can't move down */
void checkYCollision(Chuck* chuck, Water* water) {
    if (chuck->y == water->y - 32) { 
        chuck->canMoveUp = 0;
    } else {
        chuck->canMoveUp = 1;
    }
    if (chuck->y - CHUCK_HEIGHT == water->y) { 
        chuck->canMoveDown = 0;
    } else {
        chuck->canMoveDown = 1;
    }
}

/* @author Meagan */
void initWomenWalking(WomenWalking* womenWalking, UINT16 x, UINT16 y) {
    womenWalking->x = x;
    womenWalking->y = y;
    womenWalking->deltaX = 1;
    womenWalking->deltaY = 0;
}

/* @author Paolo */
void updateWomenWalking(WomenWalking* womenWalking) {
    womenWalking->x += womenWalking->deltaX;
    if (womenWalking->x + 32 >= 640) {
        womenWalking->deltaX = -1; /* Move left */
    } else if (womenWalking->x <= 0) {
        womenWalking->deltaX = 1; /* Move right */
    }
    
}

/* @author Meagan */
void collisionWomenWalking(WomenWalking* womenWalking, Chuck* chuck) {
    if (womenWalking->x == chuck->x && womenWalking->y == chuck->y) {
        /* womenWalking collides with Chuck, stop movement */
        womenWalking->deltaX = 0;
        womenWalking->deltaY = 0;
        stopWalking(chuck); /* Stop Chuck from walking */
        chuck->isColliding = 2; /* Set death collision flag for Chuck */
    }
}

/* @author Meagan
 This is for making the pseudo-random numbers for isForward state */
static UINT16 seed = 12345;

/* @author Meagan */
void setIsForward(WomenSwimming* womenSwimming, int isForward) {
    seed = (seed * 25173 + 13849) & 0x7FFF; /* make a random number */
    seed = seed & 0x0001; /* make it either 0 or 1 */
    womenSwimming->isForward = seed; /* set isForward to the random number */
}

/* @author Meagan */
void initWomenSwimming(WomenSwimming* womenSwimming, UINT16 x, UINT16 y) {
    womenSwimming->x = x;
    womenSwimming->y = y;
    womenSwimming->deltaX = 0;
    womenSwimming->deltaY = 0;
    womenSwimming->isColliding = 0;
    setIsForward(womenSwimming, 0); /* set isForward to a random value of either 0 or 1 */
}

/* @author Paolo */
void updateWomenSwimming(WomenSwimming* womenSwimming) {
    if (womenSwimming->frameCount == 70 && womenSwimming->isForward == 1) {
        womenSwimming->isForward = 0; /* Switch to backward bitmap after 70 frames */
        womenSwimming->frameCount = 0; /* Reset frame count after switching direction */
    } else if (womenSwimming->frameCount == 70 && womenSwimming->isForward == 0) {
        womenSwimming->isForward = 1; /* Switch to forward bitmap after 70 frames */
    }
    womenSwimming->frameCount++;
    
}

/* @author Meagan */
void collisionWomenSwimming(WomenSwimming* womenSwimming, Chuck* chuck) {
    if (womenSwimming->x == chuck->x && womenSwimming->y == chuck->y && womenSwimming->isForward == 1) {
        /* womenSwimming collides with Chuck, stop movement */
        womenSwimming->deltaX = 0;
        womenSwimming->deltaY = 0;
        chuck->isWalking = 0; /* Stop Chuck from walking */
        chuck->isColliding = 2; /* Set collision flag for Chuck */
        womenSwimming->isColliding = 1;
    }
}

void initRoad(Road* road, UINT16 x, UINT16 y, int z) {
    road->x = x;
    road->y = y;
    road->isLower = z;
}

/* @author Meagan */
/* Function to initialize water */
void initWater(Water* water, UINT16 x, UINT16 y) {
    water->x = x;
    water->y = y;
}

/* @author Meagan
 Function to check if Chuck goes into the water (might change later) */
void isWaterColliding(Water* water, Chuck* chuck) {
    if (chuck->x < water->x + 32 && chuck->x + 32 > water->x &&
        chuck->y < water->y + 32 && chuck->y + 32 > water->y) {
        /* Collision detected, change Chuck's state to death collision */
        chuck->isColliding = 2;
    }
}

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