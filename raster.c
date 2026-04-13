#include "raster.h"

/* @author Paolo */
UINT16 *get_video_base() {
    volatile UINT8 *video_base_hi = (volatile UINT8 *)0xFFFF8201;
    volatile UINT8 *video_base_mi = (volatile UINT8 *)0xFFFF8203;

    unsigned long old_ssp;
    unsigned long addr;

    old_ssp = Super(0);

    addr = ((unsigned long)(*video_base_hi) << 16) | ((unsigned long)(*video_base_mi) << 8);

    Super(old_ssp);

    return (UINT16 *)addr;
}



/* @author: Gaurik*/
/* constants */
/* using the constants and doing basic arithmatic in the define statements so the all of these are done during compile time
 * making the program faster at runtime.
*/
/* #define SCREEN_WIDTH 640 
#define SCREEN_HEIGHT 400 

#define BYTES_PER_ROW (SCREEN_WIDTH >> 3) 
#define WORDS_PER_ROW (BYTES_PER_ROW >> 1) 
#define LONGS_PER_ROW (BYTES_PER_ROW >> 2) 


#define PIXEL_COUNT (SCREEN_WIDTH * SCREEN_HEIGHT) 

#define HOR_LONG_MASK ((UINT32)0xFFFFFFFF) 
#define NEG_HOR_LONG_MASK (~(HOR_LONG_MASK)) 
#define VER_LONG_MASK ((UINT32)0x80000000) 


UINT16 px_in_bounds(UINT16 row, UINT16 col) {
    return (col < SCREEN_WIDTH && row < SCREEN_HEIGHT);
}

void clear_screen(UINT32 *base){
	
	UINT32 *current = base;
	UINT16 section_count = PIXEL_COUNT >> 5;
	UINT16 i;
    for (i = 0; i < section_count; i++){
		*current = 0; 
		
		current++;
	}
}

void clear_region(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width) {
    UINT32 *curr_row;
    UINT32 leftmask;
    UINT32 rightmask;
    UINT16 c_end;
    UINT16 span;
    UINT16 r;
    UINT16 i;

    if (length == 0 || width == 0) return;

    c_end = col + width - 1;
    span = (c_end >> 5) - (col >> 5); 

    
    leftmask = ~(HOR_LONG_MASK >> (col & 31));
    rightmask = ~(HOR_LONG_MASK << (31 - (c_end & 31)));

    
    curr_row = base + (row * LONGS_PER_ROW) + (col >> 5);

    
    for (r = 0; r < length; r++) {
        
        if (span == 0) {
            
            curr_row[0] &= (leftmask | rightmask); 
        } else {
            
            curr_row[0] &= leftmask;

            
            for (i = 1; i < span; i++) {
                curr_row[i] = 0;
            }

            
            curr_row[span] &= rightmask;
        }

        curr_row += LONGS_PER_ROW;
    }
}

void plot_pixel(UINT8 *base, UINT16 row, UINT16 col){
	if (px_in_bounds(row, col)) {
        
        UINT8 *current = (base + (row * BYTES_PER_ROW) + (col >> 3));

        
        *current |= (1 << (7 - (col & 7)));
    }
}

void plot_horizontal_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length){

    UINT32 *start_point;  
    UINT32 *end_point; 
    UINT32 *current; 

    UINT32 leftmask; 
    UINT32 rightmask; 
    
    UINT32 end = (col + (length - 1)); 
    
    if (length == 0) return; 

    start_point = (base + (row * LONGS_PER_ROW) + (col >> 5));
    end_point = (base + (row * LONGS_PER_ROW) + (end >> 5));
    
    leftmask = HOR_LONG_MASK >> (col & 31); 
    rightmask = HOR_LONG_MASK << (31 - (end & 31)); 
    current = start_point; 

    if (start_point == end_point){ 
        *current |= (leftmask & rightmask); 
    } else {
        *start_point |= leftmask; 
        current = start_point + 1; 
        while(current < end_point){ 
            *current = HOR_LONG_MASK; 
            current++; 
        }
        *end_point |= rightmask; 
    }
}

void plot_vertical_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length){
    UINT32 *start_point;  
    UINT32 *end_point; 
    UINT32 *current; 
    
    UINT32 bitmask; 

    UINT32 end = (row + (length - 1)); 

    if (length == 0) return; 

    start_point = (base + (row * LONGS_PER_ROW) + (col >> 5));
    end_point = (base + (end * LONGS_PER_ROW) + (col >> 5));

    bitmask = VER_LONG_MASK >> (col & 31); 
    for(current = start_point; current <= end_point; current += LONGS_PER_ROW){ 
        *current |= bitmask; 
    }
}

void plot_line(UINT32 *base, UINT16 start_row, UINT16 start_col, UINT16 end_row, UINT16 end_col){
    
    
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;

    
        
    
    dx = (int)(end_col > start_col ? end_col - start_col : start_col - end_col);
    dy = -(int)(end_row > start_row ? end_row - start_row : start_row - end_row);

    
    sx = (start_col < end_col) ? 1 : -1;
    sy = (start_row < end_row) ? 1 : -1;

    err = dx + dy; 

    for (;;) {  
        
        plot_pixel(base, start_row, start_col);

        if (start_col == end_col && start_row == end_row) {
            break;
        }

        e2 = 2 * err;

        if (e2 >= dy) { 
            err += dy; 
            start_col += sx; 
        } 
            
        if (e2 <= dx) { 
            err += dx; 
            start_row += sy; 
        } 
    }
    
}

void plot_rectangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width){
     
   
    if (length == 0 || width == 0) return; 

    
    plot_horizontal_line(base, row, col, width);
    
    plot_horizontal_line(base, (row + length - 1), col, width);
    
    plot_vertical_line(base, row, col, length);
    
    plot_vertical_line(base, row, (col + width - 1), length);
}

void plot_square(UINT32 *base, UINT16 row, UINT16 col, UINT16 side){
    plot_rectangle(base, row, col, side, side);
}

void plot_triangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 trianglebase, UINT16 height, UINT8 direction){
    if (trianglebase == 0 || height == 0) return; 

    if (direction == 0) { 
        plot_horizontal_line(base, row, col, trianglebase); 
        plot_vertical_line(base, row, col, height);        
        plot_line(base, (row + (height - 1)), col, row, (col + (trianglebase - 1))); 

    } else if (direction == 1) { 
        plot_horizontal_line(base, row, (col - (trianglebase - 1)), trianglebase); 
        plot_vertical_line(base, row, col, height); 
        plot_line(base, (row + (height - 1)), col, row, (col - (trianglebase - 1))); 

    } else if (direction == 2) { 
        plot_horizontal_line(base, row, col, trianglebase); 
        plot_vertical_line(base, (row - (height - 1)), col, height); 
        plot_line(base, (row - (height - 1)), col, row, (col + (trianglebase - 1))); 

    } else if (direction == 3) { 
        plot_horizontal_line(base, row, (col - (trianglebase - 1)), trianglebase); 
        plot_vertical_line(base, (row - (height - 1)), col, height); 
        plot_line(base, (row - (height - 1)), col, row, (col - (trianglebase - 1))); 
    }
}


void plot_bitmap_8(UINT8 *base, UINT16 row, UINT16 col, UINT16 height, const UINT8 *bitmap) {
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

void plot_bitmap_16(UINT16 *base, UINT16 row, UINT16 col, UINT16 height, const UINT16 *bitmap){
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

void plot_bitmap_32(UINT32 *base, UINT16 row, UINT16 col, UINT16 height, const UINT32 *bitmap){
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
    UINT8 *start_point;      
    UINT8 *current;          
    UINT32 i;                
    UINT16 shift;            
    const UINT8 *character; 

    
    if (IS_PRINTABLE(ch)){
        
        character = GLYPH_START(ch);
        
        
        start_point = base + (row * BYTES_PER_ROW) + (col >> 3);
        current = start_point;
        
        
        shift = (col & 7);
        
        
        for(i = 0; i < 8; i++) {
            
            *current |= (character[i] >> shift);
            
            
            if (shift > 0){
                *(current + 1) |= (character[i] << (8 - shift));
            }
            
            
            current += BYTES_PER_ROW;
        }
    }
}

void plot_string(UINT8 *base, UINT16 row, UINT16 col, char *ch) {
    UINT8 *start_point;      
    UINT8 *current;          
    UINT16 i = 0;

    while (ch[i] != '\0') { 
        plot_character(base, row, col, ch[i]);
        i++;
        col += 8;
    }
}
 */