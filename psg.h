#ifndef PSG_H
#define PSG_H

#include <osbind.h>
#include <stdio.h>
#include "types.h"


/* @author Meagan
    Writes the given byte value (0-255) to the given PSG register (0-15). 
    This is a helpernroutine to be used by the other functions in this module. 
    It takes in the register number and the value to write, 
    and performs the necessary I/O port writes to set the PSG register 
    to the given value.
*/
void write_psg(int reg, UINT8 val);


/* @author Meagan 
    For testing only. Write psg already outputs the value of the psg register so all
    it does is print it out. 
*/
void read_psg(int reg);


/* @author Meagan
    Loads the tone registers (coarse and fine) for the given channel (0=A, 1=B, 2=C) with the
    given 12-bit tuning. 
    The tuning value is split into a fine tune (lower 8 bits) and a coarse tune (upper 4 bits).
    The fine tune is loaded into the even-numbered register for the channel (0, 2, or 4) and the
    coarse tune is loaded into the odd-numbered register for the channel (1, 3, or 5).
    Fine tune is used for the notes within an octave and coarse tune is used for the octave.
*/
void set_tone(int channel, int tuning);


/* @author Meagan
    Loads the volume register for the given channel. 
    Volume is a value from 0-31, with 0 being the loudest and 31 being the quietest. 
    Uses registers 8-10 for channels A-C respectively.
*/
void set_volume(int channel, int volume);


/* @author Meagan
    Turns the given channel’s tone/noise signals on/off (0=on, 1=off).
    It works for any channel but it only writes to register 7.
*/
void enable_channel(int channel, int tone_on, int noise_on);


/* @author Meagan
    Loads the noise register (register 6) with the given tuning. 
*/
void set_noise(int tuning);


/* @author Meagan
    Loads the PSG envelope control registers with the given envelope shape and 16-bit sustain.
    From the 16-bit sustain, the function then gets the rough and fine sustains 
    and loads them into registers 11 and 12 respectively.
    The envelope shape is loaded into register 13.
*/
void set_envelope(int shape, unsigned int sustain);

/* Silences all PSG sound/noise production. For all channels. */
void stop_sound();

#endif