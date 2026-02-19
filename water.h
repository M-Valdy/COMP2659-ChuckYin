typedef struct {
    unsigned int x,y;
} Water;

void initWater(Water* water, unsigned int x, unsigned int y);
void isWaterColliding(Water* water, Chuck* chuck);
void render_water(Water* water);
