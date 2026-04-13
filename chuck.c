/* @author Paolo, originally */
/* syntax and logic updates, ISR and IKBD updates Gaurik */

#include "game.h"

int main() {
    int player_choice;
    void *base = get_video_base();
    Vector *old_vbl = install_vector(VBL, vertical_blank_custom);
    Vector *old_ikbd = install_vector(IKBD, ikbd_custom);
    clear_screen(base);
    
    player_choice = make_splashscreen(base);
    game_loop(base, player_choice);
    uninstall_vector(VBL, old_vbl);
    uninstall_vector(IKBD, old_ikbd);
    return 0;
}