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
void plot_8_bitmap(UINT8 *base, UINT16 row, UINT16 col, UINT16 height, const UINT8 *bitmap) {
    UINT8 *current;
    UINT8 *start_point;
    UINT8 *end_point;
    UINT8 i; 
    UINT8 end;
    UINT8 shift;

    if (height == 0) return;
    if (row + height > 400) height = 400 - row; 
    
    end = row + (height - 1);
    shift = (col & 7); 
    start_point = base + (row * BYTES_PER_ROW) + (col >> 3);
    end_point = base + (end * BYTES_PER_ROW) + (col >> 3);
    i = 0;

    for (current = start_point; current <= end_point; current += BYTES_PER_ROW) {
        *current |= (bitmap[i] >> shift);

        if (shift > 0 && ((col >> 3) < (BYTES_PER_ROW - 1))){
            *(current + 1) |= (bitmap[i] << (8 - shift));
        }
        i++;
    }
}

void plot_16_bitmap(UINT16 *base, UINT16 row, UINT16 col, UINT16 height, const UINT16 *bitmap){
    UINT16 *current;
    UINT16 *start_point;
    UINT16 *end_point;
    UINT16 i; 
    UINT16 end;
    UINT16 shift;

    if (height == 0) return;
    if (row + height > 400) height = 400 - row;

    shift = (col & 15);
    end = row + (height - 1);
    start_point = base + (row * WORDS_PER_ROW) + (col >> 4);
    end_point = base + (end * WORDS_PER_ROW) + (col >> 4);

    i = 0;
    for (current = start_point; current <= end_point; current += WORDS_PER_ROW) {
        *current |= (bitmap[i] >> shift);
        if (shift > 0 && ((col >> 4) < (WORDS_PER_ROW - 1))){
            *(current + 1) |= (bitmap[i] << (16 - shift));
        }
        i++;
    }
}

void plot_32_bitmap(UINT32 *base, UINT16 row, UINT16 col, UINT16 height, const UINT32 *bitmap){
    UINT32 *current;
    UINT32 *start_point;
    UINT32 *end_point;
    UINT32 end;
    UINT32 i; 
    UINT32 shift;

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
