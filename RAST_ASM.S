;=====================CONSTANTS=====================================================================

SCREEN_WIDTH	EQU	640	; #define SCREEN_WIDTH
SCREEN_HEIGHT	EQU	400 ; #define SCREEN_HEIGHT

MAX_COL  EQU  (SCREEN_WIDTH-1)
MAX_ROW  EQU  (SCREEN_HEIGHT-1)

BYTES_PER_ROW	EQU (SCREEN_WIDTH>>3)	; #define BYTES_PER_ROW (SCREEN_WIDTH >> 3)
WORDS_PER_ROW	EQU (BYTES_PER_ROW>>1)	; #define WORDS_PER_ROW (BYTES_PER_ROW >> 1)
LONGS_PER_ROW	EQU (BYTES_PER_ROW>>2) ; #define LONGS_PER_ROW (BYTES_PER_ROW >> 2)

; the total pixels to be considered
PIXEL_COUNT	EQU	(SCREEN_WIDTH*SCREEN_HEIGHT)	; #define PIXEL_COUNT (SCREEN_WIDTH * SCREEN_HEIGHT) 

; masks
HOR_BYTE_MASK	EQU	$FF	; #define HOR_BYTE_MASK ((UINT8)0xFF)
HOR_WORD_MASK	EQU	$FFFF	; #define HOR_WORD_MASK ((UINT16)0xFFFF)
HOR_LONG_MASK	EQU	$FFFFFFFF ; #define HOR_LONG_MASK ((UINT32)0xFFFFFFFF)

VER_BYTE_MASK	EQU $80	; #define VER_BYTE_MASK ((UINT8)0x80)
VER_WORD_MASK	EQU $8000 ; #define VER_WORD_MASK ((UINT16)0x8000)
VER_LONG_MASK	EQU $80000000	; #define VER_LONG_MASK ((UINT32)0x80000000)

; for "boolean operations", using negative values to prevent mixups
TRUE	EQU	-1	
FALSE	EQU	-2	

; XBIOS Function constants
PHYSBASE    EQU 2

; GEMDOS Function constants
CNECOUT     EQU 2
CONIN       EQU 1

;=========================FUNCTIONS AND HELPER FUNCTIONS===========================================
;--------------CHECK FOR PIXEL COORDINATES BEING WITHIN BOUNDS-------------------------------------
;  PURPOSE: Checks if a coordinate is within the 640x400 screen limits.
;  INPUT: x-coordinate (column), y-coordinate (row)
;  RETURN: TRUE(-1) if in bounds, FALSE(-2) if out of bounds.
;  
; int px_in_bounds(UINT16 row, UINT16 col);
px_in_bounds:
	link	a6,#0	; no local variables
	move.l	d0,-(sp)	; to preserve d0	
	; the column index is stored at 8(a6)
	; the row index is stored in the next word, 10(a6)	
	move.w	8(a6),d0
	cmpi.w	#MAX_COL,d0
	bhi		out_of_bounds

	move.w	10(a6),d0
	cmpi.w	#MAX_ROW,d0
	bhi		out_of_bounds

	move.w	#TRUE,12(a6) ; push true flag onto the stack
	bra	px_in_bounds_end 

out_of_bounds:
	move.w	#FALSE,12(a6) ; push false flag onto stack
px_in_bounds_end:
	move.l	(sp)+,d0	; return orginal values to the register(s)
	unlk	a6
	
	rts
;-------------------------------------------------------------------------------------------------
;----------------------ROUTINE FOR CLEARING THE SCREEN--------------------------------------------
; PURPOSE: Clears the entire screen.
; INPUT: Address(UINT32*): to the start of the screen
; OUTPUT: NONE

;void clear_screen(UINT32 *base);
clear_screen:
	link	a6,#0	; no local variables
	movem.l	d0/a0,-(sp)

	move.l	base,a0 ; load address of base
	
	move.l	#PIXEL_COUNT,d0 ; load pixel count
	lsr.l	#5,d0	; get the number of longwords on the screen
	subq.l	#1,d0

clear_screen_loop:
	move.l	#0,(a0)	; set the entire longword to zero
	adda.l	#4,a0
	dbra	d0,clear_screen_loop

	movem.l	(sp)+,d0/a0
	unlk	a6
	
	rts

;-----------------ROUTINE FOR CLEARING A SPECIFIED RECTANGULAR REGION-----------------------------
; void clear_region(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width);;
;   UINT32 *row_ptr;
;   UINT32 leftmask;
;   UINT32 rightmask;
;   UINT16 c_end;
;   UINT16 span;
;   UINT16 r;
;   UINT16 i;
clear_region:
    link    a6,#-8  ; two local variables, longwords
    movem.l a0-a2/d0-d5,-(sp)

    ; if (length or width == 0 return )
    move.w  16(a6),d0   ; length
    ble     clear_region_done
    move.w  18(a6),d0   ; width
    ble     clear_region_done

    ; c_end calculation  col + width - 1
    move.w  18(a6),d1   ; get the width
    add.w   14(a6),d1   ; width + col
    subq    #1,d1       ; width + col - 1

    ; span calculation span = (c_end >> 5) - (col >> 5)
    move.w  d1,d2       ; get the c_end
    lsr.w   #5,d2       ; c_end >> 5
    move.w  14(a6),d0   ; get the col
    
    move.w  d0,d3       ; make a copy for mask calculation and row_ptr
    
    lsr.w   #5,d0       ; col >> 5
    sub.w   d0,d2       ; d2 now holds span

    ; left mask value calculations
    move.w  d3,d0       ; get the col in d0
    move.l  #HOR_LONG_MASK,d4 ; get the hor-mask
    and.w   #31,d0      ; col & 31
    lsr.l   d0,d4       ; HOR_MASK >> col & 31
    not.l   d4          ; oppsoite for a plot
    move.l  d4,-4(a6)   ; THE LEFT MASK
   
    ; right mask value calculations
    move.w  d1,d0       ; get c_end
    and.w   #31,d0      ; c_end & 31
    
    move.w  #31,d4 
    sub.w   d0,d4       ; 31 - c_end & 31
    move.l  #HOR_LONG_MASK,d0   ; the long mask
    lsl.l   d4,d0       ; mask << 31 - col & 31
    not.l   d0          ; opposite for a plot
    move.l  d0,-8(a6)   ; THE RIGHT MASK

    ; row_ptr calculation
    move.l  8(a6),a1    ; load base pointer into a1
    
    ; get column offset in bytes
    clr.l   d3          
    move.w  14(a6),d3   ; get col
    lsr.w   #5,d3       ; col >> 5
    lsl.w   #2,d3       ; get byte offset (longwords * 4)

    ; get row offset in bytes (row * 80)
    clr.l   d4          
    move.w  12(a6),d4   ; get row
    lsl.w   #4,d4       ; row * 2^4
    move.w  d4,d0       
    lsl.w   #2,d4       ; (row * 2^4) * 2^2 = row * 2^6
    add.w   d0,d4       ; (row * 2^6) + (row * 2^4) = row * 80 
    
    ; calculate final start address for row_ptr
    adda.l  d4,a1       ; add row byte offset to base pointer
    adda.l  d3,a1       ; THE ROW PTR

    ; prime the loop counters
    move.w  16(a6),d3   ; d3 = length
    subq.w  #1,d3       ; for dbra

clear_region_outer_loop:
    move.l  a1,a0       ; copy row_ptr to working pointer
    move.w  d2,d4       ; get span
    
    tst.w   d4          ; check if it fits in one lognword
    bne     handle_multiple_long_clear

    ; single longword clearing
    move.l  -4(a6),d0   ; left mask
    or.l    -8(a6),d0   ; OR'd with right mask
    and.l   d0,(a0)     ; clear the bits
    bra     clear_region_next_row

handle_multiple_long_clear:
    ; left edge
    move.l  -4(a6),d0   
    and.l   d0,(a0)+    ; clear and move to next longword
    
    ; clear all the middle
    subq.w  #1,d4       ; subtract the left edge
    subq.w  #1,d4       ; subtract 1, if there is a right edge bmi will fail
    bmi     handle_no_middle  ; if span was 1, skip middle

clear_region_middle_loop:
    clr.l   (a0)+       
    dbra    d4,clear_region_middle_loop

handle_no_middle:
    ; right edge
    move.l  -8(a6),d0
    and.l   d0,(a0)

clear_region_next_row:
    adda.w  #80,a1      ; move anchor to next row
    dbra    d3,clear_region_outer_loop

clear_region_done:
    movem.l (sp)+,a0-a2/d0-d5
    unlk    a6
    rts

;-------------------------------------------------------------------------------------------------
;---------------ROUTINE FOR PLOTTING A SINGLE PXIEL ONTO SPECIFIED COORDINATES--------------------
; void plot_pixel(UINT8 *base, UINT16 row, UINT16 col);
; PURPOSE: Plots a single pixel onto the screen
; INPUT: Address of the starting byte of the board
; OUTPUT: NONE
plot_pixel:
    link a6,#0
    movem.l d0-d2/a0,-(sp)
    
    subq.l  #2,sp ; reserves space for a return value
    move.w  10(a6),-(sp) ; push col number onto the stack
    move.w  8(a6),-(sp) ; push row number onto the stack
    
    jsr     px_in_bounds
    addq.l  #4,sp   ; clean up the stack, 2 words
    
    move.w (sp)+,d0 ; get the return value
    
    cmpi.w  #FALSE,d0 ; handle bounds errors
    beq     plot_pixel_end

    ; main logic if in bounds 
    ; base + (row*BYTES_PER_ROW) + (col >> 3)

    move.w  8(a6),d1 ; store row index for arithmatic (8(a6) is row)
    ; mulu.w  #BYTES_PER_ROW,d1 ; row*BYTES_PER_ROW can be optimsed using bitshifts
	; BYTES_PER_ROW for this is 80, 64+16, 2^6+2^4 thus two lsl commands could be potentially faster
    lsl.w   #4,d1         ; row * 2^4
    move.w  d1,d0         
    lsl.w   #2,d1         ; (row * 2^4) * 2^2 = row * 2^6
    add.w   d0,d1         ; (row * 2^6) + (row * 2^4) = row * 80

    
    move.w  10(a6),d2    ; store col index for arithmatic
    move.w  d2,d0        ; copy col for bit math later
    lsr.w   #3,d2        ; col >> 3
    
    add.l   d2,d1   ; (row*BYTES_PER_ROW) + (col >> 3)

    move.l  base,a0 ; load address
    adda.l  d1,a0   ; add total offset to the address register
    
    ; d0 still holds the original col index
    move.w  #7,d1 ; 7 for the arithmatic
    moveq   #1,d2 ; bitshift base
    
    and.w   #7,d0 ; col & 7
    sub.w   d0,d1   ; 7 - (col & 7)
    lsl.b   d1,d2 ; bitshifted 1 (shifted specifically for the target byte)

    or.b    d2,(a0) ; *current |= (1 << (7 - (col & 7)));
    

plot_pixel_end:
    movem.l (sp)+,d0-d2/a0  ; return original values to the register(s)
    unlk    a6
    rts
;-------------------------------------------------------------------------------------------------
;---------------------ROUTINE FOR PLOTTING A HORIZONTAL LINE--------------------------------------
;void plot_horizontal_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length);
; PURPOSE: PLOT A SINGLE HORIZONTAL LINE AT THE GIVEN COORDINATES AND OF A GIVEN LENGTH
; INPUT: COORDINATES X (COL) AND Y (ROW), LENGTH OF THE LINE TO BE PLOTTED
; OUTPUT: NONE
plot_horizontal_line:
    link    a6,#-10     ; 2 (long) masks, an offset value for the end address(word)
    movem.l d0-d3/a0-a2,-(sp) 

    move.w  12(a6),d2   ; get the length
    ble     plot_horizontal_line_end ; is length is 0, skip
    move.w  10(a6),d1   ; col value
    
    ; end calculations
    
    subq.w  #1,d2       ; length - 1 (using .w for coordinates)
    add.w   d1,d2       ; col + length - 1 
    move.w  d2,-10(a6)  ; END OFFSET

    ; cleft mask value claculations
    move.l  d1,d3       ; copy col
    andi.l  #31,d3      ; col & 31
    move.l  #HOR_LONG_MASK,d0
    lsr.l   d3,d0       ; leftmask = HOR_LONG_MASK >> (col & 31)
    move.l  d0,-4(a6)   ; left mask stored at -4(a6)
    
    ; rightmask value calculations
    move.w  -10(a6),d3  ; end offset value
    andi.w  #31,d3      ; end & 31
    move.w  #31,d2
    sub.w   d3,d2       ; (31 - (end & 31))
    move.l  #HOR_LONG_MASK,d0
    lsl.l   d2,d0
    move.l  d0,-8(a6)   ; RIGHTMASK

    ; Row offset calculations
    move.w  8(a6),d1    ; load row index
    lsl.w   #4,d1       ; row * 2^4
    move.w  d1,d0         
    lsl.w   #2,d1       ; row * 2^6
    add.w   d0,d1       ; (row * 2^4) + (row * 2^6) = row * 80

    ; start point calcualtion
    move.w  10(a6),d2   ; store col index
    lsr.w   #5,d2       ; col >> 5 (get longword offset)
    lsl.w   #2,d2       ; convert long to byte
    
    move.l  base,a0     
    adda.w  d1,a0       ; add row offset
    adda.w  d2,a0       ; THE START ADDRESS in a0

    ; end point calcultions
    move.w  -10(a6),d2  ; store end index
    lsr.w   #5,d2       ; end >> 5
    lsl.w   #2,d2       ; convert to byte offset

    move.l  base,a1     
    adda.w  d1,a1       ; Re-use row offset in d1
    adda.w  d2,a1       ; THE END ADDRESS in a1

	; main plotting logic
	; get the masks in d0 and d1
	move.l	-4(a6),d0	; the leftmask
	move.l	-8(a6),d1	; rightmask

	cmp.l	a0,a1	; if start_point == end_point
	bne		multiplot_horizontal_line ; !(if start_point == end_point)
	
	and.l	d1,d0	; leftmask & rightmaks 
	or.l	d0,(a0)	; current |= (leftmask & rigthmask)
	bra	plot_horizontal_line_end

multiplot_horizontal_line:
	move.l	a0,a2	; current = start_point
	
	or.l	d0,(a2)	; start_point |= leftmask

fill_h_line_loop:
	cmp.l	a2,a1
	beq		fill_h_line_loop_done
	move.l	#HOR_LONG_MASK,(a2)+

fill_h_line_loop_done:
	or.l	d1,(a1)	; end_point |= rightmask

plot_horizontal_line_end:
    movem.l (sp)+,d0-d3/a0-a2 
    unlk    a6
    rts

;-------------------------------------------------------------------------------------------------
;----------------ROUTINE TO PLOT A VERTICAL LINE--------------------------------------------------
; void plot_vertical_line(UINT32 *base, UINT16 row, UINT16 col, UINT16 length);
plot_vertical_line:
    link    a6,#-6          ; two local variables, a longword and a word
    movem.l d0-d4/a0-a1,-(sp) 

    move.w  12(a6),d3       ; get the length
    ble     plot_horizontal_line_end ; if lenght is 0, skip
    ; end Calculations
    move.w  8(a6),d1        ; get the row offset 
    
    move.l  d3,d4           ; copy length for the loop counter later
    subq.w  #1,d3           ; length - 1
    add.w   d1,d3           ; row + length - 1
    move.w  d3,-6(a6)       ; THE END OFFSET

    ; col offset calculation for reuse
    move.w  10(a6),d2       ; get the col index
    
    ; determine the BIT MASK for the vertical line
    move.l	#VER_LONG_MASK,d0
	move.l	d2,d3
	and.w	#31,d3	; col & 31
	lsr.l	d3,d0
	move.l	d0,-4(a6) ; the specific mask

    ; calculate the column byte offset
    lsr.w   #5,d2           ; col >> 5 (get longword index)
    lsl.w   #2,d2           ; convert long to byte offset
    
    ; start point calculation
    lsl.w   #4,d1           ; row * 2^4
    move.w  d1,d0          
    lsl.w   #2,d1           ; row * 2^2 * 2^4
    add.w   d0,d1           ; (row * 2^4) + (row * 2^6) = row * 80
    
    move.l  base,a0         ; load actual screen address
    adda.w  d1,a0           ; add row offset
    adda.w  d2,a0           ; THE START ADDRESS in a0

    ; end point calculations
    move.w  -6(a6),d1       ; get END OFFSET
    lsl.w   #4,d1           ; End Y * 2^4
    move.w  d1,d0          
    lsl.w   #2,d1           ; End Y * 2^2 * 2^4
    add.w   d0,d1           ; End Y * 80
    
    move.l  base,a1         
    adda.w  d1,a1           ; add row offset
    adda.w  d2,a1           ; THE END ADDRESS in a1

    ; main plotting logic
    move.l  -4(a6),d0       ; get the BIT MASK
    move.l  a0,a2           ; current = start_point

vertical_line_loop:
    or.l    d0,(a2)         ; plot the bit
    cmp.l   a2,a1           
    beq.s   plot_vertical_line_end
    adda.w  #80,a2          ; skip a row
    bra.s   vertical_line_loop

plot_vertical_line_end:
    movem.l (sp)+,d0-d4/a0-a2
    unlk    a6
    rts

;-------------------------------------------------------------------------------------------------
;------------------------------ROUTINE TO PLOT A LINE BETWEEN ANY TWO GIVEN POINT-----------------
; void plot_line(UINT32 *base, UINT16 start_row, UINT16 start_col, UINT16 end_row, UINT16 end_col);

;-------------------------------------------------------------------------------------------------
;--------------------ROUTINE TO PLOT A RECTANGLE--------------------------------------------------
; void plot_rectangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width);
; void plot_rectangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width);
plot_rectangle:
    link    a6,#0
    movem.l d0-d1,-(sp)

    move.w  18(a6),d1   ; get the width
    ble     plot_rectangle_done
    move.w  16(a6),d0   ; get the length
    ble     plot_rectangle_done

; reuseable calculations
; row + length - 1 in d0
    
    add.w   12(a6),d0   ; row + length
    subq    #1,d0       ; row + length -1
; col + width - 1 in d1
    
    add.w   14(a6),d1   ;   col + width 
    subq    #1,d1       ; col + width - 1

;   /* top line */
;   plot_horizontal_line(base, row, col, width);
    move.w  18(a6),-(sp)    ; push width
    move.w  14(a6),-(sp)    ; push col
    move.w  12(a6),-(sp)    ; push row
    move.l  8(a6),-(sp)     ; push base address
    jsr     plot_horizontal_line
    adda.l  #10,sp          ; clean up: 4 + 2+2+2 = 10 

;   /* bottom line */
;   plot_horizontal_line(base, (row + length - 1), col, width);
    move.w  18(a6),-(sp)    ; push width
    move.w  14(a6),-(sp)    ; push col
    move.w  d0,-(sp)        ; push row + length - 1
    move.l  8(a6),-(sp)     ; push base address
    jsr     plot_horizontal_line
    adda.l  #10,sp          

;   /* left line */
;   plot_vertical_line(base, row, col, length);
    move.w  16(a6),-(sp)    ; push length
    move.w  14(a6),-(sp)    ; push col
    move.w  12(a6),-(sp)    ; push row
    move.l  8(a6),-(sp)     ; push base address
    jsr     plot_vertical_line
    adda.l  #10,sp          

;   /* right line */
;   plot_vertical_line(base, row, (col + width - 1), length);
    move.w  16(a6),-(sp)    ; push length 
    move.w  d1,-(sp)        ; push col + width - 1 
    move.w  12(a6),-(sp)    ; push row
    move.l  8(a6),-(sp)     ; push base address
    jsr     plot_vertical_line
    adda.l  #10,sp          

plot_rectangle_done:
    movem.l (sp)+,d0-d1
    unlk    a6
    rts
;-------------------------------------------------------------------------------------------------
;--------------------ROUTINE TO PLOT A SQUARE-----------------------------------------------------
; void plot_square(UINT32 *base, UINT16 row, UINT16 col, UINT16 side);
plot_square:
    link    a6,#0

    move.w  16(a6),d0       ; side
    ble     plot_square_done

    move.w  d0,-(sp)        ; push side for width 
    move.w  d0,-(sp)        ; push side for length 
    move.w  14(a6),-(sp)    ; push col
    move.w  12(a6),-(sp)    ; push row
    move.l  8(a6),-(sp)     ; push base address
    
    jsr     plot_rectangle 
    
    ; 4 + 2+2+2+2 = 12
    adda.l  #12,sp          
    
plot_square_done:
    unlk    a6
    rts
;-------------------------------------------------------------------------------------------------
;-------------------------ROUTINE TO PLOT A TRIANGLE----------------------------------------------
; void plot_triangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 trianglebase, UINT16 height, UINT8 direction)
plot_triangle:
    link    a6,#0
    movem.l d0-d4/a0,-(sp)
    move.w  18(a6),d1   ; get the height
    tst.w   d1
    ble     plot_triangle_done
    move.w  16(a6),d2   ; get the triangle base
    ble     plot_triangle_done
    

plot_triangle_done:
    movem.l (sp)+,d0-d4/a0
    unlk    a6
    rts
    

;-------------------------------------------------------------------------------------------------
;=========================GLOBAL VARIABLES========================================================
base: ds.l	1
;-------------------------ROUTINE TO EXIT THE PROGRAM--------------------------------------------
; terminates the program
exit:   
            clr.w   -(sp)
            trap    #1
;-------------------------------------------------------------------------------------------------

