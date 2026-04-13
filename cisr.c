/* author @Gaurik */
#include "cisr.h"

volatile UINT32 invocations = 0;
volatile UINT32 seconds = 0;
volatile int render_request_flag = 0;

Vector install_vector(int num, Vector vector) {
    Vector orig;
    Vector *vectp = (Vector *)((long)num << 2); /* calculate the memeory address, syntax vector# * 4 */
    long old_ssp = Super(0); 
    orig = *vectp; /* save the TOS handler */
    *vectp = vector; /* Install new handler */ 
    Super(old_ssp); 
    return orig; /* return old handler for later reinstallation */
}

void uninstall_vector(int num, Vector orig)  {
    Vector *vectp = (Vector *)((long)num << 2); /* calculate the memeory address, syntax vector# * 4 */
    long old_ssp = Super(0);
    *vectp = orig; /* restore the orignal vector */
}

void timer_custom() {
    invocations++; /* increment the ivocations counter */
    render_request_flag = 1; /* set the rrf every refresh */
    if ((invocations % 70) == 0) {
        seconds++; /* increment seconds every 70 refreshes */
    }
}
