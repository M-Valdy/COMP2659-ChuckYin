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
    save_new_regions(base, model);
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
    if (womenSwimming->frameCount <= MAX_FRAMES && womenSwimming->frameCount >= (int)(MAX_FRAMES*0.75)) {
        plot_square(base, womenSwimming->y, womenSwimming->x, SWIMMER_HEIGHT);
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

/* @author Paolo */
void master_render(const Model *model, UINT16 *base) {
    restore_old_regions(base, model);
    save_new_regions(base, model);
    render_dynamic_objects(base, model);
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

void save_region(UINT16 *base, int x, int y, int width, int height, UINT16 *background) {
    int row;
    UINT16 *screen_ptr;
    UINT16 *bg_ptr = background;

    for (row = 0; row < height; row++) {
        screen_ptr = base + ((y + row) * 40) + (x >> 4);

        /* width assumed 32 pixels = so 2 words */
        bg_ptr[0] = screen_ptr[0];
        bg_ptr[1] = screen_ptr[1];

        bg_ptr += 2;
    }
}

void restore_region(UINT16 *base, int x, int y, int width, int height, UINT16 *background) {
    int row;
    UINT16 *screen_ptr;
    UINT16 *bg_ptr = background;

    for (row = 0; row < height; row++) {
        screen_ptr = base + ((y + row) * 40) + (x >> 4);

        screen_ptr[0] = bg_ptr[0];
        screen_ptr[1] = bg_ptr[1];

        bg_ptr += 2;
    }
}

void restore_old_regions(UINT16 *base, Model *model) {
    int i;

    for (i = 0; i < NUM_SWIMMERS; i++) {
        restore_region(base, model->womenSwimming[i].x, model->womenSwimming[i].y, 32, 32, model->womenSwimming[i].saved_bg);
    }
    for (i = 0; i < NUM_WALKERS; i++) {
        restore_region(base, model->womenWalking[i].oldx, model->womenWalking[i].oldy, 32, 32, model->womenWalking[i].saved_bg);
    }
    restore_region(base, model->chuck.oldx, model->chuck.oldy, 32, 32, model->chuck.saved_bg);
}

void save_new_regions(UINT16 *base, Model *model) {
    int i;

    for (i = 0; i < NUM_SWIMMERS; i++) { 
        save_region(base, model->womenSwimming[i].x, model->womenSwimming[i].y, 32, 32, model->womenSwimming[i].saved_bg);
    }
    for (i = 0; i < NUM_WALKERS; i++) {
        save_region(base, model->womenWalking[i].x, model->womenWalking[i].y, 32, 32, model->womenWalking[i].saved_bg);
    }
    save_region(base, model->chuck.x, model->chuck.y, 32, 32, model->chuck.saved_bg); 
}

void render_dynamic_objects(UINT16 *base, Model *model) {
    int i;

    for (i = 0; i < NUM_SWIMMERS; i++) {
        /*if (model->womenSwimming[i].frameCount <= 1 || model->womenSwimming[i].isColliding == 1) {}*/
        render_women_swimming(base, model->womenSwimming[i].y, model->womenSwimming[i].x, &model->womenSwimming[i]);
    }
    for (i = 0; i < NUM_WALKERS; i++) {
        render_WomenWalking(base, model->womenWalking[i].y, model->womenWalking[i].x, &model->womenWalking[i]);
    }
    if (model->oldCrossCount != model->crossCount ) {
        clear_region(base, 0, 15, 8, 140);
        plot_string(base, 0, 15, "Cross Count is");
        plot_character(base, 0, 135, model->crossCount + '0');
        updateScore(model);
    }
    if (model->cheatsOn == 1) {
        plot_string(base, 0, 280, "Cheats on!");
    } else {
        clear_region(base, 0, 280, 8, 80);
    }
    render_Chuck(base, model->chuck.y, model->chuck.x, &model->chuck);
}