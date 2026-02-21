#include "Chuck.h";
/*
    This file defines the struct that contains all the information about the trees in the game,
    which includes their position and whether they're colliding with Chuck or not, as well as the functions that manipulate that state. 
    
    Team names: Meagan Valderrama, Paolo Deocareza, and Gaurik Khullar
    @authors Meagan Valderrama
*/

#ifndef TREE_H
#define TREE_H


typedef struct {
    unsigned int x,y;
    int isColliding;
} Tree;


/*----- Function: initTree -----

 PURPOSE: Initializes the Tree struct by setting its initial position and collision state.

 INPUT: Tree*: a pointer to the model containing the tree object
        unsigned int x: the initial x position of the tree
        unsigned int y: the initial y position of the tree

 OUTPUT: Tree struct initialized with the provided position and default collision state.

 ASSUMPTIONS: The renderer is working with the same coordinate system as the one used to 
       initialize the tree's position, and that the initial position provided is within 
       the bounds of the game screen.

*/
void initTree(Tree* tree, unsigned int x, unsigned int y);


/*----- Function: isTreeColliding -----

 PURPOSE: Checks for collision between Chuck and a Tree and updates Chuck's collision state accordingly.

 INPUT: Tree*: a pointer to the model containing the tree object
        Chuck*: a pointer to the model containing the player character Chuck

 OUTPUT: Chuck struct with updated collision state based on whether there is a collision with the tree or not.

 ASSUMPTIONS: This function assumes
        - Chuck's position and dimensions are defined such that his edges can be checked for collision 
        with the tree's edges
        - The tree object has defined dimensions that can be used to check for collisions with Chuck
*/
void isTreeColliding(Tree* tree, Chuck* chuck);

#endif