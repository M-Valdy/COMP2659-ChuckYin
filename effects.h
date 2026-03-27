#include "psg.h"
#include "events.h"

/*
    Channels and their purposes
    Channel A: melody
    Channel C: sound effects
*/

/* 
    You must create an effects file module. It must have one play_effect function for each type of sound effect 
    in your game. The event handling functions in the events module must be modified to play the relevant
    effect whenever its triggering event occurs. f you wish the playback of two sound effects to overlap 
    in time, also use channel B. This will limit music to channel A
*/


/* For Chuck walking, should be C4 then C5 in quick succession
    Sustain should be longer on the C5 */
void play_chuck_walking();



/* For Chuck win, should be D4 then D5 */
void play_chuck_win();