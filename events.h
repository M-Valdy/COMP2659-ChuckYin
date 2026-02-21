#include "model.h"

#ifndef EVENTS_H
#define EVENTS_H

/*
    This file contains the function prototype for handling events in the game.
    It defines a function that processes events and updates the model accordingly.

    Team names: Meagan Valderrama, Paolo Deocareza, and Gaurik Khullar
    @author Paolo Deocareza
*/




/*----- Function: event_handler -----

 PURPOSE: Processes events and updates the model accordingly.

 INPUT: Model*: a pointer to the model containing all game objects and their states

 OUTPUT: Updated Model struct with new positions, states, and any changes resulting from events

 ASSUMPTIONS: This function assumes that the model is properly initialized and that 
            events have been processed and are available for updating the model.
*/
void event_handler(Model *model);

#endif