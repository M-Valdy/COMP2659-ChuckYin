#include "model.h"

#ifndef COND_H
#define COND_H

/* @author Paolo Deocareza

    This file contains the function prototype for updating the game model based on the current 
    conditions of the game, such as player input, collisions, and movement. 
    It defines a function that processes the current state of the model and updates it accordingly.

    Team names: Meagan Valderrama, Paolo Deocareza, and Gaurik Khullar
*/



/*----Function: cond_update -----

 PURPOSE: Updates the state of the game model based on the current conditions of the game, such as player input, collisions, and movement.

 INPUT: Model*: a pointer to the model containing all game objects and their states

 OUTPUT: Updated Model struct with new positions, states, and any changes resulting from collisions or player actions

 ASSUMPTIONS: This function assumes
        - The model is properly initialized and contains valid game objects
        - Player input has been processed and is available for updating the model
        - Collision detection functions have been called before this function to update collision states in the model
*/
void cond_update(Model *model);


#endif