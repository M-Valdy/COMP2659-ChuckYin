#ifndef CHUCK_H
#define CHUCK_H
/*
   This file defines the struct that contains all the information about Chuck's state,
   which includes his position, whether he's walking or not, how much he's moving in the x and y directions, 
   whether he's colliding with an obstacle or not, and whether he's allowed to move in each direction or not,
   as well as the functions that manipulate that state. 

   Team names: Meagan Valderrama, Paolo Deocareza, and Gaurik Khullar
   @authors Meagan Valderrama, Paolo Deocareza (the author of each specific function is 
   in the comment above the function definition in Chuck.c)

*/
#define CHUCK_HORIZONTAL 8

typedef struct {
    unsigned int x,y;
    int isWalking;
    int deltaX, deltaY;
    int isColliding; // 1 = obstacle collision, 0 = no collision, 2 = death collision
    int canMoveRight, canMoveLeft;
    int canMoveUp, canMoveDown;
} Chuck;


extern int chuckBitmap[CHUCK_HORIZONTAL]; // this bitmap represents Chuck's sprite, its defined in Chuck.c

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
void initChuck(Chuck* chuck, unsigned int x, unsigned int y);


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

/*----- Function: checkXCollision -----

 PURPOSE: Checks for collisions between Chuck and the water in the x direction and updates movement permissions accordingly.

 INPUT: Chuck*: a pointer to the model containing the player character Chuck
        Water*: a pointer to the water object in the model

 OUTPUT: Chuck struct with updated movement permissions for left and right movement based on collision state with water

 ASSUMPTIONS: This function assumes
        - Chuck's position and dimensions are defined such that his edges can be checked for collision 
        with the water's edges
        - The water object has defined dimensions that can be used to check for collisions with Chuck
*/
void checkXCollision(Chuck* chuck, Water* water);


/*----- Function: checkYCollision -----

 PURPOSE: Checks for collisions between Chuck and the water in the y direction and updates movement permissions accordingly.

 INPUT: Chuck*: a pointer to the model containing the player character Chuck
        Water*: a pointer to the water object in the model

 OUTPUT: Chuck struct with updated movement permissions for up and down movement based on collision state with water

 ASSUMPTIONS: This function assumes
        - Chuck's position and dimensions are defined such that his edges can be checked for collision 
        with the water's edges
        - The water object has defined dimensions that can be used to check for collisions with Chuck
*/
void checkYCollision(Chuck* chuck, Water* water);

#endif
