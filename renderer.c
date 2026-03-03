#include "renderer.h"


 /* Also known as the "master render" function */
void render_initial_state(const Model *model, UINT32 *base) {
    clear_screen(base);
    

}

void render_Chuck(UINT32 *base, UINT16 row, UINT16 col, Chuck* chuck){
    initChuck(chuck, row, col);
    plot_32_bitmap(base, row, col, CHUCK_HEIGHT, Chuck_bitmap);
}

void render_WomenWalking(UINT32 *base, UINT16 row, UINT16 col, WomenWalking* womenWalking){
    initWomenWalking(womenWalking, row, col);
    plot_32_bitmap(base, row, col, WALKER_HEIGHT, womenWalking_bitmap);
}

void render_women_swimming(UINT32 *base, UINT16 row, UINT16 col, WomenSwimming* womenSwimming){
    initWomenSwimming(womenSwimming, row, col);
    if (womenSwimming->isForward) {
        plot_32_bitmap(base, row, col, SWIMMER_HEIGHT, womenSwimming_forward_bitmap);
    } else {
        plot_32_bitmap(base, row, col, SWIMMER_HEIGHT, womenSwimming_backward_bitmap);
    }
}

void render_water(UINT32 *base, UINT16 row, UINT16 col, Water* water){
    initWater(water, row, col);
    plot_32_bitmap(base, row, col, WATER_HEIGHT, water_bitmap);
}

void render_road(UINT32 *base, UINT16 row, UINT16 col, Road* road, int isLower){
    initRoad(road, row, col, isLower);
    if (road->isLower == 0) {
        plot_32_bitmap(base, row, col, ROAD_HEIGHT, road_bitmap_upper);
    } else {
        plot_32_bitmap(base, row, col, ROAD_HEIGHT, road_bitmap_lower);
    }
}

