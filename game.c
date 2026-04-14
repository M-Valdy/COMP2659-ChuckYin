#include "game.h"
#include "ikbd.h"

/* @author Paolo */
static UINT8 back_buffer_raw[32000 + 255]; /* add 255 bytes to make sure we still have 32000 memory because address given by align_256 might not be at the beginning of the allocated space */
/*static UINT8 buffer2_raw[32000 + 255]; use this Gaurik if you want to try 3rd buffer again*/

/* @author Gaurik */
UINT32 get_time() {
    return invocations;
}

/* @author Paolo 
returns address you can start writing to for the back buffer, which is 256 byte aligned
*/
UINT32 *align_256(void *ptr) {
    unsigned long addr;

    addr = (unsigned long)ptr; 
    addr = (addr + 255UL) & 0xFFFFFF00UL; /* add 255 so you don't point before the buffer */

    return (UINT32 *)addr;
}

/*Function so that the keyboard doesn't have any sound 
    @author Parker from Class and the teacher, Meagan*/
void no_keysound(){
    long old_ssp = Super(0);
    volatile char* console_address = 0x000484;
    UINT8 console_state = *console_address;
    console_state &= 0xFE; /* Clear bit 0 to disable keyboard sound */
    *console_address = console_state;
    Super(old_ssp);
}

/*Function so that the keyboard goes back to normal and has sound again. 
    @author Parker from Class and the teacher, Meagan*/
void return_keysound(){
    long old_ssp = Super(0);
    volatile char* console_address = 0x000484;
    UINT8 console_state = *console_address;
    console_state |= 0x01; /* Set bit 0 to enable keyboard sound */
    *console_address = console_state;
    Super(old_ssp);
}


/* @author Paolo for the main flow */ 
/* @author Gaurik for integrating the title screen */
/* @author Meagan for integrating the sound */
int game_loop(UINT32 *base, int player_choice) {
    int i = 0;
    void *temp;
    char ch;
    Model frogger;
    
    /* GOOGLED "atari st double buffering how to allocate 32000 bytes not on the stack" and used the AI overview for the 256 aligned part */
    /* https://stackoverflow.com/questions/38088732/explanation-to-aligned-malloc-implementation */
    /* Professor said in page9 of chuckpoint 3 that we need to allocated 32k bytes but NOT on the stack. We put it in the heap using GEMDOS' Malloc() */
    /* Also said that we need to make frame buffers to be 256 byte aligned */
    clear_screen(base);
    
    if (player_choice == 0) { 
        UINT32 *front, *back;
        front = base;
        back = align_256(back_buffer_raw);

        no_keysound();
        Model_init(&frogger);
        render_initial_state(&frogger, back);
        start_music();
        render_initial_state(&frogger, front);
    
        while (frogger.gameOver != 2 && frogger.gameOver != 3) {
            ch = get_kbd_input();
            if (ch == 'W') {
                asynch_button_W(&frogger);
            } else if (ch == 'A') {
                asynch_button_A(&frogger);
            } else if (ch == 'S') {
                asynch_button_S(&frogger);
            } else if (ch == 'D') {
                asynch_button_D(&frogger);
            } else if (ch == 'P') {
                asynch_button_P(&frogger);
                return_keysound();
            } else if (ch == 'O') {
                asynch_button_O(&frogger);
            }

            if (render_request_flag) {
                render_request_flag = 0;
                synch_update(&frogger);
                cond_update(&frogger);
                copy_buffer(back, front); /* Well... flickering was caused by me actually drawing on the live frame. back = front was written off since it left after images initially */
                master_render(&frogger, back);
                update_music(30);
                set_video_base(back);
                
                /* swap buffers */
                temp = front;
                front = back;
                back = temp;
            }
        }
        set_video_base(base);
        return 0;
    }

    else if (player_choice == 1) {
        clear_screen(base);
        plot_string(base, 230, 200, "You quit the game.");
        return 0;
    }

    else {
        plot_string(base, 200, 200, "AN ERROR OCCURED, PLEASE RESTART THE PROGRAM.");
        return 0;
    }
}