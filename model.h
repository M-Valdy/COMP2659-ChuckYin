#include "Chuck.h";
#include "w-walk.h";
#include "w-swim.h";
#include "tree.h";
#include "water.h";
#include "road.h";

typedef struct {
    Chuck chuck;
    WomenWalking womenWalking[15];
    WomenSwimming womenSwimming[15];
    //Tree tree[10];
    Water water[120]; // need 40 Water objects per stream (20 to cover the whole screen width, double it to make it 64 pixels high), 3 water streams total
    Road road[120]; // need 40 road segments per road (20 to cover the whole screen width, double it to make it 64 pixels high), 3 roads total
} Model;

void Model_init(Model *model);