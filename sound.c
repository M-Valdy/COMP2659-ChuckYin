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
static int previous_note = 0;

/* got this from Paolo's code in frogger.c */
UINT32 get_clock() {
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
    UINT32 start = get_clock();
    while (get_clock() - start < count) {
        ;
    }
}


/* All melody is done on channel A, I refuse to do harmony */
void start_music() {
    current_note = 0;
    next_time = get_clock() + 30;
    set_tone(0, notes[0]);
    enable_channel(0, 1, 0);  /* tone enabled, noise disabled */
    set_volume(0, 0xb);        /* volume = 11 */
    set_envelope(0x08, 0x0400);
}


void update_music(UINT32 note_length) {
    UINT32 this_length = 0;
    if (get_clock() >= next_time) {
        previous_note = notes[current_note];
        current_note++;

        /* For looping */
        if (current_note >= total_notes) {
            current_note = 0;
        }

        if (current_note == 12) {
            this_length += note_length * 4;
        } 
        else if(current_note == 25) {
            this_length += (note_length * 9) / 2;
        }
        else {
            this_length += note_length;
        }

        if (notes[current_note] == previous_note) {
            set_volume(0,0);
            delay(1);
            set_volume(0,0xb);
        }

        set_tone(0, notes[current_note]);

        if (current_note >= 0 && current_note <= 7) {
            /* A#4 F#4 F#4 F#4 A#4 F#4 F#4 F#4 */
            set_envelope(0x08, 0x0400);
        }
        else if ((current_note >= 8 && current_note <= 11) ||
                 (current_note >= 21 && current_note <= 24)) {
            /* B4 B4 A#4 A#4 and C#5 B4 A#4 G#4 */
            set_envelope(0x08, 0x0600);
        }

        else if (current_note == 12) {
            /* For a sustain in G#4 */
            set_envelope(0x0A, 0x2010);
        }

        else if (current_note >= 13 && current_note <= 20) {
            /* C#5 B4 A#4 G#4 */
            set_envelope(0x08, 0x0500);
        }

        else if (current_note == total_notes - 1) {
            /* final long F#4 */
            set_envelope(0x0A, 0x2020);
        }

        next_time += this_length;
    }
}