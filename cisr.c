#include "cisr.h"

volatile int seconds = 0; /*  to keep track of seconds */
volatile int invocations = 0; /* sub counter to track the invcations and update seconds in regard to the 70Hz */

Vector install_vector(int num, Vector vector) {
    Vector orig;
    Vector *vectp = (Vector *)((long)num << 2); /* calculate the memeory address, syntax vector# * 4 */
    long old_ssp = Super(0); /* enter Supervisor Mode */
    orig = *vectp; /* save the TOS handler */
    *vectp = vector; /* Install new handler */
    Super(old_ssp); /* Return to User Mode */
    return orig;  /* return old handler for later restoration */
}

void uninstall_vector(int num, Vector old_vector) {
    Vector *vectp = (Vector*)((long)num << 2);
    long old_ssp = Super(0);
    *vectp = old_vector; /* put the original vector back */
    Super(old_ssp);
}

void isr_timer(){
    invocations++;
    if (invocations >= 70) {
        seconds++;
        invocations = 0; /* reset sub-counter */
    }
}
