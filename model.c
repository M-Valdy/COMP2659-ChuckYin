#include "model.h";

// @author Paolo
// not finished yet, just getting it started with initializing Chuck and the arrays of objects in the Model struct
void Model_init(Model *model) {
    initChuck(&model->chuck, 320, 350);
    for (int i = 0; i < 15; i++) {
        initWomenWalking(&model->womenWalking[i], 0, 0); // still need to set x and y values for each womenWalking object based on their position on the road
        initWomenSwimming(&model->womenSwimming[i], 0, 0); // still need to set x and y values for each womenSwimming object based on their position in the water stream
    }
    /*for (int i = 0; i < 10; i++) {
        initTree(&model->tree[i], 0, 0); // still need to set x and y values for each tree object based on their position
    }*/
    for (int i = 0; i < 120; i++) {
        initWater(&model->water[i], 0, 0); // still need to set x and y values for each water object based on their position in the water stream
        initRoad(&model->road[i], 0, 0); // still need to set x and y values for each road object based on their position in their appropriate street
    }
}

// @author Paolo
int main() {
    Model model;
    Model_init(&model);

    return 0;
}