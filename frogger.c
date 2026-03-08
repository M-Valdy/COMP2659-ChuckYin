#include <stdio.h>
#include "model.h"
#include "cond.h"
#include "asynch.h"
#include "synch.h"
#include "renderer.h"
#include <osbind.h>
#include "input.h"

/* @author Paolo */
UINT32 get_time() {
    long old_ssp;
    long *timer;
    UINT32 time;

    timer = (long *)0x462;
    old_ssp = Super(0);
    time = *timer;
    Super(old_ssp); 

    return time;
}

/* @author Paolo */
int main() {
    int i = 0;
    void *temp;
    char ch;
    UINT32 timeThen, timeNow, timeElapsed;
    Model frogger;

    /* GOOGLED "atari st double buffering how to allocate 32000 bytes not on the stack" and used the AI overview */
    /* https://stackoverflow.com/questions/38088732/explanation-to-aligned-malloc-implementation */
    /* Professor said in page9 of chuckpoint 3 that we need to allocated 32k bytes but NOT on the stack. We put it in the heap using GEMDOS' Malloc() */
    /* Also said that we need to make frame buffers to be 256 byte aligned */
    void *base = Physbase();
    void *front, *back;
    void *raw_back;
    front = base;
    raw_back = (void *)Malloc(32000L + 255L);
    back = (void *)(((long)raw_back + 255L) & 0xFFFFFF00L);
    
    Model_init(&frogger);
    render_initial_state(&frogger, back);
    render_initial_state(&frogger, front);
    
    timeThen = get_time();
    while (frogger.gameOver != 2 && frogger.gameOver != 3) {
        if (has_input()) {
            ch = get_input();
            if (ch == 'w') {
                asynch_button_W(&frogger);
            } else if (ch == 'a') {
                asynch_button_A(&frogger);
            } else if (ch == 's') {
                asynch_button_S(&frogger);
            } else if (ch == 'd') {
                asynch_button_D(&frogger);
            } else if (ch == 'x') {
                asynch_button_X(&frogger);
            } else if (ch == 'p') {
                asynch_button_P(&frogger);
            }
        }

        timeNow = get_time();
        timeElapsed = timeNow - timeThen;
        if (timeElapsed > 0) {
            synch_update(&frogger);
            cond_update(&frogger);
            /*clear_screen(back);*/
            back = front;
            master_render(&frogger, back); /* TO DO: need to optimize master_render by implementing functions for clearing affected bitmaps and rendering */
            
            /* Use Vsync to prevent premature rendering */
            Setscreen(-1L, (long)back, -1L);
            Vsync();
            /* swap buffers */
            temp = front;
            front = back;
            back = temp;

            timeThen = timeNow;
        }
    }

    /* Prevent crash-on-quit */
    Setscreen(-1L, (long)base, -1L);

    return 0;
}