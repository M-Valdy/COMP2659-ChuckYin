#include "renderer.h"

/* void plot_bitmap_32(UINT32 *base, UINT16 row, UINT16 col, UINT16 height, const UINT32 *bitmap); */

/* @author Paolo 
    probably dont need to update the background after the first time right?
*/
void master_render(const Model *model, UINT8 *base) {
    int i;
    for (i = 0; i < 120; i++) {
        render_water(base, &model->water[i].x, &model->water[i].y, water_bitmap[WATER_HEIGHT]);
        if (&model->road[i].isLower == 0) {
            render_road_upper(base, &model->road[i].x, &model->road[i].y, road_bitmap_upper[ROAD_HEIGHT]);
        } else if (&model->road[i].isLower == 1) {
            render_road_lower(base, &model->road[i].x, &model->road[i].y, road_bitmap_lower[ROAD_HEIGHT]);
        }
    }
    for (i = 0; i < 15; i++) {
        render_WomenWalking(base, &model->womenWalking[i].x, &model->womenWalking[i].y, womenWalking_bitmap[WALKER_HEIGHT]);
        if (&model->womenSwimming[i].isForward == 1) {
            render_women_swimming_forward(base, &model->womenSwimming[i].x, &model->womenSwimming[i].y, womenSwimming_forward_bitmap[SWIMMER_HEIGHT]);
        } else if (&model->womenSwimming[i].isForward == 0) {
            render_women_swimming_backward(base, &model->womenSwimming[i].x, &model->womenSwimming[i].y, womenSwimming_backward_bitmap[SWIMMER_HEIGHT]);
        }
    }
    render_Chuck(base, &model->chuck.x, &model->chuck.y, Chuck_bitmap[CHUCK_HEIGHT]);
}

/* @author Gaurik */
void render_Chuck(UINT32 *base, UINT16 row, UINT16 col, const Chuck* chuck){
    plot_bitmap_32(base, row, col, CHUCK_HEIGHT, Chuck_bitmap);
}

/* @author Gaurik */
void render_WomenWalking(UINT32 *base, UINT16 row, UINT16 col, const WomenWalking* womenWalking_bitmap){
    plot_bitmap_32(base, row, col, WALKER_HEIGHT, womenWalking_bitmap);
}

/* @author Gaurik */
void render_women_swimming_forward(UINT32 *base, UINT16 row, UINT16 col, const WomenSwimming* womenSwimming_forward_bitmap){
    plot_bitmap_32(base, row, col, SWIMMER_HEIGHT, womenSwimming_forward_bitmap);
}

/* @author Gaurik */
void render_women_swimming_backward(UINT32 *base, UINT16 row, UINT16 col, const WomenSwimming* womenSwimming_backward_bitmap){
    plot_bitmap_32(base, row, col, SWIMMER_HEIGHT, womenSwimming_backward_bitmap);
}

/* @author Gaurik */
void render_tree(UINT32 *base, UINT16 row, UINT16 col, Tree* tree_bitmap) {
    plot_bitmap_32(base, row, col, TREE_HEIGHT, tree_bitmap);
}

/* @author Gaurik */
void render_water(UINT32 *base, UINT16 row, UINT16 col, Water* water_bitmap){
    plot_bitmap_32(base, row, col, WATER_HEIGHT, water_bitmap);
}

/* @author Gaurik */
void render_road_upper(UINT32 *base, UINT16 row, UINT16 col, Road* road_bitmap){
    plot_bitmap_32(base, row, col, ROAD_HEIGHT,road_bitmap);
}

