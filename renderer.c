#include "renderer.h"

/* void plot_bitmap_32(UINT32 *base, UINT16 row, UINT16 col, UINT16 height, const UINT32 *bitmap); */

void render_intial_state(const Model *model, UINT8 *base); /* Also known as the "master render" function */

void render_Chuck(UINT32 *base, UINT16 row, UINT16 col, const Chuck* chuck){
    plot_bitmap_32(base, row, col, CHUCK_HEIGHT, Chuck_bitmap);
}

void render_WomenWalking(UINT32 *base, UINT16 row, UINT16 col, const WomenWalking* womenWalking_bitmap){
    plot_bitmap_32(base, row, col, WALKER_HEIGHT, womenWalking_bitmap);
}

void render_women_swimming_forward(UINT32 *base, UINT16 row, UINT16 col, const WomenSwimming* womenSwimming_forward_bitmap){
    plot_bitmap_32(base, row, col, SWIMMER_HEIGHT, womenSwimming_forward_bitmap);
}

void render_women_swimming_backward(UINT32 *base, UINT16 row, UINT16 col, const WomenSwimming* womenSwimming_backward_bitmap){
    plot_bitmap_32(base, row, col, SWIMMER_HEIGHT, womenSwimming_backward_bitmap);
}

void render_tree(UINT32 *base, UINT16 row, UINT16 col, Tree* tree_bitmap) {
    plot_bitmap_32(base, row, col, TREE_HEIGHT, tree_bitmap);
}

void render_water(UINT32 *base, UINT16 row, UINT16 col, Water* water_bitmap){
    plot_bitmap_32(base, row, col, WATER_HEIGHT, water_bitmap);
}

void render_road_upper(UINT32 *base, UINT16 row, UINT16 col, Road* road_bitmap){
    plot_bitmap_32(base, row, col, ROAD_HEIGHT,road_bitmap);
}

