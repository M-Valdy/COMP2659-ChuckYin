#ifndef MODEL_H
#define MODEL_H

#include "types.h"

/*

    This file defines the struct that contains all the structures that represent the state 
    of all game objects in the model, which includes the player character Chuck, the women walking, 
    the women swimming, the trees, the water, and the roads.

    It also defines the function that initializes the model by setting the initial positions 
    and states of all game objects.

    Team names: Meagan Valderrama, Paolo Deocareza, and Gaurik Khullar
    @authors Meagan Valderrama, Paolo Deocareza
*/
#define CHUCK_SPEED 6
/*#define CHUCK_SPEED 32  change this after this is only for gauriks testing */
#define WALKER_SPEED 8
#define MAX_FRAMES 63

#define CHUCK_HEIGHT 32
#define WALKER_HEIGHT 32
#define SWIMMER_HEIGHT 32
#define ROAD_HEIGHT 32
#define WATER_HEIGHT 32

#define NUM_WALKERS 4
#define NUM_SWIMMERS 20
#define NUM_WATER 60
#define NUM_ROADS 120

extern const UINT32 Chuck_bitmap[CHUCK_HEIGHT];
extern const UINT32 womenWalking_bitmap[WALKER_HEIGHT];
extern const UINT32 womenSwimming_forward_bitmap[SWIMMER_HEIGHT];
extern const UINT32 womenSwimming_backward_bitmap[SWIMMER_HEIGHT];
extern const UINT32 road_bitmap_upper[ROAD_HEIGHT];
extern const UINT32 road_bitmap_lower[ROAD_HEIGHT];
extern const UINT32 water_bitmap[WATER_HEIGHT];

typedef struct {
    int x;
    int y;
    int oldx;
    int oldy;
    int isWalking;
    int deltaX;
    int deltaY;
    int isColliding; /* 1 = obstacle collision, 0 = no collision, 2 = death collision */
    int deathCounter;
} Chuck;

typedef struct {
    int x, y;
    int oldx, oldy;
    int deltaX, deltaY;
    int isColliding;
} WomenWalking;

typedef struct {
    unsigned int x,y;
    int deltaX, deltaY;
    int isColliding;
    int isForward; /*1 = looking forward, 0 = looking backward*/ 
    int frameCount;
} WomenSwimming;

typedef struct {
    unsigned int x,y;
    int isLower;
    int isColliding;
    int isPrevColliding;
} Road;

typedef struct {
    int x,y;
} Water;

typedef struct {
    int gameOver;
    int crossCount;
    int oldCrossCount;
    int cheatsOn;
    Chuck chuck;
    WomenWalking womenWalking[NUM_WALKERS];
    WomenSwimming womenSwimming[NUM_SWIMMERS];
    Water water[NUM_WATER]; 
    Road road[NUM_ROADS];
} Model;

void toggleCheats(Model *model);
void updateScore(Model *model);
void resetRoadCollision(Road* road);

/*----- Function: initChuck -----

 PURPOSE: Initializes the Chuck struct by setting his initial position, walking state, 
        movement deltas, collision state, and movement permissions.

 INPUT: Chuck*: a pointer to the model containing the player character Chuck
        unsigned int x: the initial x position of Chuck
        unsigned int y: the initial y position of Chuck

 OUTPUT: Chuck struct initialized with the provided position 
        and default states for walking, movement, and collision.

 ASSUMPTIONS: The renderer is working with the same coordinate system as the one used to 
       initialize Chuck's position, and that the initial position provided is within 
       the bounds of the game screen.

*/
void initChuck(Chuck* chuck, int x, int y);


/*----- Function: startWalking -----

 PURPOSE: Sets the walking state of Chuck to 1 and initializes movement deltas.

 INPUT: Chuck*: a pointer to the model containing the player character Chuck
        int deltaX: the x direction of movement (1 for right, -1 for left)
        int deltaY: the y direction of movement (1 for down, -1 for up)

 OUTPUT: Chuck struct with walking state set to 1 and movement deltas set

 ASSUMPTIONS: This function assumes
        - isWalking state is properly set to 0
        - movement deltas will be used in the updateChuck function to change 
        Chuck's position accordingly. 

*/
void startWalking(Chuck* chuck, int deltaX, int deltaY);


/*----- Function: updateChuck -----

 PURPOSE: Changes Chuck's position based on his movement deltas if he's walking, and checks for collisions 
        and movement permissions before updating his position.

 INPUT: Chuck*: a pointer to the model containing the player character Chuck

 OUTPUT: Chuck struct with updated position state

 ASSUMPTIONS: This function assumes
       - isWalking state is properly set to either 0 or 1
       - movement deltas are set correctly based on the direction of movement
       - collision state and movement permissions are updated correctly by 
       other functions before this function is called

*/
void updateChuck(Chuck* chuck);


/*----- Function: stopWalking -----

 PURPOSE: Sets the walking state of Chuck to 0 and resets movement deltas.

 INPUT: Chuck*: a pointer to the model containing the player character Chuck

 OUTPUT: Chuck struct with walking state set to 0 and movement deltas reset to 0

 ASSUMPTIONS: This function assumes
        - isWalking state is properly set to 1 before this function is called
        - movement deltas will be reset to 0 to stop Chuck's movement in the updateChuck function.

*/
void stopWalking(Chuck* chuck);


/*-----Function: initWomenWalking-----
 PURPOSE: Initializes the WomenWalking struct with the given x and y coordinates.

 INPUT: WomenWalking*: a pointer to the model containing the women walking
        unsigned int x: the initial x position of the women walking
        unsigned int y: the initial y position of the women walking

 OUTPUT: WomenWalking struct initialized with the provided position and default movement deltas.

 ASSUMPTIONS: The renderer is working with the same coordinate system as the one used to 
       initialize WomenWalking's position, and that the initial position provided is within 
       the bounds of the game screen.
*/
void initWomenWalking(WomenWalking* womenWalking, unsigned int x, unsigned int y);


/*-----Function: updateWomenWalking-----
 PURPOSE: Updates the position of the women walking based on their movement deltas, 
    and changes direction when they reach the edge of the screen.

 INPUT: WomenWalking*: a pointer to the model containing the women walking

 OUTPUT: WomenWalking struct with updated position based on movement deltas and screen boundaries.
 ASSUMPTIONS: This function assumes
        - movement deltas are set correctly based on the direction of movement
        - the screen width is 640 pixels, and the
*/
void updateWomenWalking(WomenWalking* womenWalking);

/*-----Function: collisionWomenWalking-----
 PURPOSE: Checks for collision between the women walking and Chuck.
 
 INPUT: WomenWalking*: a pointer to the model containing the women walking
        Chuck*: a pointer to the model containing Chuck

 OUTPUT: Updates the collision state of Chuck if a collision is detected.

 ASSUMPTIONS: This function assumes
        - both WomenWalking and Chuck have defined positions and dimensions
        - collision detection is based on overlapping bounding boxes
*/
void collisionWomenWalking(WomenWalking* womenWalking, Chuck* chuck);


/*----- Function: intGenerator -----

 PURPOSE: Used for anything that might need a random number

 INPUT: int max: the max possible value in the range

 OUTPUT: The random value generated, which will be used for frameCount and isForward initializations.

 ASSUMPTIONS: The seed variable is properly initialized and updated elsewhere in the code.
 
*/
int intGenerator(int max);



/*----- Function: initWomenSwimming -----

 PURPOSE: Initializes the WomenSwimming struct by setting their initial position, movement deltas, 
        collision state, whether they are facing forward or backward, and frame count.

 INPUT: WomenSwimming*: a pointer to an object containing a woman swimming
        unsigned int x: the initial x position of the woman swimming
        unsigned int y: the initial y position of the woman swimming

 OUTPUT: Women Swimming struct initialized with the provided position and default states for movement, 
 collision, facing direction, and frame count.
 
 ASSUMPTIONS: The renderer is working with the same coordinate system as the one used

*/
void initWomenSwimming(WomenSwimming* womenSwimming, unsigned int x, unsigned int y);


/*----- Function: updateWomenSwimming -----

 PURPOSE: Updates the position of the women swimming based on their forward/backward states
        then it switches their facing direction after 70 frames.

 INPUT: WomenSwimming*: a pointer to an object containing a woman swimming

 OUTPUT: Updated position and facing direction of the woman swimming based on the animation 
        frame count and their current facing direction.

 ASSUMPTIONS: This function assumes that the frame count is being properly incremented elsewhere in the code, 
        and that the forward/backward state is properly initialized using the setIsForward function. 
*/
void updateWomenSwimming(WomenSwimming* womenSwimming);


/*----- Function: collisionWomenSwimming -----

 PURPOSE: Handles the collision between a woman swimming and Chuck. Sets the movement of 
        both Chuck and the women swimming to 0. And then it sets the collision state of both Chuck and the women
        swimming to indicate that a collision has occurred.

 INPUT: WomenSwimming*: a pointer to an object containing a woman swimming
        Chuck*: a pointer to the Chuck struct

 OUTPUT: Updates the collision state of both the woman swimming and Chuck.
 
 ASSUMPTIONS: This function assumes that the positions and forward/backward states are properly set
*/
void collisionWomenSwimming(WomenSwimming* womenSwimming, Chuck* chuck);

void initRoad(Road* road, UINT16 x, UINT16 y, int z);
void isRoadCollidingWalker(Road* road, WomenWalking* womenWalking);
void isRoadCollidingChuck(Road* road, Chuck* chuck);

/*----- Function: initWater -----

 PURPOSE: Initializes the Water struct by setting its initial position.

 INPUT: Water*: a pointer to the model containing the water object
        unsigned int x: the initial x position of the water
        unsigned int y: the initial y position of the water

 OUTPUT: Water struct initialized with the provided position.

 ASSUMPTIONS: The renderer is working with the same coordinate system as the one used to 
       initialize the water's position, and that the initial position provided is within 
       the bounds of the game screen.

*/
void initWater(Water* water, unsigned int x, unsigned int y);

/*----- Function: Model_init -----

 PURPOSE: Initializes the model by setting the initial positions and states of all game objects.

 INPUT: Model*: a pointer to the model containing all game objects

 OUTPUT: Entire game screen with all game objects initialized to their starting positions and states

*/
void Model_init(Model *model);

/*----- Function: init_land -----

 PURPOSE: Initializes water and road objects in their appropriate coordinates

 INPUT: Model*: a pointer to the model containing all game objects

 OUTPUT: All water and road objects ready to be rendered

*/
void init_land(Model *model);

/*----- Function: init_women -----

 PURPOSE: Initializes swimmers and walking women in their appropriate coordinates

 INPUT: Model*: a pointer to the model containing all game objects

 OUTPUT: All swimmers and walking women objects ready to be rendered

*/
void init_women(Model *model);

#endif