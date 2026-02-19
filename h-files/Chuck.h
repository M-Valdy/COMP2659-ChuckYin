typedef struct {
    unsigned int x,y;
    int isWalking;
    int deltaX, deltaY;
    int isColliding;
} Chuck;

void initChuck(Chuck* chuck, unsigned int x, unsigned int y);
void startWalking(Chuck* chuck, int deltaX, int deltaY);
void updateChuck(Chuck* chuck);
void stopWalking(Chuck* chuck);
void render_Chuck(Chuck* chuck);