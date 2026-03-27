#ifndef SOUND_H
#define SOUND_H
#include "types.h"
#include <osbind.h>

#include "psg.h"

/*
    Channels and their purposes
    Channel A: melody
    Channel B: harmony
    Channel C: sound effects
*/

/* Begins the playing of the song by loading the data for the first note into the PSG. */
void start_music();

/* 
    Advances to the next note of the song if necessary, as determined by the amount of
    time elapsed since the previous call. The time elapsed is determined by the caller. It is
    intended that this value is equal to the current value of the vertical blank clock, minus
    its value when the function was last called. 
*/
void update_music(UINT32 time_elapsed);




#endif