#define CHUCK_HORIZONTAL 8

typedef struct {
    unsigned int x,y;
    int isWalking;
    int deltaX, deltaY;
    int isColliding; // 1 = obstacle collision, 0 = no collision, 2 = death collision
} Chuck;

extern int chuckBitmap[CHUCK_HORIZONTAL];




void initChuck(Chuck* chuck, unsigned int x, unsigned int y);
void startWalking(Chuck* chuck, int deltaX, int deltaY);
void updateChuck(Chuck* chuck);
void stopWalking(Chuck* chuck);
void render_Chuck(Chuck* chuck);