#ifndef RENDERER_H
#define RENDERER_H

#include "types.h"
#include "model.h"
#include "raster.h"

/*----- Function: render -----

 PURPOSE: Renders the entire game screen by drawing all game objects in the model.

 INPUT: Model*: a pointer to the model containing all game objects
        Address(UINT32*): to the start of the screen

 OUTPUT: Entire game screen with all game objects rendered at their current positions

*/
void render_intial_state(const Model *model, UINT8 *base);


void render_Chuck(UINT32 *base, UINT16 row, UINT16 col, const Chuck* chuck);

/*----- Function: render_WomenWalking -----
    PURPOSE: Renders the women walking on the screen at their current positions.
    
    INPUT: WomenWalking*: a pointer to the array of WomenWalking objects in the model
           Address(UINT8*): to the start of the screen

    OUTPUT: Women walking rendered on the screen at their current positions
*/
void render_WomenWalking(UINT32 *base, UINT16 row, UINT16 col, const WomenWalking* womenWalking_bitmap);

/*----- Function: render_WomenSwimming -----
    PURPOSE: Renders the women swimming on the screen at their current positions.

    INPUT: WomenSwimming*: a pointer to the array of WomenSwimming objects in the model
           Address(UINT8*): to the start of the screen

    OUTPUT: Women swimming rendered on the screen at their current positions
*/
void render_women_swimming_forward(UINT32 *base, UINT16 row, UINT16 col, const WomenSwimming* womenSwimming_forward_bitmap);

void render_women_swimming_backward(UINT32 *base, UINT16 row, UINT16 col, const WomenSwimming* womenSwimming_forward_bitmap);

/*----- Function: render_tree -----
    PURPOSE: Renders the trees on the screen at their current positions.

    INPUT: Tree*: a pointer to the array of Tree objects in the model
           Address(UINT8*): to the start of the screen

    OUTPUT: Trees rendered on the screen at their current positions
*/
void render_tree(UINT32 *base, UINT16 row, UINT16 col, Tree* tree_bitmap);

/*----- Function: render_water -----
    PURPOSE: Renders the water on the screen at its current position.

    INPUT: Water*: a pointer to the array of Water objects in the model
           Address(UINT8*): to the start of the screen

    OUTPUT: Water rendered on the screen at its current position
*/
void render_water(UINT32 *base, UINT16 row, UINT16 col, Water* water_bitmap);


/*----- Function: render_road -----
    PURPOSE: Renders the road on the screen at its current position.

    INPUT: Road*: a pointer to the array of Road objects in the model
           Address(UINT8*): to the start of the screen

    OUTPUT: Road rendered on the screen at its current position
*/
void render_road_upper(UINT32 *base, UINT16 row, UINT16 col, Road* road_bitmap);

#endif