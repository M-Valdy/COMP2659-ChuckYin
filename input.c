#include <osbind.h>
#include "input.h"
#include "ikbd.h"

/* @author Paolo */
int has_input() {
    return Cconis() != 0;
}

/* @author Paolo */
char get_input() {
    return (char)Cnecin();
}

/* @author Paolo 
    because a user holding down a key just floods the buffer so player keeps moving even if user lets go of key
*/
char get_latest_input() {
    char ch = 0;

    if (!has_input()) {
        return 0;
    }

    ch = get_input();

    while (has_input()) {
        ch = get_input();
    }

    return ch;
}
