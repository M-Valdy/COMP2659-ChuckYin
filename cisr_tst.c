#include <osbind.h>
#include <stdio.h>
#include "cisr.h"

void vbl_custom(); 

int main() {
    Vector old_VBL = install_vector(VBL, vbl_custom);

    printf("Timer started. Waiting for 10 seconds...\n");

    while (seconds < 10) {
        printf("Seconds: %d\r", seconds);
    }

    uninstall_vector(VBL, old_VBL);

    printf("\nTimer finished. Vector restored. Exiting...\n");

    return 0;
}