/* @author Gaurik */

#include "ikbd.h"
#include "types.h"
#include "raster.h"
#include <osbind.h>

int main() {

    char input = 0;
    int exit_game = 0;
    int x = 50;
    Vector *old_ikbd = install_vector(IKBD, ikbd_custom);
    UINT32 *base = Physbase();
    clear_screen(base);
    
    while (!exit_game) {
        
        input = get_kbd_input();

        if (input != 0) {
            if (input == 'Q') {
                exit_game = 1;
            } else {
                plot_character(base, x, 100, input); 
                x+=8;
            }
        }
    }

    uninstall_vector(IKBD, old_ikbd);
    return 0;
}