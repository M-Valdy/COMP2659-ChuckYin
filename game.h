#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include "model.h"
#include "cond.h"
#include "asynch.h"
#include "synch.h"
#include "renderer.h"
#include <osbind.h>
#include "start.h"
#include "sound.h"
#include "raster.h"
#include "cisr.h"

/* @author Gaurik, Paolo 
    Gets the invocations from VBL ISR to time the game.
*/
UINT32 get_time();

/* @author Paolo
    Aligns a pointer to the next 256 byte boundary. Used for double buffering.
    Used this instead of malloc, setting setting aside memory for the buffers 
    needs them to have their last 2 bits be '00'.
*/
UINT32 *align_256(void *ptr);

/*Function so that the keyboard doesn't have any sound 
    @author Parker from Class and the teacher, Meagan*/

void no_keysound();

void return_keysound();

/* @author Paolo for the main flow */ 
/* @author Gaurik for integrating the title screen */
/* @author Meagan for integrating the sound */

int game_loop();

#endif