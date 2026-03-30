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

}

void envelope_tst() {
    /* set envelope with shape 0x0A and sustain 0x1234 */
    set_envelope(0x08, 0x1234);

    /* should show shape in register 13, rough sustain in register 11, fine sustain in register 12 */
    read_psg(11);
    read_psg(12);
    read_psg(13);

    set_envelope(0x0F, 0x1000);

    /* should show shape in register 13, rough sustain in register 11, fine sustain in register 12 */
    read_psg(11);
    read_psg(12);
    read_psg(13);

    while (!Cconis()) {
        /* advance music */
        update_music(30);
        read_psg(0);
        read_psg(1);
        read_psg(7);
        read_psg(8);
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
    envelope_tst();

    return 0;
}