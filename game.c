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

int game_loop(UINT32* base, int player_choice) {
    int i = 0;
    void *temp;
    char ch;
    Vector *old_vbl;
    UINT32 timeThen, timeNow, timeElapsed;
    Model frogger;

    old_vbl = install_vector(VBL, vertical_blank_custom);
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
    
        timeThen = get_time();
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
                } /* i think i need to clear the user input to prevent continuous walking despite key release */
            }

            timeNow = get_time();
            timeElapsed = timeNow - timeThen;
            if (timeElapsed > 0) {
                synch_update(&frogger);
                cond_update(&frogger);
                master_render(&frogger, back);
                update_music(30);
                Setscreen(-1L, (long)back, -1L);

                temp = front;
                front = back;
                back = temp;
                timeThen = timeNow;
            }
        }
        Setscreen(-1L, (long)base, -1L); /*set_video_base(base); */
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