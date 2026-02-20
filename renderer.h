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


#endif