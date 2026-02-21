#include "raster.h"

/* @author: Gaurik*/
/* constants */
/* using the constants and doing basic arithmatic in the define statements so the all of these are done during compile time
 * making the program faster at runtime.
*/
#define SCREEN_WIDTH 640 /* the horizontal size */
#define SCREEN_HEIGHT 400 /* the vertical size */

#define BYTES_PER_ROW (SCREEN_WIDTH >> 3) /* how many bytes are in a single row of the screen */
#define WORDS_PER_ROW (BYTES_PER_ROW >> 1) /* how many words are in a single row of the screen */
#define LONGS_PER_ROW (BYTES_PER_ROW >> 2) /* how many longs are in a single row of the screen */

/* the total pixels to be considered */
#define PIXEL_COUNT (SCREEN_WIDTH * SCREEN_HEIGHT) 

/* masks */
#define HOR_BYTE_MASK ((UINT8)0xFF) /* all 1s mask to handle the byte(s), for HORIZONAL LINES */
#define HOR_WORD_MASK ((UINT16)0xFFFF) /* all 1's mask to handle the owrd(s), for HORIZONAL LINES*/
#define HOR_LONG_MASK ((UINT32)0xFFFFFFFF) /* all 1's mask to handle the longowrd(s), for HORIZONAL LINES */

#define NEG_HOR_LONG_MASK (~(HOR_LONG_MASK)) /* negated, all 0's mask to handle the longword(s), FOR HORIZONTAL */

#define VER_BYTE_MASK ((UINT8)0x80) /* 1 followed by all 0's mask to handle the byte(s), for VERTICAL LINES*/
#define VER_WORD_MASK ((UINT16)0x8000) /* 1 followed by all 0's mask to handle the word(s), for VERTICAL */
#define VER_LONG_MASK ((UINT32)0x80000000) /* 1 followed by all 0's mask to handle the long(s), for VERTICAL */

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
    /* seeing this as a filled rectangle to be plotted but with "negative masks." */
    /* 
    * a negtive mask is just negated masks in plot_horiozontal_line funtion looped for the specified
    * number of rows down like plot_veritcal_line function.
    * the & and | operations are negated too. 
    */
   
   UINT32 *start_point;  /* starting location */
   UINT32 *end_point; /* ending location */
   UINT32 *current; /* to track the current lonword, horizontal tracker */
   UINT32 *count; /* vertical tracker */
   UINT32 leftmask; /* mask to handle the left partial longword */
   UINT32 rightmask; /* mask to handle the right partial longword */

   UINT16 r_end = row + (length - 1);  /* calcuate the vertical offset for the end longword */
   UINT16 c_end = col + (width - 1); /* calcuate the horizontal offset for the end longword */

   UINT16 offset =  ((c_end >> 5) - (col >> 5)); /* cant use width directly as it wont always be perfectly aligned longword(s)
   so calcuate the numebr of 32 bit sections instead to get the offset for the end row */
   UINT32 *row_start; /* to get row start for indiviusal rwos inside the loop*/
   UINT32 *row_end; /* to get indivisual row ends inside the loops */
   
   if (length == 0 || width == 0) return; /* unless 2 dimesions are given, dont attempt to clear */

   start_point = base + (row * LONGS_PER_ROW) + (col >> 5); /* two offset calcuations since the area is 2D */
   end_point = base + (r_end * LONGS_PER_ROW) + (c_end >> 5); /* get the top_left and bottom-right coordinates */

   leftmask = ~(HOR_LONG_MASK >> (col & 31)); /* right shift for the start */
   rightmask = ~(HOR_LONG_MASK << (31 - (c_end & 31))); /*left shift for the end */

   for (current = start_point; current <= end_point; current += LONGS_PER_ROW) {
    row_start = current; /* the start point of the current row */
    /* end point of the current row */
    row_end = current + offset; 

    /* if both start and end are the same address, bitwise AND with both masks OR'd */
    if (row_start == row_end) *current &= (leftmask | rightmask); /* |'ing preserves any protected bits from both masks */
    else {
        *row_start &= leftmask; /* handle the partial longword on the left end */
        count = row_start + 1; /* get current to next longword */
        /* loop until just before end address */
        while (count < row_end){
            *count = 0; /* set to all 0's without prejudice */
            count++;
        }
        *row_end &= rightmask; /* handle the partial longword on the right end */
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

void plot_horizontal_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length){

    UINT32 *start_point;  /* starting location */
    UINT32 *end_point; /* ending location */
    UINT32 *current; /* to track the current lonword */

    UINT32 leftmask; /* mask to handle the left partial longword */
    UINT32 rightmask; /* mask to handle the right partial longword */
    
    UINT32 end = (col + (length - 1)); /* for easier calculations */
    
    if (length == 0) return; /* dont attempt if length is 0 */

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

    if (length == 0) return; /* dont attempt if length is zero */

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
    UINT32 temp;
    
    /* Bresenham Algoirthm stuff */
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;

    /* Initial pointers */
    start_point = base + (start_row * LONGS_PER_ROW) + (start_col >> 5);
    end_point = base + (end_row * LONGS_PER_ROW) + (end_col >> 5);

    /* Horizontal and Vertical */
    if (start_row == end_row) {
        if (start_col > end_col) {
            temp = start_col; 
            start_col = end_col; 
            end_col = temp;
        }
        plot_horizontal_line(base, start_row, start_col, (end_col - start_col + 1));
    } else if (start_col == end_col) {
        if (start_row > end_row) {
            temp = start_row; 
            start_row = end_row;
            end_row = temp;
        }
        plot_vertical_line(base, start_row, start_col, (end_row - start_row));
    } else {
        /* Bresenham Algorithm 
        * Based on and adapted from https://gist.github.com/bert/1085538#file-circle-c-L1
        */
        
        /* Calculate absolute differences safely for UINT16 */
        dx = (int)(end_col > start_col ? end_col - start_col : start_col - end_col);
        dy = -(int)(end_row > start_row ? end_row - start_row : start_row - end_row);

        /* Determine step direction */
        sx = (start_col < end_col) ? 1 : -1;
        sy = (start_row < end_row) ? 1 : -1;

        err = dx + dy; /* error value e_xy */

        for (;;) {  /* loop */
            /* Plot current pixel using your base pointer and coordinates */
            plot_pixel(base, start_row, start_col);

            if (start_col == end_col && start_row == end_row) {
                break;
            }

            e2 = 2 * err;

            if (e2 >= dy) { 
                err += dy; 
                start_col += sx; 
            } /* e_xy+e_x > 0 */
            
            if (e2 <= dx) { 
                err += dx; 
                start_row += sy; 
            } /* e_xy+e_y < 0 */
        }
    }
}

void plot_rectangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width){
    /* Length: the length (number of rows) in pixels of the rectangle
    * Width: the width (number of columns) in pixels of the rectangle */ 
   
    if (length == 0 || width == 0) return; /* unless 2 dimesions are given, dont attempt to plot */

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
    plot_rectangle(base, row, col, side, side);
}

void plot_triangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 trianglebase, UINT16 height, UINT8 direction){
    UINT32 *start_point;
    if (trianglebase == 0 || height == 0) return; /* unless valid inputs given, dont attempt to plot */

    if (direction == 0) { /* top-left coordinate, the height goes downwards adn base goes right */
        plot_line(base, row, col, row, (col + (trianglebase - 1))); /* plot base */
        plot_line(base, row, col, (row + (height - 1)), col); /* plot perpendicular */       
        plot_line(base, (row + (height - 1)), col, row, (col + (trianglebase - 1))); /* plot hypotenuse */

    } else if (direction == 1) { /* top-right coordinate, the height goes downwards and base goes left */
        plot_line(base, row, col, row, (col - (trianglebase - 1))); /* plot base */
        plot_line(base, row, col, (row + (height - 1)), col); /* plot perpendicular */
        plot_line(base, (row + (height - 1)), col, row, (col - (trianglebase - 1))); /* plot hypotenuse */

    } else if (direction == 2) { /* bottom-left coordinate, the hieght goes upwards and the base goes right */
        plot_line(base, row, col, row, (col + (trianglebase - 1))); /* plot base */
        plot_line(base, row, col, (row - (height - 1)), col); /* plot perpendicular */
        plot_line(base, (row - (height - 1)), col, row, (col + (trianglebase - 1))); /* plot hypotenuese */

    } else if (direction == 3) { /* bottom-right coordinate, the goes upwards and base goes left */
        plot_line(base, row, col, row, (col - (trianglebase - 1))); /* plot base */
        plot_line(base, row, col, (row - (height - 1)), col); /* plot_perpendicular */
        plot_line(base, (row - (height - 1)), col, row, (col - (trianglebase - 1))); /* plot hypotenuese */
    }
}

/* GNERAL FUCNTON STRUCTURE FOR THE BITMAP FUCNTIONS, 'X' IS THE WIDTH OF THE BITMAP- BYTE, WORD, LONGWORD....
 * HERE, TO MIMICK DIVISON BY BITSHIFTING RIGHT:
 *                             VALUE FOR BYTES IS 3
 *                             VALUE FOR WORDS IS 4
 *                             VALUE FOR LONGS IS 5
 *
 * POINTERS SHOULD MATCH THE BASE AND BITMAP DECLARATION OF SIZE, WHILE UINT16 IS USED AS ITS THE STANDARD 'INT' 
 * AND ACCOMADATED 2^16 VALUES WHICH IS ENOUGH FOR THE CURRENT DIMENSIONS, WHILE UINT8 ONLY GETS 2^8 WHICH IS NOT ENOUGH
 *
 * void plot_bitmap_x(UINTX *base, UINT16 row, UINT16 col, UINT16 height, const UINTX *bitmap) {
 *   
 * UINTX *current; "TO POINT TO THE CURRENT SECTION- BYTE, WORD OR LONGWORD"
 * UINTX *start_point; "TO GET A COORDINATE ON THE SCREEN AS THE TOP LEFT COORDINATE FOR THE BITMAP"
 * UINTX *end_point; "TO GET A COORDINATE ON THE SCREEN AS THE TOP LEFT COORDINATE FOR THE BITMAP"
 *
 * UINT16 i = 0; "LOOP COUNTER VARIABLE"
 * UINT16 end; "TO CALCULATE THE END OFFSET"
 * UINT16 shift; "TO CALCUATE THE SHIFT TO MANAGE PARTIAL-X RENDERS"
 *
 * if (height == 0){ "IF THE CHARACTER HAS NO HEIGHT DO NOT ATTEMPT TO PRINT"
 *  return; "THIS IS TO SAVE RESOURCES TO PREVENT OFFSCREEN ERRORS"
 *  }
 *
 * if (row + height > 400) {  "IF IRS TOO LOW TO BE FULLY PRINTED"
 *   height = 400 - row; "aADJUST HEIGHT TO GET RID OF THE EXCESS"
 * }
 *
 *  end = row + (height - 1); "CALCULATE THE ENDING ROW FOR GETTING THE OFFSET"
 *  shift = (col & (X-1)); "CALCULATE THE NUMBER OF BITSHIFTS TO HANDLE CROSS-X PLOTS"
 * 
 * "CALCULATE ADDRESS OF THE STARTING X BY THE ROW AND COL OFFSETS"
 *  start_point = base + (row * X_PER_ROW) + (col >> 3/4/5);
 * 
 * "CALCULATE ADDRESS OF THE ENDING X BY THE END AND COL OFFSETS"
 *  end_point = base + (end * X_PER_ROW) + (col >> 3/4/5);
 *
 *  "LOOP THROUGH THE ROWS"
 *  for (current = start_point; current <= end_point; current += X_PER_ROW) {
 *      "BITWISE OR THE BITSHIFTED BITMAP X AT THE CURRENT ADDRESS"
 *      *current |= (bitmap[i] >> shift);
 *
 *      "IF ANY SHIFT OPERATIONS WERE DONE AND COL INDEX IS LESS THAN LAST X"
 *      if (shift > 0 && ((col >> 3/4/5) < (X_PER_ROW - 1))){
 *           
 *          "GET TO THE NEXT X AND BITWISE OR IT WITH THE BITMAP SHIFTED THE OPPOSITE DIECTION. 
 *           BITMAP IS X WIDE, SO TO ISOLATE THE BITS THAT FELL OFF, BITSHIFT (X - shift) WILL GET RID
 *           OFF THE THE BITS PLOTTED ON THE ORIGINAL X."" 
 *          *(current + 1) |= (bitmap[i] << (X - shift));
 *      }
 *      i++; "INCREMENT i TO GET TO THE NEXT ROW ON THE BITMAP"
 *  }
 * }
*/
void plot_bitmap_8(UINT8 *base, UINT16 row, UINT16 col, UINT16 height, const UINT8 *bitmap) {
    UINT8 *current;
    UINT8 *start_point;
    UINT8 *end_point;
    UINT16 i = 0; 
    UINT16 end;
    UINT16 shift;

    if (height == 0) return;
    if (row + height > 400) height = 400 - row; 
    
    end = row + (height - 1);
    shift = (col & 7); 
    start_point = base + (row * BYTES_PER_ROW) + (col >> 3);
    end_point = base + (end * BYTES_PER_ROW) + (col >> 3);

    for (current = start_point; current <= end_point; current += BYTES_PER_ROW) {
        *current |= (bitmap[i] >> shift);

        if (shift > 0 && ((col >> 3) < (BYTES_PER_ROW - 1))){
            *(current + 1) |= (bitmap[i] << (8 - shift));
        }
        i++;
    }
}

void plot_bitmap_16(UINT16 *base, UINT16 row, UINT16 col, UINT16 height, const UINT16 *bitmap){
    UINT16 *current;
    UINT16 *start_point;
    UINT16 *end_point;
    UINT16 i = 0; 
    UINT16 end;
    UINT16 shift;

    if (height == 0) return;
    if (row + height > 400) height = 400 - row;

    shift = (col & 15);
    end = row + (height - 1);
    start_point = base + (row * WORDS_PER_ROW) + (col >> 4);
    end_point = base + (end * WORDS_PER_ROW) + (col >> 4);

    for (current = start_point; current <= end_point; current += WORDS_PER_ROW) {
        *current |= (bitmap[i] >> shift);
        if (shift > 0 && ((col >> 4) < (WORDS_PER_ROW - 1))){
            *(current + 1) |= (bitmap[i] << (16 - shift));
        }
        i++;
    }
}

void plot_bitmap_32(UINT32 *base, UINT16 row, UINT16 col, UINT16 height, const UINT32 *bitmap){
    UINT32 *current;
    UINT32 *start_point;
    UINT32 *end_point;
    UINT16 end;
    UINT16 i = 0; 
    UINT16 shift;

    if (height == 0) return;

    if (row + height > 400) height = 400 - row;

    end = row + (height - 1);
    shift = (col & 31);
    start_point = base + (row * LONGS_PER_ROW) + (col >> 5);
    end_point = base + (end * LONGS_PER_ROW) + (col >> 5);

    for (current = start_point; current <= end_point; current += LONGS_PER_ROW) {
        *current |= (bitmap[i] >> shift);
     
        if (shift > 0 && ((col >> 5) < (LONGS_PER_ROW - 1))){
            *(current + 1) |= (bitmap[i] << (32 - shift));
        }
        i++;
    }   
}

void plot_character(UINT8 *base, UINT16 row, UINT16 col, char ch){
    UINT8 *start_point;      /* starting position */
    UINT8 *current;          /*  current position */
    UINT32 i;                /* loop counter */
    UINT16 shift;            /* bit shift amount for aligning pixels with screen bytes */
    const UINT8 *character; /* pointer to the 8x8 bitmap data for the character */

    /* Check if the character is printable */
    if (IS_PRINTABLE(ch)){
        /* Get the glyph bitmap for the character from the font array */
        character = GLYPH_START(ch);
        
        /* Calculate the starting memory address */
        start_point = base + (row * BYTES_PER_ROW) + (col >> 3);
        current = start_point;
        
        /* Calculate bit shift */
        shift = (col & 7);
        
        /* Loop through the 8 rows of the 8x8 character glyph */
        for(i = 0; i < 8; i++) {
            /* Use bitwise OR to avoid overwriting existing screen pixels */
            *current |= (character[i] >> shift);
            
            /* If the character spans across two bytes (shift > 0),
             * plot the remaining pixels in the next byte by shifting left */
            if (shift > 0){
                *(current + 1) |= (character[i] << (8 - shift));
            }
            
            /* Move to the next row in screen memory */
            current += BYTES_PER_ROW;
        }
    }
}

void plot_string(UINT8 *base, UINT16 row, UINT16 col, char *ch) {
    UINT8 *start_point;      /* starting position */
    UINT8 *current;          /*  current position */
    UINT16 i = 0;

    while (ch[i] != '\0') { /* loop through screen using plot_character function */
        plot_character(base, row, col, ch[i]);
        i++;
        col += 8;
    }
}
