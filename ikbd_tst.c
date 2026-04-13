/* @author Gaurik and Meagan */

#include "ikbd.h"
#include "types.h"
#include "raster.h"
#include <osbind.h>

int main(void) {
    char input = 0;
    int exit_game = 0;
    int x = 50;

    int old_mouse_x;
    int old_mouse_y;
    int old_mouse_buttons;

    Vector old_ikbd = install_vector(IKBD, ikbd_custom);
    UINT32 *base = Physbase();
    clear_screen(base);

    old_mouse_x = get_mouse_x();
    old_mouse_y = get_mouse_y();
    old_mouse_buttons = get_mouse_buttons();

    while (!exit_game) {
        input = get_kbd_input();

        if (input != 0) {
            if (input == 'Q') {
                exit_game = 1;
            } else {
                plot_character(base, x, 100, input);
                x += 8;
            }
        }

        if (get_mouse_x() != old_mouse_x) {
            plot_character(base, x, 120, 'X');
            x += 8;
            old_mouse_x = get_mouse_x();
        }

        if (get_mouse_y() != old_mouse_y) {
            plot_character(base, x, 140, 'Y');
            x += 8;
            old_mouse_y = get_mouse_y();
        }

        if (get_mouse_buttons() != old_mouse_buttons) {
            plot_character(base, x, 160, 'B');
            x += 8;
            old_mouse_buttons = get_mouse_buttons();
        }
    }

    uninstall_vector(IKBD, old_ikbd);
    return 0;
}