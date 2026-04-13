#include "game.h"

/* @author Paolo 
    Copied most of the professor's screenshot on the checkpoint PDF
*/
UINT32 get_time() {
    return invocations;
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


void return_keysound(){
    long old_ssp = Super(0);
    volatile char* console_address = 0x000484;
    UINT8 console_state = *console_address;
    console_state |= 0x01; /* Clear bit 0 to disable keyboard sound */
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
    /* UINT32 timeThen, timeNow, timeElapsed; */
    Vector *old_vbl = install_vector(VBL, vertical_blank_custom);
    Model frogger;
    
    /* GOOGLED "atari st double buffering how to allocate 32000 bytes not on the stack" and used the AI overview for the 256 aligned part */
    /* https://stackoverflow.com/questions/38088732/explanation-to-aligned-malloc-implementation */
    /* Professor said in page9 of chuckpoint 3 that we need to allocated 32k bytes but NOT on the stack. We put it in the heap using GEMDOS' Malloc() */
    /* Also said that we need to make frame buffers to be 256 byte aligned */
    clear_screen(base);
    
    if (player_choice == 0) { 
        void *front, *back;
        void *raw_back;
        front = base;
        raw_back = (void *)Malloc(32000L + 255L);
        back = (void *)(((long)raw_back + 255L) & 0xFFFFFF00L);

        no_keysound();
        Model_init(&frogger);
        render_initial_state(&frogger, back);
        start_music();
        render_initial_state(&frogger, front);
    
        /* timeThen = get_time(); */
        while (frogger.gameOver != 2 && frogger.gameOver != 3) {
            if (has_input()) {
                ch = get_latest_input();
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
                    return_keysound();
                } else if (ch == 'o') {
                    asynch_button_O(&frogger);
                }
            }

            if (render_request_flag) {
                render_request_flag = 0;
                synch_update(&frogger);
                cond_update(&frogger);
                back = front;
                master_render(&frogger, back); /* TO DO: need to optimize render_road */
                update_music(30);
                set_video_base((long)back); /* Setscreen(-1L, (long)back, -1L);*/
                /* Vsync(); */
                
                /* swap buffers */
                temp = front;
                front = back;
                back = temp;
            }
        }
        set_video_base((long)base); /*Setscreen(-1L, (long)base, -1L); */
        uninstall_vector(VBL, old_vbl);
        return 0;
    }

    else if (player_choice == 1) {
        clear_screen(base);
        plot_string(base, 230, 200, "You quit the game.");
        return 0;
    }

    else {
        plot_string(base, 200, 200, "AN ERROR OCCURED, PLEASE RESTART THE PROGRAM.");
    }
}