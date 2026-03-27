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