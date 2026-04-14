#include <osbind.h>
#include "start.h"
#include "ikbd.h"
#include "cisr.h" 

/* @author Gaurik */

int main()
{
    int player_choice;
    Vector *old_ikbd = install_vector(IKBD, ikbd_custom);
    void *base = Physbase();
    clear_screen(base);
    
    player_choice = make_splashscreen(base);
    if (player_choice == 1) { 
        clear_screen(base);
        plot_string(base, 100, 100, "You quit");
    } 
    else if (player_choice == 0) {
        clear_screen(base);
        plot_string(base, 100, 100, "You play");
    }
    uninstall_vector(IKBD, old_ikbd);
    return 0;
}
