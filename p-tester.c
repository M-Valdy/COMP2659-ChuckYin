#include <stdio.h>
#include "types.h"

#define CHUCK_HEIGHT 32

/* @author Paolo
 find row X by (X+11)

 replace with a different bitmap to test a different image */
const UINT32 Chuck_bitmap[CHUCK_HEIGHT] =
{ 
    0x00000000, 
    0x003FFC00, 
    0x007FFE00, 
    0x00FFFF00, 
    0x01E3C780, 
    0x03DC3BC0, 
    0x03BFFDC0, 
    0x037FFEC0, 
    0x0367E6C0, 
    0x0367E6C0, 
    0x037FFEC0, 
    0x02FFFF40, 
    0x01FFFF80, 
    0x01FC3F80, 
    0x00FFFF00, 
    0x00FFFF00,
    0x007FFE00, 
    0x001FF800, 
    0x000FF000, 
    0x003FFC00, 
    0x007FFE00, 
    0x006FF600, 
    0x006FF600, 
    0x006FF600, 
    0x006FF600, 
    0x006FF600, 
    0x006C3600, 
    0x000C3000, 
    0x000C3000, 
    0x000C3000, 
    0x000C3000, 
    0x00000000
};

/* @author Paolo
 Repeatedly print the bitmap until user inputs a different character than '0' */
int main() {
    char userInput = '0';
    int i;
    int n;
    int pixel;

    while (userInput == '0') {
        for (i = 0; i < CHUCK_HEIGHT; i++) {
            for (n = 0; n < CHUCK_HEIGHT; n++) {
                pixel = (Chuck_bitmap[i] >> (31-(n&31))) & 1; /* uncomment for 32x32 bitmaps */
                if (pixel == 0) {
                    printf(".");
                } else {
                    printf("X");
                }
            }
            printf("\n");
        }

        scanf(" %c", &userInput);
    }
    return 0;
}