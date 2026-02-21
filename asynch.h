#include "model.h"
/*
    This file contains the function prototypes for asynchronous button handling in the game.
    It defines functions that handle input events for the W, A, S, and D keys.

    Team names: Meagan Valderrama, Paolo Deocareza, and Gaurik Khullar
    @authors Paolo Deocareza
*/

/*----- Function: asynch_button_W -----

 PURPOSE: Handles the asynchronous input event for the W key, which is typically used for moving up in the game.

 INPUT: Model*: a pointer to the model containing all game objects and their states

 OUTPUT: Updates the model's state to reflect the input from the W key, such as setting Chuck's movement direction to up.

 ASSUMPTIONS: This function assumes that the model is properly initialized and that 
            Chuck's state can be updated based on the input event.
*/
void asynch_button_W(Model *model);


/*----- Function: asynch_button_A -----

 PURPOSE: Handles the asynchronous input event for the A key, which is typically used for moving left in the game.

 INPUT: Model*: a pointer to the model containing all game objects and their states

 OUTPUT: Updates the model's state to reflect the input from the A key, such as setting Chuck's movement direction to left.

 ASSUMPTIONS: This function assumes that the model is properly initialized and that 
            Chuck's state can be updated based on the input event.
*/
void asynch_button_A(Model *model);


/*----- Function: asynch_button_S -----

 PURPOSE: Handles the asynchronous input event for the S key, which is typically used for moving down in the game.

 INPUT: Model*: a pointer to the model containing all game objects and their states

 OUTPUT: Updates the model's state to reflect the input from the S key, such as setting Chuck's movement direction to down.

 ASSUMPTIONS: This function assumes that the model is properly initialized and that 
            Chuck's state can be updated based on the input event.
*/
void asynch_button_S(Model *model);


/*----- Function: asynch_button_D -----

 PURPOSE: Handles the asynchronous input event for the D key, which is typically used for moving right in the game.

 INPUT: Model*: a pointer to the model containing all game objects and their states

 OUTPUT: Updates the model's state to reflect the input from the D key, such as setting Chuck's movement direction to right.

 ASSUMPTIONS: This function assumes that the model is properly initialized and that 
            Chuck's state can be updated based on the input event.
*/
void asynch_button_D(Model *model);