#ifndef MODEL_H
#define MODEL_H

#include "Chuck.h"
#include "w-walk.h"
#include "w-swim.h"
#include "tree.h"
#include "water.h"
#include "road.h"

/*

    This file defines the struct that contains all the structures that represent the state 
    of all game objects in the model, which includes the player character Chuck, the women walking, 
    the women swimming, the trees, the water, and the roads.

    It also defines the function that initializes the model by setting the initial positions 
    and states of all game objects.

    Team names: Meagan Valderrama, Paolo Deocareza, and Gaurik Khullar
    @authors Meagan Valderrama, Paolo Deocareza
*/


typedef struct {
    int gameOver;
    int crossCount;
    Chuck chuck;
    WomenWalking womenWalking[15];
    WomenSwimming womenSwimming[15];
    Water water[120]; /* need 40 Water objects per stream (20 to cover the whole screen width, double it to make it 64 pixels high), 3 water streams total */ 
    Road road[120]; /* need 40 road segments per road (20 to cover the whole screen width, double it to make it 64 pixels high), 3 roads total */ 
} Model;


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