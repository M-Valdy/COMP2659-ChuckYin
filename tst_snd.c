#include "psg.h"
#include "sound.h"
#include "effects.h"
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

void music_tst() {
    UINT32 timeThen;
    /* initial register state */
    printf("Before start_music:\n");
    read_psg(0);
    read_psg(1);
    read_psg(7);
    read_psg(8);

    /* start first note */
    start_music();

    printf("After start_music:\n");
    read_psg(0);
    read_psg(1);
    read_psg(7);
    read_psg(8);

    /* keep updating until keypress */
    while (!Cconis()) {
        update_music(30);   /* 7 ticks on 70 Hz clock */
    }

    printf("Before stop_sound:\n");
    read_psg(0);
    read_psg(1);
    read_psg(7);
    read_psg(8);

    stop_sound();

    printf("After stop_sound:\n");
    read_psg(0);
    read_psg(1);
    read_psg(7);
    read_psg(8);

    Cnecin();
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

void noise_tst() {
    /* enable noise on channel A */
    enable_channel(0, 0, 1);   /* tone OFF, noise ON */
    set_volume(0, 10);
    
    set_noise(0x01);
    delay(30);

    set_noise(0x03);
    delay(30);

    set_noise(0x07);
    delay(30);
    
    set_noise(0x0F);
    delay(30);

    set_noise(0x1F);
    delay(30);

    set_volume(0, 0);
}


void effects_tst() {
    int i;
    start_music();
    while (i != 11*4) {
        update_music(30);
        printf("Chuck walks\n");
        play_chuck_walking();
        delay(10);
        set_volume(2,0);
        update_music(30);
        printf("--------------------------\n");
        printf("Chuck wins\n");
        play_chuck_win();
        delay(10);
        set_volume(2,0);
        update_music(30);
        printf("--------------------------\n");
        printf("Chuck touches edge\n");
        play_touch_edge();
        delay(10);
        set_volume(2,0);
        update_music(30);
        printf("--------------------------\n");
        printf("Chuck collides with women\n");
        play_women_collide();
        i += 1;
    }
    set_volume(0,0);
}

int main () {
    effects_tst();
    return 0;
}