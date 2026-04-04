#include <osbind.h>
#include "effects.h"
#include "psg.h"

/* For Chuck walking, should be C4 then C5 in quick succession
    Sustain should be longer on the C5 */
void play_chuck_walking() {
    enable_channel(2, 1, 0);   /* tone on, noise off */
    set_envelope(0x0A, 0x2000);
    set_volume(2, 12);

    set_tone(2, 0x0d6);        /* C5-ish */
    delay(2);

    set_volume(2, 0);
}

/* For Chuck win, should be D5 then D6 */
void play_chuck_win() {
    enable_channel(2, 1, 0);   /* tone on, noise off */
    set_envelope(0x0A, 0x2000);
    set_volume(2, 12);

    set_tone(2, 0x0be);        /* D5-ish */
    delay(20);

    set_tone(2, 0x17d);        /* second note */
    delay(30);

    set_volume(2, 0);
}

/* When touching the edges play C2 */
void play_touch_edge() {
    enable_channel(2, 1, 0);   /* tone on, noise off */
    set_envelope(0x0A, 0x2000);
    set_volume(2, 12);

    set_tone(2, 0x6ae);
    set_noise(0x01);
    delay(20);

    set_volume(2, 0);
}


/* When colliding with obstacle, play E2 then C2 */
void play_women_collide() {
    enable_channel(2, 1, 1);    /* Both tone and noise are used */
    set_envelope(0x0A, 0x2000);
    set_volume(2, 12);

    set_tone(2, 0x54d);
    delay(20);

    set_tone(2, 0x6ae);
    set_noise(0x03);
    delay(30);

    set_volume(2, 0);
}