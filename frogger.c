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
    old_ssp = Super(0);
    timeNow = *timer;
    Super(old_ssp); 
}

/* @author Paolo */
int main() {
    int i = 0;
    void *temp;
    char ch;

    /* GOOGLED "atari st double buffering how to allocate 32000 bytes not on the stack" and used the AI overview */
    /* https://stackoverflow.com/questions/38088732/explanation-to-aligned-malloc-implementation */
    /* Professor said in page9 of chuckpoint 3 that we need to allocated 32k bytes but NOT on the stack. We put it in the heap using GEMDOS' Malloc() */
    /* Also said that we need to make frame buffers to be 256 byte aligned */
    void *base = Physbase();
    void *front, *back;
    front = base;
    back = Malloc(32000); /* TO DO: make it 256 byte aligned */

    long *timer = (long *)0x462;
    UINT32 timeThen, timeNow, timeElapsed;
    
    Model frogger;
    Model_init(&frogger);
    render_initial_state(&frogger, back);
    
    while (frogger.gameOver != 1) {
        if (!has_input()) {
            return;
        }
        ch = get_input();
        if (ch == 'w') {
            asynch_button_W(model);
        } else if (ch == 'a') {
            asynch_button_A(model);
        } else if (ch == 's') {
            asynch_button_S(model);
        } else if (ch == 'd') {
            asynch_button_D(model);
        }

        timeNow = get_time();
        timeElapsed = timeNow - timeThen;
        if (timeElapsed > 0) {
            synch_update(&frogger);
            cond_update(&frogger);
            clear_screen(back);
            master_render(&frogger, back); /* TO DO: need to optimize master_render by implementing functions for clearing affected bitmaps and rendering */
            
            /* Use Vsync to prevent premature rendering */
            Setscreen(-1, back, -1);
            Vsync();
            /* swap buffers */
            temp = front;
            front = back;
            back = temp;
        }
    }

    /* Prevent crash-on-quit */
    Setscreen(-1, base, -1);

    return 0;
}