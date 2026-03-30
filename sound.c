#include "sound.h"
#include "psg.h"
#include <osbind.h>
#include <stdio.h>
#include "model.h"

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
static int total_notes = sizeof(notes) / sizeof(notes[0]);
static UINT32 next_time = 0;
Model model;

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
    set_envelope(0x08, 0x1234);
}

void update_music(UINT32 note_length) {
    if (get_time() >= next_time) {
        current_note++;

        if (current_note >= total_notes) {
            current_note = 0;
        }

        set_tone(0, notes[current_note]);

        if (current_note == 13) {
            next_time += note_length * 2;
        } else {
            next_time += note_length;
        }

        printf("current_note = %d\n", current_note);
        read_psg(0);
        read_psg(1);
        read_psg(7);
        read_psg(8);
    }
}