#include "model.h"
#include "raster.h"
#include "effects.h"

typedef struct {
    int x;
    int y;
} Coords;

/* @author Paolo */
static const Coords WALKERS_SPAWN_POINTS[4] = {
    { 320, 48 }, { 400, 144 }, { 480, 272 }, { 64, 304 }
};

/* @author Paolo */
static const Coords SWIMMERS_SPAWN_POINTS[20] = {
    {160,80}, {160,112}, {192,112}, {224,112}, {224,80}, /* 160, 224, 416, 480... 80 y coord*/ 
    {416,80}, {416,112}, {448,112}, {480,112}, {480,80}, /* 160, 192, 224, 416, 448, 480... 112 y coord**/
    {160,208}, {160,240}, {192,240}, {224,240}, {224,208}, 
    {416,208}, {416,240}, {448,240}, {480,240}, {480,208} 
};

/* @author Paolo */
static const Coords WATER_SPAWN_POINTS[60] = {
    {0,80}, {32,80}, {64,80}, {96,80}, {128,80}, {192,80}, {256,80}, {288,80}, {320,80}, {352,80},
    {384,80}, {448,80}, {512,80}, {544,80}, {576,80}, {608,80}, {0,112}, {32,112}, {64,112}, {96,112}, 
    {128,112}, {256,112}, {288,112}, {320,112}, {352,112}, {384,112}, {512,112}, {544,112}, {576,112}, {608,112},

    {0,208}, {32,208}, {64,208}, {96,208}, {128,208}, {192,208}, {256,208}, {288,208}, {320,208}, {352,208},
    {384,208}, {448,208}, {512,208}, {544,208}, {576,208}, {608,208}, {0,240}, {32,240}, {64,240}, {96,240}, 
    {128,240}, {256,240}, {288,240}, {320,240}, {352,240}, {384,240}, {512,240}, {544,240}, {576,240}, {608,240}
};

/*
    @author Paolo
    This is the bitmap that contains the dimensions of the Chuck sprite
    which will be used for rendering and collision detection
*/
const UINT32 Chuck_bitmap[CHUCK_HEIGHT] =
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
const UINT32 womenWalking_bitmap[WALKER_HEIGHT] =
{
    0x00000000, 
    0x001FF800, 
    0x007E7E00, 
    0x00F18F00, 
    0x00EFF700, 
    0x01DFFB80, 
    0x01BFFD80, 
    0x037FFEC0, 
    0x02E7E740, 
    0x02E7E740, 
    0x01FFFF80, 
    0x03FFFFC0, 
    0x03FFFFC0, 
    0x03FC3FC0, 
    0x03FFFFC0, 
    0x06FFFF60, 
    0x047FFE20, 
    0x0C1FF830, 
    0x180FF018, 
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
const UINT32 womenSwimming_forward_bitmap[SWIMMER_HEIGHT] =
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
    0x03FFFFC0, 
    0x03FFFFC0, 
    0x07FFFFE0, 
    0x0FC7E3F0, 
    0x0F8001F0,
    0x0F8001F0, 
    0x0F0000F0, 
    0x0D1818B0, 
    0x1D1818B8, 
    0x1D0000B8, 
    0x1F0000F8, 
    0x1F0000F8, 
    0x3F0000FC, 
    0x7F83C1FE, 
    0xFFC003FF, 
    0xFFE007FF, 
    0xFFF00FFF, 
    0x00000000, 
    0x00000000, 
    0x00000000, 
    0x00000000
};

/* @author Paolo */
const UINT32 womenSwimming_backward_bitmap[SWIMMER_HEIGHT] =
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

/* @author Paolo */
const UINT32 water_bitmap[WATER_HEIGHT] =
{
    0x00000000,
    0x00000000,
    0x0703C0E0,
    0x08842110,
    0x90481209,
    0x60300C06,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x0703C0E0,
    0x08842110,
    0x90481209,
    0x60300C06,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x0703C0E0,
    0x08842110,
    0x90481209,
    0x60300C06,
    0x00000000,
    0x00000000,
    0x00000000,
    0x00000000,
    0x0703C0E0,
    0x08842110,
    0x90481209,
    0x60300C06,
    0x00000000,
    0x00000000
};

/* @author Paolo, needed this in renderer for the minimized plotting of the score */
void updateScore(Model *model) {
    model->oldCrossCount = model->crossCount;
}

/* @author Meagan & Paolo
function for initializing Chuck's position and state */
void initChuck(Chuck* chuck, int x, int y) {
    chuck->x = x;
    chuck->y = y;
    if (chuck->deathCounter == 0) {
        chuck->oldx = x;
        chuck->oldy = y;
        chuck->deathCounter = 1;
    }
    chuck->isWalking = 0;
    chuck->isColliding = 0;
    chuck->deltaX = 0;
    chuck->deltaY = 0;
    stopWalking(chuck);
}

/* @author Meagan */
/* function for starting Chuck's walking in a specified direction */
void startWalking(Chuck* chuck, int deltaX, int deltaY) {
    chuck->isWalking = 1;
    chuck->deltaX = deltaX;
    chuck->deltaY = deltaY;
}

/* @author Meagan & Paolo
function for updating Chuck's position based on his walking state */
void updateChuck(Chuck* chuck) {
    chuck->oldx = chuck->x;
    chuck->oldy = chuck->y;
    if (chuck->isWalking) {
        int newX = chuck->x + chuck->deltaX;
        int newY = chuck->y + chuck->deltaY;

        if (newX < 0) {
            play_touch_edge();
            newX = 0;
        } else if (newX > 640 - CHUCK_HEIGHT) {
            newX = 640 - CHUCK_HEIGHT;
        }
        if (newY < 0) {
            play_touch_edge();
            newY = 0;
        } else if (newY > 400 - CHUCK_HEIGHT) {
            newY = 400 - CHUCK_HEIGHT;
        }
        chuck->x = newX;
        chuck->y = newY;

        stopWalking(chuck);
    }
}

/* @author Meagan
function for stopping Chuck's walking */
void stopWalking(Chuck* chuck) {
    chuck->isWalking = 0;
    chuck->deltaX = 0;
    chuck->deltaY = 0;
}

/* @author Meagan & Paolo*/
void initWomenWalking(WomenWalking* womenWalking, UINT16 x, UINT16 y) {
    int multiplier;
    womenWalking->x = x;
    womenWalking->y = y;
    womenWalking->oldx = x;
    womenWalking->oldy = y;
    womenWalking->isColliding = 0;
    multiplier = intGenerator(1);
    if (multiplier == 1) {
        womenWalking->deltaX = WALKER_SPEED;
    } else if (multiplier == 0) {
        womenWalking->deltaX = -1*WALKER_SPEED;
    }
    womenWalking->deltaY = 0;
}

/* @author Paolo */
void updateWomenWalking(WomenWalking* womenWalking) {
    womenWalking->oldx = womenWalking->x;
    womenWalking->oldy = womenWalking->y;

    womenWalking->x += womenWalking->deltaX;

    if (womenWalking->x + WALKER_HEIGHT > 640) {
        womenWalking->x = 640 - WALKER_HEIGHT;
        womenWalking->deltaX = -WALKER_SPEED;
    } else if (womenWalking->x < 0) {
        womenWalking->x = 0;
        womenWalking->deltaX = WALKER_SPEED;
    }
}

/* @author Meagan & Paolo 
    Paolo's notes:
    - i copied my swimmer if statement overhaul and pasted it here, check notes on it if need clarity
*/
void collisionWomenWalking(WomenWalking* womenWalking, Chuck* chuck) {
    if (womenWalking->x+WALKER_HEIGHT-6 >= chuck->x && womenWalking->x <= chuck->x+CHUCK_HEIGHT-6 &&  
        womenWalking->y <= chuck->y+CHUCK_HEIGHT-6 && womenWalking->y+WALKER_HEIGHT-6 >= chuck->y ) {
        /*stopWalking(chuck); /* Stop Chuck from walking */
        chuck->isColliding = 2; /* Set death collision flag for Chuck */
        womenWalking->isColliding = 1;
    } else {
        womenWalking->isColliding = 0;
    }
}

/* @author Meagan
 This is for making the pseudo-random numbers for isForward state */
static UINT16 seed = 12345;

/* @author Meagan & Paolo */
int intGenerator(int max) { /* used Bing and Copilot for help. Max must be any of these: 1,3,7,15,31,63, 127, 255, 511, 1023 */
    seed = (seed * 25173 + 13849) & 0x7FFF;
    return (seed >> 8) & max;
}

/* @author Meagan & Paolo*/
void initWomenSwimming(WomenSwimming* womenSwimming, UINT16 x, UINT16 y) {
    womenSwimming->x = x;
    womenSwimming->y = y;
    womenSwimming->deltaX = 0;
    womenSwimming->deltaY = 0;
    womenSwimming->isColliding = 0;
    womenSwimming->isForward = intGenerator(1); /* set isForward to a random value of either 0 or 1 */
    womenSwimming->frameCount = intGenerator(MAX_FRAMES);
}

/* @author Paolo */
void updateWomenSwimming(WomenSwimming* womenSwimming) {
    if (womenSwimming->frameCount == MAX_FRAMES && womenSwimming->isForward == 1) {
        womenSwimming->isForward = 0; /* Switch to backward bitmap after MAX_FRAMES frames */
        womenSwimming->frameCount = 0; /* Reset frame count after switching direction */
    } else if (womenSwimming->frameCount == MAX_FRAMES && womenSwimming->isForward == 0) {
        womenSwimming->frameCount = 0;
        womenSwimming->isForward = 1; /* Switch to forward bitmap after MAX_FRAMES frames */
    }
    womenSwimming->frameCount++;
}

/* @author Meagan & Paolo 
    Paolo's notes:
    - i overhauled the if statement significantly. instead of women.x/y == chuck.x/y, it now uses their coords+HEIGHT
    - if statement checks:
        - if swimmer from left enters chucks bitmap
        - if swimmer from right enters chucks bitmap
        - if swimmer from above enters chucks bitmap
        - if swimmer from below enters chucks bitmap
    - i'm also adding -6 so it doesn't activate right away and player doesn't have to be pixel perfect to avoid collision
*/
void collisionWomenSwimming(WomenSwimming* womenSwimming, Chuck* chuck) { 
    if (womenSwimming->x+SWIMMER_HEIGHT-6 >= chuck->x && womenSwimming->x <= chuck->x+CHUCK_HEIGHT-6 &&  
        womenSwimming->y <= chuck->y+CHUCK_HEIGHT-6 && womenSwimming->y+SWIMMER_HEIGHT-6 >= chuck->y) {
        if (womenSwimming->isForward == 1) {
            /* womenSwimming collides with Chuck, stop movement */
            womenSwimming->deltaX = 0;
            womenSwimming->deltaY = 0;
            chuck->isWalking = 0; /* Stop Chuck from walking */
            chuck->isColliding = 2; /* Set collision flag for Chuck */
        }
        womenSwimming->isColliding = 1;
    } else {
        womenSwimming->isColliding = 0;
    }
}

/* @author Paolo */
void initRoad(Road* road, UINT16 x, UINT16 y, int z) {
    road->x = x;
    road->y = y;
    road->isLower = z;
    road->isColliding = 0;
    road->isPrevColliding = 0;
}

/* @author Paolo */
void isRoadCollidingWalker(Road* road, WomenWalking* womenWalking) {
    if (womenWalking->x < road->x + ROAD_HEIGHT + 10 || womenWalking->x + WALKER_HEIGHT + 10 > road->x) {
        road->isColliding = 1;
    } else { 
        road->isColliding = 0;
    }
} 

/* @author Paolo */
void isRoadCollidingChuck(Road* road, Chuck* chuck) {
    if ((chuck->x < road->x + ROAD_HEIGHT && chuck->x + CHUCK_HEIGHT > road->x && chuck->y < road->y + ROAD_HEIGHT && chuck->y + CHUCK_HEIGHT > road->y) || 
        (chuck->oldx < road->x + ROAD_HEIGHT && chuck->oldx + CHUCK_HEIGHT > road->x && chuck->oldy < road->y + ROAD_HEIGHT && chuck->oldy + CHUCK_HEIGHT > road->y)) {
        road->isPrevColliding = road->isColliding;
        road->isColliding = 1;
    } else {
        if (road->isPrevColliding == 0) {
            road->isPrevColliding = road->isColliding;
            road->isColliding = 0;
        }
    }
}

/* @author Paolo */
void resetRoadCollision(Road* road) {
    road->isPrevColliding = 0;
}


/* @author Meagan */
/* Function to initialize water */
void initWater(Water* water, UINT16 x, UINT16 y) {
    water->x = x;
    water->y = y;
}

/* @author Meagan & Paolo
    Paolo's notes: 
    - copied my swimmer collision if statement overhaul
    - i don't minus 5 because water is now small and its the players fault if they accidentally run over it
 Function to check if Chuck goes into the water (might change later) */
void isWaterColliding(Water* water, Chuck* chuck) {
    /* (womenSwimming->x+SWIMMER_HEIGHT-6 >= chuck->x && womenSwimming->x <= chuck->x+CHUCK_HEIGHT-6 &&  
        womenSwimming->y <= chuck->y+CHUCK_HEIGHT-6 && womenSwimming->y+SWIMMER_HEIGHT-6 >= chuck->y) */
    if (chuck->x < water->x + WATER_HEIGHT && chuck->x + CHUCK_HEIGHT > water->x &&
        chuck->y < water->y + WATER_HEIGHT && chuck->y + CHUCK_HEIGHT > water->y) {
        /* Collision detected, change Chuck's state to death collision */
        chuck->isColliding = 2;
    }
}

/* @author Paolo 
    Initializes the roads. Since water objects are always 64 pixels below, might as well just use the same coordinates while adding 64
*/
void init_land(Model *model) {
    int i = 0;
    int x = 0;
    int y = 16;
    int count = 0;
    int isDown = 0;
    for (i = 0; i < NUM_ROADS; i++) {
        initRoad(&model->road[i], x, y, isDown);
        x += 32;
        count++;
        if (count > 19) {
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

    for (i = 0; i < NUM_WATER; i++) {
        initWater(&model->water[i], WATER_SPAWN_POINTS[i].x, WATER_SPAWN_POINTS[i].y);
    }
}

/* @author Paolo */
void init_women(Model *model) {
    int i;
    for (i = 0; i < NUM_WALKERS; i++) {
        initWomenWalking(&model->womenWalking[i], WALKERS_SPAWN_POINTS[i].x, WALKERS_SPAWN_POINTS[i].y);
    }

    for (i = 0; i < NUM_SWIMMERS; i++) {
        initWomenSwimming(&model->womenSwimming[i], SWIMMERS_SPAWN_POINTS[i].x, SWIMMERS_SPAWN_POINTS[i].y); 
    }
}

/* @author Paolo */
void Model_init(Model *model) {
    model->gameOver = 0;
    model->crossCount = 0;
    model->oldCrossCount = 0;
    model->chuck.deathCounter = 0;
    model->cheatsOn = 0;
    init_land(model);
    init_women(model);
    initChuck(&model->chuck, 320, 368);
}

/* @author Paolo */
void toggleCheats(Model *model) {
    if (model->cheatsOn == 1) {
        model->cheatsOn = 0;
    } else {
        model->cheatsOn = 1;
    }
}