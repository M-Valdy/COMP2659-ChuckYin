#include "Chuck.h";

typedef struct {
    unsigned int x,y;
} StoreAisle;

void initStoreAisle(StoreAisle* storeAisle, unsigned int x, unsigned int y);
void isChuckCollidingWithStoreAisle(Chuck* chuck, StoreAisle* storeAisle);