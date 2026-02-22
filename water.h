
#ifndef WATER_H
#define WATER_H

/*
    This file defines the struct that contains all the information about the water in the game,
    which includes its position, as well as the functions that manipulate that state. 
    
    Team names: Meagan Valderrama, Paolo Deocareza, and Gaurik Khullar
    @authors Meagan Valderrama
*/
typedef struct {
    unsigned int x,y;
} Water;


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

/*----- Function: isWaterColliding -----

 PURPOSE: Checks for collisions between Chuck and the water and updates Chuck's collision state accordingly.

 INPUT: Water*: a pointer to the model containing the water object
        Chuck*: a pointer to the model containing the player character Chuck

 OUTPUT: Chuck struct with updated collision state if a collision with water is detected.

 ASSUMPTIONS: This function assumes
        - Chuck's position and dimensions are defined such that his edges can be checked for collision 
        with the water's edges
        - The water object has defined dimensions that can be used to check for collisions with Chuck
*/
/* void isWaterColliding(Water* water, Chuck* chuck); */

#endif
