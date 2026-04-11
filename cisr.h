#ifndef CISR_H
#define CISR_H

/* @author Gaurik*/

#include <osbind.h>

/* Vertical Blank is Vector #28 */
#define VBL 28

extern volatile int seconds;
extern volatile int invocations;

/* a Vector is a function start address
 * it is a pointer to a function that has no parameters and no return value 
*/
typedef void (*Vector)();

/*  
 * routine to replace default TOS ISR with a custom ISR.
 * Takes in integer "num" correspsonding to the # vector needed and stores it in the address label
 * specied for the "vector."
*/
Vector install_vector(int num, Vector vector);
void uninstall_vector(int num, Vector old_vector);
void isr_timer();
#endif