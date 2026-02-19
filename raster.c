#include "raster.h"

/* constants */
#define SCREEN_WIDTH 640 /* the horizontal size */
#define SCREEN_HEIGHT 400 /* the vertical size */

#define BYTES_PER_ROW (SCREEN_WIDTH >> 3)
#define LONGS_PER_ROW (BYTES_PER_ROW >> 2)

/* the total pixels to be considered */
#define PIXEL_COUNT (SCREEN_WIDTH * SCREEN_HEIGHT) 

/* masks */
#define HOR_BYTE_MASK 0xFF /* mask to handle the byte(s), for HORIZONAL */
#define HOR_WORD_MASK 0xFFFF /* mask to handle the owrd(s), for HORIZONAL */
#define HOR_LONG_MASK 0xFFFFFFFF /* mask to handle the longowrd(s), for HORIZONAL */

#define VER_BYTE_MASK 0x80 /* mask to handle the byte(s), for VERTICAL */
#define VER_WORD_MASK 0x8000 /* mask to handle the word(s), for VERTICAL */
#define VER_LONG_MASK 0x80000000 /* mask to handle the long(s), for VERTICAL */

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
}

void plot_pixel(UINT8 *base, UINT16 row, UINT16 col){
	if (px_in_bounds(row, col)) {
        /* Calculate (row * bytes_per_row) + (col / 8) */
        UINT8 *current = (base + (row * BYTES_PER_ROW) + (col >> 3));

        /* Bitwise OR to flip/maintain the bit */
        *current |= (1 << (7 - (col & 7)));
    }
}

void plot_horizontal_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length){

    UINT32 *start_point;  /* starting location */
    UINT32 *end_point; /* ending location */
    UINT32 *current; /* to track the current lonword */

    UINT32 leftmask; /* mask to handle the left partial longword */
    UINT32 rightmask; /* mask to handle the right partial longword */
    
    UINT32 end = (col + (length - 1)); /* for easier calculations */
    
    start_point = (base + (row * LONGS_PER_ROW) + (col >> 5));
    end_point = (base + (row * LONGS_PER_ROW) + (end >> 5));
    
    leftmask = HOR_LONG_MASK >> (col & 31); /* rightshifting for the start is more effictient */
    rightmask = HOR_LONG_MASK << (31 - (end & 31)); /* leftshifting for the end is more effictient */
    current = start_point; 

    if (start_point == end_point){ /* if the start and end addreses are the same */
        *current |= (leftmask & rightmask); /* &'ing the masks tohether creates a "stencil" */
    } else {
        *start_point |= leftmask; /* handle the left fringe */
        current = start_point + 1; /* move one longword forward */
        while(current < end_point){ /* loop till current address matches end point */
            *current = HOR_LONG_MASK; /* set all 1's without prejudice */
            current++; /* move to next longword */
        }
        *end_point |= rightmask; /* handle the right fringe */
    }
}

void plot_vertical_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length){
    UINT32 *start_point;  /* starting location */
    UINT32 *end_point; /* ending location */
    UINT32 *current; /* to track the current lonword */
    
    UINT32 bitmask; /* a specific mask for alignment anywhere in the longword */

    UINT32 end = (row + (length - 1)); /* for easier calculations */

    start_point = (base + (row * LONGS_PER_ROW) + (col >> 5));
    end_point = (base + (end * LONGS_PER_ROW) + (col >> 5));

    bitmask = VER_LONG_MASK >> (col & 31); /* creates a unique mask based on col input */
    for(current = start_point; current <= end_point; current += LONGS_PER_ROW){ /* loop vertically jumping 20 longwords at a time*/
        *current |= bitmask; /* use bitwise OR to prevent overwriting things */
    }
}

void plot_line(UINT32 *base, UINT16 start_row, UINT16 start_col, UINT16 end_row, UINT16 end_col){
    UINT32 *start_point;  /* starting location */
    UINT32 *end_point; /* ending location */
    UINT32 *current; /* to track the current lonword */

    start_point = base + (start_row * LONGS_PER_ROW) + (start_col >> 5);
    end_point = base + (end_row * LONGS_PER_ROW) + (end_col >> 5);

    if (start_row == end_row){ /* */
        plot_horizontal_line(base, start_row, start_col, (end_col - start_col));
    } else if (start_col == end_col){
        plot_vertical_line(base, start_row, start_col, (end_row - start_row));
    }
}

void plot_rectangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width){
    /* Length: the length (number of rows) in pixels of the rectangle
    * Width: the width (number of columns) in pixels of the rectangle */ 
    
    /* top line */
    plot_line(base, row, col, row, (col + (width - 1)));
    /* bottom line */
    plot_line(base, (row + (length - 1)), col, (row + (length - 1)), (col + (width - 1)));
    /* left line */
    plot_line(base, row, col, (row + (length - 1)), col);
    /* right line */
    plot_line(base, row, (col + (width - 1)), (row + (length - 1)), (col + (width - 1)));
}

void plot_square(UINT32 *base, UINT16 row, UINT16 col, UINT16 side){
  
   /* top line */
    plot_line(base, row, col, row, (col + (side - 1)));
    /* bottom line */
    plot_line(base, (row + (side - 1)), col, (row + (side - 1)), (col + (side - 1)));
    /* left line */
    plot_line(base, row, col, (row + (side - 1)), col);
    /* right line */
    plot_line(base, row, (col + (side - 1)), (row + (side - 1)), (col + (side - 1)));

}
