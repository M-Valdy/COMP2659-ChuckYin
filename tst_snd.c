#include "psg.h"
#include "sound.h"
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
    /* initial register state */
    read_psg(0);
    read_psg(1);
    read_psg(7);
    read_psg(8);

    /* start first note */
    start_music();

    /* should now show first note, mixer on, volume set */
    read_psg(0);
    read_psg(1);
    read_psg(7);
    read_psg(8);

    while (!Cconis()) {
        /* advance music */
        update_music(30);
    }

    stop_sound();

    /* volume should now be 0 */
    read_psg(0);
    read_psg(1);
    read_psg(7);
    read_psg(8);

    Cnecin();
}

int main () {
    music_tst();
    return 0;
}