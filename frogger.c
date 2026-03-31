#include <stdio.h>
#include "model.h"
#include "cond.h"
#include "asynch.h"
#include "synch.h"
#include "renderer.h"
#include <osbind.h>
#include "input.h"
#include "start.h"
#include "sound.h"
/* @author Paolo 
    Copied most of the professor's screenshot on the checkpoint PDF
*/
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
    char user_choice, play_char, quit_char;

    /* GOOGLED "atari st double buffering how to allocate 32000 bytes not on the stack" and used the AI overview for the 256 aligned part */
    /* https://stackoverflow.com/questions/38088732/explanation-to-aligned-malloc-implementation */
    /* Professor said in page9 of chuckpoint 3 that we need to allocated 32k bytes but NOT on the stack. We put it in the heap using GEMDOS' Malloc() */
    /* Also said that we need to make frame buffers to be 256 byte aligned */
    void *base = Physbase();
   
    clear_screen(base);
   make_splashscreen(base);
   
   play_char = 'p';
   quit_char = 'q';
   
   scanf("%s", &user_choice);
   
   if(user_choice == play_char){
 
    void *front, *back;
    void *raw_back;
    front = base;
    raw_back = (void *)Malloc(32000L + 255L);
    back = (void *)(((long)raw_back + 255L) & 0xFFFFFF00L);
    
    Model_init(&frogger);
    render_initial_state(&frogger, back);
    render_initial_state(&frogger, front);
    start_music();
    
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
            back = front; /* realized had to do this because it looked too choppy even though it was working */
            master_render(&frogger, back); /* TO DO: need to optimize render_road */
            update_music(30);
            
            Setscreen(-1L, (long)back, -1L);
            Vsync();
            /* swap buffers */
            temp = front;
            front = back;
            back = temp;

            timeThen = timeNow;
        }
    }
    Setscreen(-1L, (long)base, -1L);

    return 0;
    }

    else {
        clear_screen(base);
        plot_string(base, 200, 300, "You quit the game.");
        return 0;
    }
}