#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include "model.h"
#include "cond.h"
#include "asynch.h"
#include "synch.h"
#include "renderer.h"
#include <osbind.h>
#include "input.h"
#include "start.h"
#include "sound.h"
#include "raster.h"
#include "cisr.h"

/* @author Paolo 
    Copied most of the professor's screenshot on the checkpoint PDF
*/
UINT32 get_time();
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