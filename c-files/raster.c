#include "raster.h"

/**
 * Helper Function: px_in_bounds
 * Purpose: Checks if a coordinate is within the 640x400 screen limits.
 * Input: x (column), y (row)
 * Return: 1 if in bounds, 0 if out of bounds.
 */
int px_in_bounds(UINT16 x, UINT16 y) {
    return (x < 640 && y < 400);
}

void clear_screen(UINT32 *base){
	/* using UINT32 will require the least iterations to cover the screen
	640*400 = 256,000 pixels; 256000/32 = 8000 iterations */
	UINT32 *current = base;
	for (int i = 0; i < 8000; i++){
		*current = 0; /* set the current section to all zeros */
		/* current is a longword and a single increment will move to the next longword */
		current++;
	}
}

void plot_pixel(UINT8 *base, UINT16 row, UINT16 col){
	if (px_in_bounds(col, row)) {
        /* Calculate (row * bytes_per_row) + (col / 8) */
        UINT8 *target_byte = base + (row * 80) + (col >> 3);

        /* Bitwise OR to flip/maintain the bit */
        *target_byte |= (1 << (7 - (col & 7)));
    }
}