#include "psg.h"
#include <stdio.h>
#include <osbind.h>

void psg_tst () {
    read_psg(0);
    set_tone(0, 248);         /* channel A */
    read_psg(0);
    read_psg(7);
    enable_channel(0, 1, 0);  /* tone enabled, noise disabled */
    read_psg(7);
    read_psg(8);
    set_volume(0, 11);        /* volume = 11 */
    read_psg(8);

    while (!Cconis())
        ;

    stop_sound();         /* stop sound */
    read_psg(8);
    Cnecin();                 /* consume key */

}

void music_tst(){
    start_music();
    update_music(30); /* 30 sec delay */
    while (!Cconis())
        ;
    stop_sound();         /* stop sound */
    Cnecin();                 /* consume key */
}

int main () {
    psg_tst();
    music_tst();
    return 0;
}