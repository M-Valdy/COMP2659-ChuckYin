#include "renderer.h"

/* @author Paolo */
void render_initial_state(const Model *model, UINT32 *base) {
    int i;
    clear_screen(base);
    for (i = 0; i < NUM_ROADS; i++) {
        render_road(base, model->road[i].y, model->road[i].x, &model->road[i]);
    }
    for (i = 0; i < NUM_WATER; i++) {
        render_water(base, model->water[i].y, model->water[i].x, &model->water[i]);
    }
    for (i = 0; i < NUM_WALKERS; i++) {
        render_WomenWalking(base, model->womenWalking[i].y, model->womenWalking[i].x, &model->womenWalking[i]);
    }
    for (i = 0; i < NUM_SWIMMERS; i++) {
        render_women_swimming(base, model->womenSwimming[i].y, model->womenSwimming[i].x, &model->womenSwimming[i]);
        if (model->womenSwimming[i].frameCount <= 31 && model->womenSwimming[i].frameCount >= 25) {
            plot_square(base, model->womenSwimming[i].y, model->womenSwimming[i].x, SWIMMER_HEIGHT);
        }
    }
    render_Chuck(base, model->chuck.y, model->chuck.x, &model->chuck);
    plot_string(base, 0, 15, "Cross Count is");
    plot_character(base, 0, 135, model->crossCount + '0');
}

void render_Chuck(UINT32 *base, UINT16 row, UINT16 col, const Chuck* chuck){
    plot_32_bitmap(base, row, col, CHUCK_HEIGHT, Chuck_bitmap);
}

void render_WomenWalking(UINT32 *base, UINT16 row, UINT16 col, const WomenWalking* womenWalking){
    plot_32_bitmap(base, row, col, WALKER_HEIGHT, womenWalking_bitmap);
}

void render_women_swimming(UINT32 *base, UINT16 row, UINT16 col, const WomenSwimming* womenSwimming){
    if (womenSwimming->isForward == 1) {
        plot_32_bitmap(base, row, col, SWIMMER_HEIGHT, womenSwimming_forward_bitmap);
    } else if (womenSwimming->isForward == 0) {
        plot_32_bitmap(base, row, col, SWIMMER_HEIGHT, womenSwimming_backward_bitmap);
    }
}

void render_water(UINT32 *base, UINT16 row, UINT16 col, const Water* water){
    plot_32_bitmap(base, row, col, WATER_HEIGHT, water_bitmap);
}

void render_road(UINT32 *base, UINT16 row, UINT16 col, const Road* road){
    if (road->isLower == 0) {
        plot_32_bitmap(base, row, col, ROAD_HEIGHT, road_bitmap_upper);
    } else {
        plot_32_bitmap(base, row, col, ROAD_HEIGHT, road_bitmap_lower);
    }
}

/* @author Paolo 
    i will try my best to make the code look cleaner... some other day :D
*/
void master_render(const Model *model, UINT32 *base) {
    int i;
    int h;
    int l;
    if (model->cheatsOn == 1) {
        plot_string(base, 0, 280, "Cheats on!");
    } else {
        clear_region(base, 0, 280, 8, 80);
    }
    for (h = 0; h < 2; h++) {
        for (i = 0; i < NUM_ROADS; i++) {
            if (model->road[i].isColliding == 1 &&
                (model->chuck.oldx != model->chuck.x || model->chuck.oldy != model->chuck.y) ) {
                clear_region(base, model->road[i].y, model->road[i].x, ROAD_HEIGHT, ROAD_HEIGHT);
                if (h == 1) {
                    render_road(base, model->road[i].y, model->road[i].x, &model->road[i]);
                    
                }
            }
        }
        /*for (i = 0; i < 60; i++) {
            render_water(base, model->water[i].y, model->water[i].x, &model->water[i]);
        }*/
        for (i = 0; i < NUM_WALKERS; i++) {
            clear_region(base, model->womenWalking[i].oldy, model->womenWalking[i].oldx, WALKER_HEIGHT, WALKER_HEIGHT);
            if (model->womenWalking[i].oldy == 16) {
                render_road(base, model->womenWalking[i].oldy, model->womenWalking[i].oldx, &model->road[0]);
            } else {
                render_road(base, model->womenWalking[i].oldy+1, model->womenWalking[i].oldx, &model->road[0]);
            }
             /* turns out that render_road doesn't need to render at their position, so you can render two road[0] */
            if (h == 1) { 
                render_WomenWalking(base, model->womenWalking[i].y, model->womenWalking[i].x, &model->womenWalking[i]);
            }
        }
        for (i = 0; i < NUM_SWIMMERS; i++) {
            if (model->womenSwimming[i].frameCount <= 1 || model->womenSwimming[i].isColliding == 1) {
                clear_region(base, model->womenSwimming[i].y, model->womenSwimming[i].x, SWIMMER_HEIGHT, SWIMMER_HEIGHT);
                if (h == 1) {
                    render_women_swimming(base, model->womenSwimming[i].y, model->womenSwimming[i].x, &model->womenSwimming[i]);
                }
            } /* TO DO: because of how i made the collision less tight and pixel perfect (i added -6), it won't always repair object image)*/
            if (model->womenSwimming[i].frameCount <= MAX_FRAMES && model->womenSwimming[i].frameCount >= (int)(MAX_FRAMES*0.75) && h == 1) {
                plot_square(base, model->womenSwimming[i].y, model->womenSwimming[i].x, SWIMMER_HEIGHT);
            }
        }
        if (model->oldCrossCount != model->crossCount ) {
            clear_region(base, 0, 15, 8, 140);
            if (h == 1) {
                plot_string(base, 0, 15, "Cross Count is");
                plot_character(base, 0, 135, model->crossCount + '0');
                updateScore(model);
            }
        }
        if (model->chuck.x != model->chuck.oldx || model->chuck.y != model->chuck.oldy) {
            clear_region(base, model->chuck.oldy, model->chuck.oldx, CHUCK_HEIGHT, CHUCK_HEIGHT);
            if (h == 1) {
                render_Chuck(base, model->chuck.y, model->chuck.x, &model->chuck); 
            }
        }
    }
}

/* @author Paolo 
    use this for testing
*/
void old_master_render(const Model *model, UINT32 *base) {
    int i;
    int h;
    int l;
    clear_screen(base);
    for (i = 0; i < NUM_ROADS; i++) {
        render_road(base, model->road[i].y, model->road[i].x, &model->road[i]);
    }
    for (i = 0; i < NUM_SWIMMERS; i++) {
        render_women_swimming(base, model->womenSwimming[i].y, model->womenSwimming[i].x, &model->womenSwimming[i]);
    }
    for (i = 0; i < NUM_WATER; i++) {
        render_water(base, model->water[i].y, model->water[i].x, &model->water[i]);
    }
    for (i = 0; i < NUM_WALKERS; i++) {
        render_WomenWalking(base, model->womenWalking[i].y, model->womenWalking[i].x, &model->womenWalking[i]);
    }
    render_Chuck(base, model->chuck.y, model->chuck.x, &model->chuck);
}