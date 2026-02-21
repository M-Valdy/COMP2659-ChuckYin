#include "Chuck.h";

#ifndef W_WALK_H
#define W_WALK_H
/*
    This file defines the womenWalking struct as well as the fumction to initialize the struct,
    update the position of the womenWalking so they continuously walk across the screen, 
    and check for collision between the womenWalking and Chuck.
*/
typedef struct {
    unsigned int x,y;
    int deltaX, deltaY;
} WomenWalking;


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

#endif