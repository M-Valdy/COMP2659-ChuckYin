 /* @author Gaurik */

#ifndef CISR_H
#define CISR_H

#include <osbind.h>
#include "types.h"
/* vertical blank: vector #28 */
#define VBL 28

/* 
 * VOLATILE
 * a type qualifier that tells the compiler that a variable's value may change unexpectedly at any
 * time—due to hardware, interrupts, or multi-threading
 * preventing the compiler from optimizing memory reads/writes.
 */
extern volatile UINT32 invocations; /* global volatile sub counter to track the invocations */
extern volatile UINT32 seconds; /*  global volatile to keep track of time seconds */

extern volatile int render_request_flag;

/*
 * a Vector is a function start address
 * it is a pointer to a function that has no parameters and no return value 
 * from lab notes
*/
typedef void (*Vector)();

/*  
 * routine to replace default TOS ISR with a custom ISR.
 * Takes in integer "num" correspsonding to the # vector needed and stores it in the address label
 * specied for the "vector."
*/
Vector install_vector(int num, Vector vector);

/*  
 * routine to reinstall default TOS ISR from a custom ISR.
 * Takes in integer "num" correspsonding to the # vector needed and read from the old vector for correct
 * adress for reintalling the orginal vector.
*/
void uninstall_vector(int num, Vector old_vector);

/* 
 * a routine to replace the system clock for game events, uses the VBL vector isntead.
 * The Atari ST has a vertical refresh rate of 70Hz, thus every 70 "invocations" increments the seconds global variable by 1.
 * This is done by first incrementing the "invocations" variable by 1 for every refresh.
 * (Honestly, I have no idea what invocations mean but it made sense from the lab notes that this can be used for timing purposes)
*/
void timer_custom();

#endif