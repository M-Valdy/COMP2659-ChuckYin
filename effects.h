#include "psg.h"
#include "events.h"
#include "model.h"
#include "sound.h"

/*
    Channels and their purposes
    Channel A: melody
    Channel C: sound effects
*/

/* 
    You must create an effects file module. It must have one play_effect function for each type of sound effect 
    in your game. The event handling functions in the events module must be modified to play the relevant
    effect whenever its triggering event occurs. If you wish the playback of two sound effects to overlap 
    in time, also use channel B. This will limit music to channel A
*/


/* For Chuck walking, should be C4 then C5 in quick succession
    Sustain should be longer on the C5 */
void play_chuck_walking();


/* For Chuck win, should be D5 then D6 */
void play_chuck_win();


/* When touching the edges play C2 */
void play_touch_edge();


/* When colliding with obstacle, play E2 then C2 */
void play_women_collide();