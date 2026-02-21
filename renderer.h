#include "types.h"
#include "model.h"
#include "raster.h"

#ifndef RENDERER_H
#define RENDERER_H

/*----- Function: render -----

 PURPOSE: Renders the entire game screen by drawing all game objects in the model.

 INPUT: Model*: a pointer to the model containing all game objects
        Address(UINT32*): to the start of the screen

 OUTPUT: Entire game screen with all game objects rendered at their current positions

*/
void render(const Model *model, UINT8 *base);

/*----- Function: render_Chuck -----
    PURPOSE: Renders Chuck on the screen at his current position.
    
    INPUT: Chuck*: a pointer to the Chuck object in the model
            Address(UINT8*): to the start of the screen
    
    OUTPUT: Chuck rendered on the screen at his current position
*/
void render_Chuck(const Chuck* chuck, UINT8 *base);

/*----- Function: render_WomenWalking -----
    PURPOSE: Renders the women walking on the screen at their current positions.
    
    INPUT: WomenWalking*: a pointer to the array of WomenWalking objects in the model
           Address(UINT8*): to the start of the screen

    OUTPUT: Women walking rendered on the screen at their current positions
*/
void render_WomenWalking(const WomenWalking* womenWalking, UINT8 *base);

/*----- Function: render_WomenSwimming -----
    PURPOSE: Renders the women swimming on the screen at their current positions.

    INPUT: WomenSwimming*: a pointer to the array of WomenSwimming objects in the model
           Address(UINT8*): to the start of the screen

    OUTPUT: Women swimming rendered on the screen at their current positions
*/
void render_WomenSwimming(const WomenSwimming* womenSwimming, UINT8 *base);


/*----- Function: render_tree -----
    PURPOSE: Renders the trees on the screen at their current positions.

    INPUT: Tree*: a pointer to the array of Tree objects in the model
           Address(UINT8*): to the start of the screen

    OUTPUT: Trees rendered on the screen at their current positions
*/
void render_tree(Tree* Tree);



/*----- Function: render_water -----
    PURPOSE: Renders the water on the screen at its current position.

    INPUT: Water*: a pointer to the array of Water objects in the model
           Address(UINT8*): to the start of the screen

    OUTPUT: Water rendered on the screen at its current position
*/
void render_water(Water* water);


/*----- Function: render_road -----
    PURPOSE: Renders the road on the screen at its current position.

    INPUT: Road*: a pointer to the array of Road objects in the model
           Address(UINT8*): to the start of the screen

    OUTPUT: Road rendered on the screen at its current position
*/
void render_road(Road* road);

#endif