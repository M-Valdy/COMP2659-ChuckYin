/* @author Gaurik and Meagan */

#include "ikbd.h"
#include "types.h"
#include "raster.h"
#include "start.h"

int main(void) {
    char input = 0;
    int exit_game = 0;
    int x = 50;

    int mx, my;
    int mb;
    int old_mouse_x;
    int old_mouse_y;
    int old_mouse_buttons;

    Vector *old_vbl = install_vector(VBL, vertical_blank_custom);
    Vector *old_ikbd = install_vector(IKBD, ikbd_custom);
    
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
            }
            else if (input == 'P') {
                clear_screen(base);
            }
            else {
                plot_character(base, x, 100, input);
                x += 8;
            }
        }

        mx = get_mouse_x();
        my = get_mouse_y();
        mb = get_mouse_buttons();

        if (mx != old_mouse_x || my != old_mouse_y) {
            clear_region(base, old_mouse_y, old_mouse_x, 16, 16);
            plot_mouse(base, mx, my);
            old_mouse_x = mx;
            old_mouse_y = my;
        }
        if (mb != old_mouse_buttons) {
            plot_character(base, mx, my, 'X'); 
            old_mouse_buttons = mb;
        }
    }
    uninstall_vector(VBL, old_vbl);
    uninstall_vector(IKBD, old_ikbd);
    return 0;
}