#include <stdio.h>
#include <stdint.h> // needed to use this for unsigned 64 bit integers https://stackoverflow.com/questions/9606455/how-to-specify-64-bit-integers-in-c

#define CHUCK_HEIGHT 32

// @author Paolo
// use uint32_t OR uint64_t OR unsigned long 
// find row X by (X+12)
// replace with a different bitmap to test with different images, just make sure to change the bit shift in the main function 
// if using a different size bitmap (ex: 64x64 vs 32x32)
const unsigned long Chuck_bitmap[CHUCK_HEIGHT] =
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

// @author Paolo
// Repeatedly print the bitmap until user inputs a different character than '0'
int main() {
    char userInput = '0';
    while (userInput == '0') {
        for (int i = 0; i < CHUCK_HEIGHT; i++) {
            for (int n = 0; n < CHUCK_HEIGHT; n++) {
                //int pixel = (Chuck_bitmap[i] >> (63-(n&63))) & 1; // uncomment for 64x64 bitmaps
                int pixel = (Chuck_bitmap[i] >> (31-(n&31))) & 1; // uncomment for 32x32 bitmaps
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