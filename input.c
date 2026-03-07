#include <osbind.h>
#include "input.h"

/* @author Paolo */
int has_input() {
    return Cconis() != 0;
}

/* @author Paolo */
char get_input() {
    return (char)Cnecin();
}
