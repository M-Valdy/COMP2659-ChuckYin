#include "raster.h"

/* constants */
#define SCREEN_WIDTH 640 /* the horizontal size */
#define SCREEN_HEIGHT 400 /* the vertical size */

#define BYTES_PER_ROW (SCREEN_WIDTH >> 3)
#define LONGS_PER_ROW (BYTES_PER_ROW >> 2)

/* the total pixels to be considered */
#define PIXEL_COUNT (SCREEN_WIDTH * SCREEN_HEIGHT) 

/*
 * Helper Function: px_in_bounds
 * Purpose: Checks if a coordinate is within the 640x400 screen limits.
 * Input: x-coordinate (column), y-coordinate (row)
 * Return: 1 if in bounds, 0 if out of bounds.
 */
int px_in_bounds(UINT16 row, UINT16 col) {
    return (col < SCREEN_WIDTH && row < SCREEN_HEIGHT);
}

void clear_screen(UINT32 *base){
	/* using UINT32 will require the least iterations to cover the screen
	640*400 = 256,000 pixels; 256000/32 = 8000 iterations */
	UINT32 *current = base;
	UINT16 section_count = PIXEL_COUNT >> 5;
	UINT16 i;
    for (i = 0; i < section_count; i++){
		*current = 0; /* set the current section to all zeros */
		/* current is a longword and a single increment will move to the next longword */
		current++;
	}
}

void clear_region(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width){
    /* I. get to the correct postition, same logic as plot pixel */
    UINT32 *current; 
    /* using UINT32 because base is a UINT32 and may cause alignment isuues later */

	UINT16 long_width = width >> 5; /* the width in longwords instead of bits(indivisual pixels) */
	/* again, delaing with longwords, divided by 32 */

    UINT16 r;
    UINT16 c;
    /* II. loop to clear the region, outer loop for vertical and inner for horizontal */
    for (r = 0; r < length; r++) {
        /* calculate the start of the current row */
        /* recalcualting everytime to reset the horizontal when moving to the next line 
         * using LONGWORDS instead of bytes because "current" is a longword pointer so moves a longword
         * each time it is incremented.
         * Since we're using longwords instead of bytes here, >> 5 should be used unlike in
         * plot_pixel funtion since x >> n is x/(2^n) and n = 5 for a longword.
         * Also, using LONGS_PER_ROW which is just BYTES_PER_ROW/4 since current moves one longword at
         * a time so would otherwise moves 4 longwords instead of 4 bytes.
         * Additionally, width was divided by 32 because we're going by longword and it would clear more
         * than required.
        */
        current = base + ((row + r) * LONGS_PER_ROW) + (col >> 5); 
        
        /* loop through each longword in the horizontal section to clear it */
        for (c = 0; c < long_width; c++) {
            *current = 0;   /* set the current section to all zeros */
            current++;      /* Move to the next word */
        }
    }
}

void plot_pixel(UINT8 *base, UINT16 row, UINT16 col){
	if (px_in_bounds(row, col)) {
        /* Calculate (row * bytes_per_row) + (col / 8) */
        UINT8 *current = (base + (row * BYTES_PER_ROW) + (col >> 3));

        /* Bitwise OR to flip/maintain the bit */
        *current |= (1 << (7 - (col & 7)));
    }
}

