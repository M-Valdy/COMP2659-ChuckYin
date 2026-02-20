#include "Chuck.h"

#ifndef W_SWIM_H
#define W_SWIM_H

/*
    This file defines the struct that contains all the information needed to represent
    the women swimming, which includes their position, movement deltas, collision state, 
    whether they're looking forward or backward, and how much they are moving in the x and y directions
    It also defines the functions that manipulate the state of the women swimming, including initializing their state, 
    updating their position and animation frame, and handling collisions with Chuck.

    Team names: Meagan Valderrama, Paolo Deocareza, and Gaurik Khullar
    @authors Meagan Valderrama, Paolo Deocareza (the author of each specific function is 
    in the comment above the function definition in w-swim.c)
*/
typedef struct {
    unsigned int x,y;
    int deltaX, deltaY;
    int isColliding;
    int isForward; // 1 = looking forward, 0 = looking backward
    int frameCount;
} WomenSwimming;


/*----- Function: setIsForward -----

 PURPOSE: Sets the isForward state of a WomenSwimming object to a random value (0 or 1).
        Using complicated mathematics that can be translated in Assembly instead of the rand 
        function in C.

 INPUT: WomenSwimming*: a pointer to an object containing a woman swimming
        int isForward: the value to set isForward to (0 or 1)

 OUTPUT: The isForward field of the WomenSwimming object is set to the provided value.

 ASSUMPTIONS: The seed variable is properly initialized and updated elsewhere in the code.
 
*/
void setIsForward(WomenSwimming* womenSwimming, int isForward);



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

#endif