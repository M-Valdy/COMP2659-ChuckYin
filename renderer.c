#include "renderer.h"


 /* Also known as the "master render" function */
void render_initial_state(const Model *model, UINT32 *base) {

    

}

void render_Chuck(UINT32 *base, UINT16 row, UINT16 col, Chuck* chuck){
    initChuck(chuck, row, col);
    plot_32_bitmap(base, row, col, CHUCK_HEIGHT, Chuck_bitmap);
}

void render_WomenWalking(UINT32 *base, UINT16 row, UINT16 col, WomenWalking* womenWalking){
    initWomenWalking(womenWalking, row, col);
    plot_32_bitmap(base, row, col, WALKER_HEIGHT, womenWalking_bitmap);
}

void render_women_swimming_forward(UINT32 *base, UINT16 row, UINT16 col, WomenSwimming* womenSwimming){
    initWomenSwimming(womenSwimming, row, col);
    plot_32_bitmap(base, row, col, SWIMMER_HEIGHT, womenSwimming_forward_bitmap);
}

void render_women_swimming_backward(UINT32 *base, UINT16 row, UINT16 col, WomenSwimming* womenSwimming){
    initWomenSwimming(womenSwimming, row, col);
    plot_32_bitmap(base, row, col, SWIMMER_HEIGHT, womenSwimming_backward_bitmap);
}

void render_tree(UINT32 *base, UINT16 row, UINT16 col, Tree* tree) {
    initTree(tree, row, col);
    plot_32_bitmap(base, row, col, TREE_HEIGHT, tree_bitmap);
}

void render_water(UINT32 *base, UINT16 row, UINT16 col, Water* water){
    initWater(water, row, col);
    plot_32_bitmap(base, row, col, WATER_HEIGHT, water_bitmap);
}

void render_road_upper(UINT32 *base, UINT16 row, UINT16 col, Road* road){
    initRoad(road, row, col, 0);
    plot_32_bitmap(base, row, col, ROAD_HEIGHT, road_bitmap_upper);
}
void render_road_lower(UINT32 *base, UINT16 row, UINT16 col, Road* road){
    initRoad(road, row, col, 1);
    plot_32_bitmap(base, row, col, ROAD_HEIGHT, road_bitmap_lower);
}

