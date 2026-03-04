#include "renderer.h"

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