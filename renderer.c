#include "renderer.h"

void render_initial_state(const Model *model, UINT32 *base) {
    int i;
    clear_screen(base);
    for (i = 0; i < 120; i++) {
        if (i < 20) {
            render_water(base, model->water[i].y, model->water[i].x, &model->water[i]);
        }
        render_road(base, model->road[i].y, model->road[i].x, &model->road[i]);
    }
    /*for (i = 0; i < 15; i++) {
        render_WomenWalking(base, model->womenWalking[i].y, model->womenWalking[i].x, &model->womenWalking[i]);
    }*/
    render_WomenWalking(base, model->womenWalking[1].y, model->womenWalking[1].x, &model->womenWalking[1]);
    render_WomenWalking(base, model->womenWalking[5].y, model->womenWalking[5].x, &model->womenWalking[5]);
    render_WomenWalking(base, model->womenWalking[11].y, model->womenWalking[11].x, &model->womenWalking[11]);
    for (i = 0; i < 30; i++) {
        render_women_swimming(base, model->womenSwimming[i].y, model->womenSwimming[i].x, &model->womenSwimming[i]);
        if (model->womenSwimming[i].frameCount <= 31 && model->womenSwimming[i].frameCount >= 25) {
            plot_square(base, model->womenSwimming[i].y, model->womenSwimming[i].x, SWIMMER_HEIGHT);
        }
    }
    render_Chuck(base, model->chuck.y, model->chuck.x, &model->chuck);
    plot_string(base, 390, 15, "Cross Count is");
    plot_character(base, 390, 135, model->crossCount + '0');
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
    i will try my best to make the code look cleaner... some other day :D
*/
void master_render(const Model *model, UINT32 *base) {
    int i;
    int h;
    int l;
    /*render_road(base, 350, 320, &model->road[40]);*/
    for (h = 0; h < 2; h++) {
        for (i = 0; i < 120; i++) {
            if (model->road[i].isColliding == 1) {
                clear_region(base, model->road[i].y, model->road[i].x, ROAD_HEIGHT, ROAD_HEIGHT);
                if (h == 1) {
                    render_road(base, model->road[i].y, model->road[i].x, &model->road[i]);
                }
            }
        }
        /*for (i = 0; i < 120; i++) {
            clear_region(base, model->road[i].y, model->road[i].x, ROAD_HEIGHT, ROAD_HEIGHT);
            if (h == 1) {
                render_road(base, model->road[i].y, model->road[i].x, &model->road[i]);
            }
            if (i < 80) {
                render_water(base, model->water[i].y, model->water[i].x, &model->water[i]);
            }
            for (l = 0; i < 15; i++) {
                if (&model->road[i].y == &model->womenWalking[l].y) {
                    isRoadCollidingWalker(&model->road[i], &model->womenWalking[l]);
                }
            }
            isRoadCollidingChuck(&model->road[i], &model->chuck);
            if (model->road[i].isColliding == 1) {
                clear_region(base, model->road[i].y, model->road[i].x, ROAD_HEIGHT, ROAD_HEIGHT);
                if (h == 1) {
                    render_road(base, model->road[i].y, model->road[i].x, &model->road[i]);
                }
            }
        }*/

        for (i = 0; i < 20; i++) {
            render_water(base, model->water[i].y, model->water[i].x, &model->water[i]);
        }

        clear_region(base, model->womenWalking[1].oldy, model->womenWalking[1].oldx, WALKER_HEIGHT, WALKER_HEIGHT);
        render_road(base, model->womenWalking[1].oldy, model->womenWalking[1].oldx, &model->road[0]);
        render_WomenWalking(base, model->womenWalking[1].y, model->womenWalking[1].x, &model->womenWalking[1]);
        
        clear_region(base, model->womenWalking[5].oldy, model->womenWalking[5].oldx, WALKER_HEIGHT, WALKER_HEIGHT);
        render_road(base, model->womenWalking[5].oldy+1, model->womenWalking[5].oldx, &model->road[0]);
        render_WomenWalking(base, model->womenWalking[5].y, model->womenWalking[5].x, &model->womenWalking[5]);
        
        clear_region(base, model->womenWalking[11].oldy, model->womenWalking[11].oldx, WALKER_HEIGHT, WALKER_HEIGHT);
        render_road(base, model->womenWalking[11].oldy+1, model->womenWalking[11].oldx, &model->road[0]);
        render_WomenWalking(base, model->womenWalking[11].y, model->womenWalking[11].x, &model->womenWalking[11]);
        /*for (i = 0; i < 15; i++) {
            clear_region(base, model->womenWalking[i].oldy, model->womenWalking[i].oldx, WALKER_HEIGHT, WALKER_HEIGHT);
            render_road(base, model->womenWalking[i].oldy, model->womenWalking[i].oldx, &model->road[0]);*/
            /*if (model->womenWalking[i].oldy == 16) {
                render_road(base, model->womenWalking[i].oldy, model->womenWalking[i].oldx, &model->road[0]);
            } else {
                render_road(base, model->womenWalking[i].oldy+1, model->womenWalking[i].oldx, &model->road[0]);
            }
            
             turns out that render_road doesn't need to render at their position, so you can render two road[0] 
            if (h == 1) { 
                /render_WomenWalking(base, model->womenWalking[i].y, model->womenWalking[i].x, &model->womenWalking[i]);
            }
        }*/

        for (i = 0; i < 30; i++) {
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
        
        if (model->crossCount != model->oldCrossCount || (model->chuck.x <= 175 && model->chuck.y >= 358)) {
            clear_region(base, 390, 15, 8, 120);
            if (h == 1) {
                plot_string(base, 390, 15, "Cross Count is");
                plot_character(base, 390, 135, model->crossCount + '0');
            }
        }
        /* TO DO: clear_region calls messing with plotted string, making it look weird.  */
        if (model->chuck.x != model->chuck.oldx || model->chuck.y != model->chuck.oldy) {
            clear_region(base, model->chuck.oldy, model->chuck.oldx, CHUCK_HEIGHT, CHUCK_HEIGHT);
            if (h == 1) {
                render_Chuck(base, model->chuck.y, model->chuck.x, &model->chuck); 
            }
        }
    }
    
    
}