#include "psg.h"
#include <stdio.h>

void psg_tst () {
    set_tone(0, 248);         /* channel A */
    read_psg(0);
    enable_channel(0, 1, 0);  /* tone enabled, noise disabled */
    read_psg(0);
    set_volume(0, 11);        /* volume = 11 */
    read_psg(0);

    while (!Cconis())
        ;

    set_volume(0, 0);         /* stop sound */
    read_psg(0);
    Cnecin();                 /* consume key */

}

int main () {
    psg_tst();
    return 0;
}