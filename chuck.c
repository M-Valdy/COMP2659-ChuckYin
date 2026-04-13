/* @author Paolo, originally */
/* syntax and logic updates, ISR and IKBD updates Gaurik */

#include "game.h"

int main() {
    int player_choice;
    void *base = get_video_base();
    clear_screen(base);
    
    player_choice = make_splashscreen(base);
    game_loop(base, player_choice);

    return 0;
}