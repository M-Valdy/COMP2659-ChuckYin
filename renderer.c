#include "renderer.h"

void render_initial_state(const Model *model, UINT32 *base) {
    clear_screen(base);
}

void render_Chuck(UINT32 *base, UINT16 row, UINT16 col, const Chuck* chuck){
    /*initChuck(chuck, row, col);*/
    plot_32_bitmap(base, row, col, CHUCK_HEIGHT, Chuck_bitmap);
}

void render_WomenWalking(UINT32 *base, UINT16 row, UINT16 col, const WomenWalking* womenWalking){
    /*initWomenWalking(womenWalking, row, col);*/
    plot_32_bitmap(base, row, col, WALKER_HEIGHT, womenWalking_bitmap);
}

void render_women_swimming(UINT32 *base, UINT16 row, UINT16 col, const WomenSwimming* womenSwimming){
    /*initWomenSwimming(womenSwimming, row, col);*/
    if (womenSwimming->isForward == 1) {
        plot_32_bitmap(base, row, col, SWIMMER_HEIGHT, womenSwimming_forward_bitmap);
    } else if (womenSwimming->isForward == 0) {
        plot_32_bitmap(base, row, col, SWIMMER_HEIGHT, womenSwimming_backward_bitmap);
    }
}

void render_water(UINT32 *base, UINT16 row, UINT16 col, const Water* water){
    /*initWater(water, row, col);*/
    plot_32_bitmap(base, row, col, WATER_HEIGHT, water_bitmap);
}

void render_road(UINT32 *base, UINT16 row, UINT16 col, const Road* road){
    /*initRoad(road, row, col, isLower);*/
    if (road->isLower == 0) {
        plot_32_bitmap(base, row, col, ROAD_HEIGHT, road_bitmap_upper);
    } else {
        plot_32_bitmap(base, row, col, ROAD_HEIGHT, road_bitmap_lower);
    }
}

/* @author Paolo 
    probably dont need to update the background after the first time right?
*/
void master_render(const Model *model, UINT32 *base) {
    int i;
    for (i = 0; i < 120; i++) {
        if (i < 80) {
            render_water(base, model->water[i].y, model->water[i].x, &model->water[i]);
        }
        render_road(base, model->road[i].y, model->road[i].x, &model->road[i]);
    }
    for (i = 0; i < 15; i++) {
        render_WomenWalking(base, model->womenWalking[i].y, model->womenWalking[i].x, &model->womenWalking[i]);
    }
    for (i = 0; i < 30; i++) {
        render_women_swimming(base, model->womenSwimming[i].y, model->womenSwimming[i].x, &model->womenSwimming[i]);
        if (model->womenSwimming[i].frameCount <= 31 && model->womenSwimming[i].frameCount >= 25) {
            plot_square(base, model->womenSwimming[i].y, model->womenSwimming[i].x, SWIMMER_HEIGHT);
        }
    }
    render_Chuck(base, model->chuck.y, model->chuck.x, &model->chuck);
    plot_string(base, 390, 5, "Cross Count is");
    plot_character(base, 390, 125, model->crossCount + '0');
}