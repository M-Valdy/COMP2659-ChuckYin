#include "psg.h"
#include <osbind.h>
void psg_tst () {
    set_tone(0, 248);         /* channel A */
    enable_channel(0, 1, 0);  /* tone enabled, noise disabled */
    set_volume(0, 11);        /* volume = 11 */

    while (!Cconis())
        ;

    set_volume(0, 0);         /* stop sound */
    Cnecin();                 /* consume key */

}

int main () {
    psg_tst();
    return 0;
}