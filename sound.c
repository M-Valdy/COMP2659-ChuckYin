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


/* Helper function for delaying the notes for music */
void delay(int count) {
    
}


/* All melody is done on channel A, I refuse to do harmony */
void start_music() {
    set_tone(0, notes[0]);
    enable_channel(0, 1, 0);  /* tone enabled, noise disabled */
    set_volume(0, 11);        /* volume = 11 */
}

void update_music(UINT32 time_elapsed){

}