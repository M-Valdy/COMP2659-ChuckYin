#include "renderer.h";

void render(const Model *model, UINT8 *base) {
    // just placed these here for the meanwhile lmao
    render_Chuck(&model->chuck, base);
    render_WomenWalking(model->womenWalking, base);
    render_WomenSwimming(model->womenSwimming, base);
}

void render_Chuck(const Chuck* chuck, UINT8 *base) {
    // Render Chuck at his current position
    // This is a placeholder implementation and should be replaced with actual rendering code
    // that draws Chuck's sprite on the screen based on his x and y coordinates
}