#include "sound.h"
#include "psg.h"
#include <osbind.h>

/* Frogger theme song music notes:
    A#4 F#4 F#4 F#4 
    A#4 F#4 F#4 F#4 
    B4 B4 A#4 A#4 G#4 
    B4 B4 A#4 A#4 G#4 G#4 D#5 D#5 
    C#5 B4 A#4 G#4 F#4 
*/
int notes[] = {
                0x0f0,0x12e,0x12e,0x12e,
                0x0f0,0x12e,0x12e,0x12e,
                0x0e2,0x0e2,0x0f0,0x0f0,0x10d,
                0x0e2,0x0e2,0x0f0,0x0f0,0x10d,0x10d,0x0b4,0x0b4,
                0x0CA,0x0e2,0x0f0,0x10d,0x12e
              };

static int current_note = 0;
static UINT32 start_time = 0;
static int total_notes = sizeof(notes) / sizeof(notes[0]);

/* got this from Paolo's code in frogger.c */
UINT32 get_time() {
    long old_ssp;
    long *timer;
    UINT32 time;

    timer = (long *)0x462;
    old_ssp = Super(0);
    time = *timer;
    Super(old_ssp); 

    return time;
}


/* Helper function for delaying the notes for music */
void delay(int count) {
    UINT32 start = get_time();
    while (get_time() - start < count) {
        ;
    }
}


/* All melody is done on channel A, I refuse to do harmony */
void start_music() {
    current_note = 0;
    next_time = get_time() + 30;
    set_tone(0, notes[0]);
    enable_channel(0, 1, 0);  /* tone enabled, noise disabled */
    set_volume(0, 11);        /* volume = 11 */
}

/* Updates the music based on the elapsed time */
void update_music(UINT32 time_elapsed){
    if (current_note + 1 < total_notes && get_time() >= next_time) {
        current_note++;
        set_tone(0, notes[current_note]);
        next_time += time_elapsed;
    }
}