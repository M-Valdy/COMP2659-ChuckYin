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
; dx -12, dy -10, sx -8, sy -6, err -4, err2  -2
plot_line:
    link    a6,#-12     ; 6 ints is 12 bytes, so 12 bytes for local variables
    movem.l d3-d7/a1,-(sp) ; d3 start row, d4 start col, d5 end row, d6 end col, d7 for locals

set_regs:
    movea.l 8(a6),a1    ; load base address into a1
    move.w  12(a6),d3   ; start row
    move.w  14(a6),d4   ; start col
    move.w  16(a6),d5   ; end row
    move.w  18(a6),d6   ; end col 

calculate_diff:
;    dx = (int)(end_col > start_col ? end_col - start_col : start_col - end_col);
;    dy = -(int)(end_row > start_row ? end_row - start_row : start_row - end_row);
    cmp.w   d4,d6       ; if (end_col > start_col)
    bhi     dx_true
    move.w  d4,d7       ; false statement
    sub.w   d6,d7       ; start_col - end_col
    move.w  d7,-12(a6)  ; store dx
    bra     dy_calc
dx_true:
    move.w  d6,d7       ; true statement
    sub.w   d4,d7       ; end_col - start_col
    move.w  d7,-12(a6)  ; store dx
dy_calc:
    cmp.w   d3,d5
    bhi     dy_true
    move.w  d3,d7       ; false statement
    sub.w   d5,d7       ; start_row - end_row
    neg.w   d7          ; negate for the negative value
    move.w  d7,-10(a6)  ; store dy
    bra     step_direction
dy_true:
    move.w  d5,d7       ; true statement
    sub.w   d3,d7       ; end_row - start_row
    neg.w   d7          ; negate for the negative value
    move.w  d7,-10(a6)  ; store dy

step_direction:
;    sx = start_col < end_col ? 1 : -1;
;    sy = start_row < end_row ? 1 : -1;
    moveq   #1,d7       ; default step direction is 1 for sx
    move.w  d7,-8(a6)  ; store default sx value
    cmp.w   d4,d6       ; if endcol > start col, step is 1
    bhi     sx_done
    moveq   #-1,d7      ; else -1
    move.w  d7,-8(a6)  ; store sx value
sx_done:
    moveq   #1,d7  ; default step direction is 1 for sy
    move.w  d7,-6(a6)   ; store default sy value
    cmp.w   d3,d5        ; if endrow > start row, step is 1
    bhi     err_val
    moveq   #-1,d7      ; else -1
    move.w  d7,-6(a6)   ; store sy value

err_val:
;    err = dx + dy;  /* error value e_xy */
    move.w    -12(a6),d7
    add.w     -10(a6),d7
    move.w    d7,-4(a6)

plotting_loop:
;   plot_pixel(base, start_row, start_col);
    move.w  d4,-(sp)    ; push start_col, 2 bytes
    move.w  d3,-(sp)    ; push start_row, 2 bytes
    move.l  a1,-(sp)    ; push base address, 4 bytes
    jsr     plot_pixel
    adda.l  #8,sp       ; clean up the stack by 8 bytes
;   if (start_col == end_col && start_row == end_row)
    cmp.w   d4,d6
    bne     not_equal
    cmp.w   d3,d5
    bne     not_equal
    bra     plot_line_done
not_equal:
;   err2 = 2 * err;
    move.w  -4(a6),d7
    add.w   d7,d7
    move.w  d7,-2(a6)
first_if:
;   if (err2 >= dy) { err += dy; start_col += sx; }
    move.w  -2(a6),d7
    move.w  -10(a6),d6     ; get dy for comparison
    cmp.w   d7,d6     ; if (dy > err2)
    bgt     second_if
    move.w  -10(a6),d7     ; move dy back into d7
    add.w   d7,-4(a6)      ; err += dy
    move.w  -8(a6),d7      ; move sx into d7
    add.w   d7,d4          ; start_col += sx
second_if:
;   if (err2 <= dx) { err += dx; start_row += sy; }
    move.w  -2(a6),d7
    move.w  -12(a6),d6     ; get dx for comparison
    cmp.w   d7,d6     ; if (dx < err2)
    blt     plotting_loop
    move.w  -12(a6),d7     ; move dx back into d7
    add.w   d7,-4(a6)      ; err += dx
    move.w  -6(a6),d7      ; move sy into d7
    add.w   d7,d3          ; start_row += sy
    bra     plotting_loop

plot_line_done:
    movem.l (sp)+,d3-d7/a1
    unlk    a6
    rts

;-------------------------------------------------------------------------------------------------
;--------------------ROUTINE TO PLOT A RECTANGLE--------------------------------------------------
; void plot_rectangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width);
plot_rectangle:
    link    a6,#0
    movem.l d0-d1,-(sp)

    move.w  18(a6),d1   ; get the width
    tst.w   d1          ; check if width == 0
    ble     plot_rectangle_done
    move.w  16(a6),d0   ; get the length
    tst.w   d0          ; check if length == 0
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
    move.w  16(a6),d1   ; get the height
    tst.w   d1          ; check if height == 0
    ble     plot_triangle_done
    move.w  14(a6),d2   ; get the triangle base
    ble     plot_triangle_done
    move.w  12(a6),d3   ; get the col
    move.w  18(a6),d4   ; get the direction
    cmpi.w  #0,d4       ; check if direction == 0
    beq     plot_southeast_triangle
    cmpi.w  #1,d4       ; check if direction == 1
    beq     plot_southwest_triangle
    cmpi.w  #2,d4       ; check if direction == 2
    beq     plot_northeast_triangle
    cmpi.w  #3,d4       ; check if direction == 3
    beq     plot_northwest_triangle
    bra     plot_triangle_done  ; else done

plot_southeast_triangle:
    ; plot_line(base, row, col, row, (col + (trianglebase - 1))); 
    subq.w  #1,d2       ; trianglebase = trianglebase - 1
    add.w   12(a6),d2   ; col + trianglebase - 1
    move.w  d2,-(sp)    ; push col + trianglebase - 1
    move.w  10(a6),-(sp)    ; push row
    move.w  12(a6),-(sp)    ; push col
    move.w  10(a6),-(sp)    ; push row again
    move.l  8(a6),-(sp)     ; push base address
    jsr     plot_line       ; the line being plotted is the base
    add.l   #12,sp

    ; plot_line(base, row, col, (row + (height - 1)), col)
    move.w  12(a6),-(sp)    ; push col
    subq.w  #1,d1       ; height = height - 1
    add.w   10(a6),d1       ; row + height - 1
    move.w  d1,-(sp)        ; push row + height - 1
    move.w  12(a6),-(sp)    ; push col
    move.w  10(a6),-(sp)    ; push row
    move.l  8(a6),-(sp)     ; push base address
    jsr     plot_line       ; plot the perpendicular line
    add.l   #12,sp

    ; plot_line(base, (row + (height - 1)), col, row, (col + (trianglebase - 1)))
    move.w  d2,-(sp)    ; push col
    move.w  10(a6),-(sp)    ; push row
    move.w  d2,-(sp)    ; push col again
    move.w  d1,-(sp)    ; push row + height - 1
    move.l  8(a6),-(sp)     ; push base address
    jsr     plot_line       ; plot the hypotenuse
    add.l   #12,sp

    bra plot_triangle_done

plot_southwest_triangle:
    ; plot_line(base, row, col, row, (col - (trianglebase - 1)))
    move.w  14(a6),d2   ; get the triangle base
    subq.w  #1,d2       ; trianglebase - 1
    sub.w   d2,d3       ; col - (trianglebase - 1)
    move.w  d3,-(sp)    ; push col - (trianglebase - 1)
    move.w  10(a6),-(sp)    ; push row
    move.w  12(a6),-(sp)    ; push col
    move.w  10(a6),-(sp)    ; push row again
    move.l  8(a6),-(sp)     ; push base address
    jsr     plot_line       ; the line being plotted is the base
    add.l   #12,sp

    ; plot_line(base, row, col, (row + (height - 1)), col)
    move.w  12(a6),-(sp)    ; push col
    subq.w  #1,d1       ; height - 1
    add.w   10(a6),d1       ; row + height - 1
    move.w  d1,-(sp)        ; push row + height - 1
    move.w  12(a6),-(sp)    ; push col
    move.w  10(a6),-(sp)    ; push row
    move.l  8(a6),-(sp)     ; push base address
    jsr     plot_line       ; plot the perpendicular line
    add.l   #12,sp

    ; plot_line(base, (row + (height - 1)), col, row, (col - (trianglebase - 1)))
    move.w  d3,-(sp)    ; push col - (trianglebase - 1)
    move.w  10(a6),-(sp)    ; push row
    move.w  12(a6),-(sp)    ; push col
    move.w  d1,-(sp)    ; push row + height - 1
    move.l  8(a6),-(sp)     ; push base address
    jsr     plot_line       ; plot the hypotenuse
    add.l   #12,sp

    bra plot_triangle_done

plot_northeast_triangle:
    ; plot_line(base, row, col, row, (col + (trianglebase - 1)))
    move.w  14(a6),d2   ; get the triangle base
    subq.w  #1,d2       ; trianglebase - 1
    add.w   12(a6),d2   ; col + trianglebase - 1
    move.w  d2,-(sp)    ; push col + trianglebase - 1
    move.w  10(a6),-(sp)    ; push row
    move.w  12(a6),-(sp)    ; push col
    move.w  10(a6),-(sp)    ; push row again
    move.l  8(a6),-(sp)     ; push base address
    jsr     plot_line       ; the line being plotted is the base
    add.l   #12,sp

    ; plot_line(base, row, col, (row - (height - 1)), col)
    move.w  d3,-(sp)        ; push col (same as before)
    subq.w  #1,d1           ; height = height - 1
    sub.w   d1,10(a6)       ; row - height + 1
    move.w  d3,-(sp)        ; push col again
    move.w  d1,-(sp)        ; push row - (height - 1)
    move.l  8(a6),-(sp)     ; push base address
    jsr     plot_line       ; plot the perpendicular line
    add.l   #12,sp

    ; plot_line(base, (row - (height - 1)), col, row, (col + (trianglebase - 1)))
    move.w  d2,-(sp)    ; push col + trianglebase - 1
    move.w  10(a6),-(sp)    ; push row
    move.w  12(a6),-(sp)    ; push col
    move.w  d1,-(sp)        ; push row - (height - 1)
    move.l  8(a6),-(sp)     ; push base address
    jsr     plot_line       ; plot the hypotenuse line
    add.l   #12,sp
    bra plot_triangle_done

plot_triangle_done:
    movem.l (sp)+,d0-d4/a0
    unlk    a6
    rts
    
;-------------------------------------------------------------------------------------------------
;-------------------------ROUTINE TO PLOT A BITMAP_8----------------------------------------------
; void plot_bitmap_8(UINT8 *base, UINT16 row, UINT16 col, UINT16 height, const UINT8 *bitmap)
plot_bitmap_8:
    link   a6,#-20
    movem.l d0-d3/a0-a4,-(sp)
    move.w  16(a6),d1   ; get the height
    tst.w   d1          ; check if height == 0
    beq     plot_bitmap_8_done
    add.w   12(a6),d1   ; row + height
    cmpi.w  #400,d1   ; check if row + height > 400
    bgt     bitmap_8_too_large
    bra     bitmap_8_init

bitmap_8_too_large:
    move.w  #400,d1
    sub.w   12(a6),d1   ; height = 400 - row
    move.w  d1,16(a6)   ; store height
    bra    bitmap_8_init

bitmap_8_init:
    move.w  16(a6),d2   ; get the height
    subq.w  #1,d2   ; height - 1
    move.w  d2,-6(a6)   ; store height - 1
    add.w   12(a6),d2   ; row + height - 1
    move.w  d2,-6(a6)   ; end = row + height - 1

    move.w  14(a6),d3   ; get the col
    and.w   #7,d3       ; col & 7
    move.w  d3,-2(a6)   ; shift = (col & 7)

    move.w  14(a6),d3   ; move col to d3    
    lsr.w   #3,d3       ; col >> 3
    move.w  12(a6),d0   ; get row
    mulu.w  #BYTES_PER_ROW,d0       ; row * BYTES_PER_ROW
    add.w   d3,d0       ; row * BYTES_PER_ROW + (col >> 3)
    move.l  8(a6),a0     ; load base address
    adda.l  d0,a0      ; base + row * BYTES_PER_ROW + (col >> 3)
    move.l  a0,-10(a6)   ; start_point = base + (row * BYTES_PER_ROW) + (col >> 3)
    
    move.w  -6(a6),d1   ; get end value (row + height - 1
    mulu.w  #BYTES_PER_ROW,d1   ; (end * BYTES_PER_ROW)
    add.w   d3,d1       ; (end * BYTES_PER_ROW) + (col >> 3)
    move.l  8(a6),a1     ; load base address
    adda.l  d1,a1      ; base + end * BYTES_PER_ROW + (col >> 3)
    move.l  a1,-8(a6)   ; end_point = base + (end * BYTES_PER_ROW) + (col >> 3)

    move.l  a0,-12(a6)   ; current = start_point
    move.l  -12(a6),a3

    movea.l 18(a6),a4   ; load bitmap address into a4 (20(a6) is the bitmap address)

bitmap_8_loop:
    cmpa.l  a1,a3    ; if current <= end_point
    bhi     plot_bitmap_8_done  ; if current > end_point, done

    move.l  (a4)+,d2     ; load bitmap address
    move.w  -2(a6),d0   ; get shift value
    lsr.l   d0,d2       ; bitmap >> shift for the byte offset
    or.l    d2,(a3)   ; *current |= (bitmap[i] >> shift)

    tst.w   -2(a6)       ; check if shift is 0
    bge     bitmap8_increment
    move.w   #BYTES_PER_ROW,d0
    subq.w  #1,d0       ; BYTES_PER_ROW - 1
    cmp.w   d0,d3       ; if (col >> 3) < BYTES_PER_ROW - 1
    bge     bitmap8_increment
    move.w  -2(a6),d0
    move.w  #8,d1
    sub.w   d0,d1       ; 8 - shift
    lsl.l   d1,d2       ; bitmap[i] << (8 - shift)
    or.b    d2,(a3)   ; *(current + 1) |= (bitmap[i] << (8 - shift))
    move.l  a3,-12(a6)   ; move new result to current for the next loop
    bra     bitmap_8_increment

bitmap8_increment:
    adda.l  #BYTES_PER_ROW,a3   ; current += BYTES_PER_ROW
    move.l  a3,-12(a6)   ; move new result to current for the next loop
    bra     bitmap_8_loop

plot_bitmap_8_done:
    movem.l (sp)+,d0-d3/a0-a4
    unlk    a6
    rts

;-------------------------------------------------------------------------------------------------
;-------------------------ROUTINE TO PLOT A BITMAP_16----------------------------------------------
; void plot_bitmap_16(UINT16 *base, UINT16 row, UINT16 col, UINT16 height, const UINT16 *bitmap)
plot_bitmap_16:
    link   a6,#-20
    movem.l d0-d3/a0-a4,-(sp)
    move.w  16(a6),d1   ; get the height
    tst.w   d1          ; check if height == 0
    beq     plot_bitmap_16_done
    add.w   12(a6),d1   ; row + height
    cmpi.w  #400,d1   ; check if row + height > 400
    bgt     bitmap_16_too_large
    bra     bitmap_16_variable_init

bitmap_16_too_large:
    move.w  #400,d1
    sub.w   12(a6),d1   ; height = 400 - row
    move.w  d1,16(a6)   ; store height
    bra    bitmap_16_variable_init

bitmap_16_variable_init:
    move.w  16(a6),d2   ; get the height
    subq.w  #1,d2   ; height - 1
    move.w  d2,-6(a6)   ; store height - 1
    add.w   12(a6),d2   ; row + height - 1
    move.w  d2,-6(a6)   ; end = row + height - 1

    move.w  14(a6),d3   ; get the col
    and.w   #15,d3       ; col & 15
    move.w  d3,-2(a6)   ; shift = (col & 15)

    move.w  14(a6),d3   ; move col to d3    
    lsr.w   #4,d3       ; col >> 4
    move.w  12(a6),d0   ; get row
    mulu.w  #WORDS_PER_ROW,d0       ; row * WORDS_PER_ROW
    add.w   d3,d0       ; row * WORDS_PER_ROW + (col >> 4)
    move.l  8(a6),a0     ; load base address
    adda.l  d0,a0      ; base + row * WORDS_PER_ROW + (col >> 4)
    move.l  a0,-10(a6)   ; start_point = base + (row * WORDS_PER_ROW) + (col >> 4)
    
    move.w  -6(a6),d1   ; get end value (row + height - 1
    mulu.w  #WORDS_PER_ROW,d1   ; (end * WORDS_PER_ROW)
    add.w   d3,d1       ; (end * WORDS_PER_ROW) + (col >> 4)
    move.l  8(a6),a1     ; load base address
    adda.l  d1,a1      ; base + end * WORDS_PER_ROW + (col >> 4)
    move.l  a1,-8(a6)   ; end_point = base + (end * WORDS_PER_ROW) + (col >> 4)

    move.l  a0,-12(a6)   ; current = start_point
    move.l  -12(a6),a3

    movea.l 18(a6),a4   ; load bitmap address into a4 (20(a6) is the bitmap address)

bitmap_16_loop:
    cmpa.l  a1,a3    ; if current <= end_point
    bhi     plot_bitmap_16_done  ; if current > end_point, done

    move.l  (a4)+,d2     ; load bitmap address
    move.w  -2(a6),d0   ; get shift value
    lsr.l   d0,d2       ; bitmap >> shift for the byte offset
    or.l    d2,(a3)   ; *current |= (bitmap[i] >> shift)

    tst.w   -2(a6)       ; check if shift is 0
    bge     bitmap16_increment
    move.w   #WORDS_PER_ROW,d0
    subq.w  #1,d0       ; WORDS_PER_ROW - 1
    cmp.w   d0,d3       ; if (col >> 4) < WORDS_PER_ROW - 1
    bge     bitmap16_increment
    move.w  -2(a6),d0
    move.w  #16,d1
    sub.w   d0,d1       ; 16 - shift
    lsl.l   d1,d2       ; bitmap[i] << (16 - shift)
    or.b    d2,(a3)   ; *(current + 1) |= (bitmap[i] << (16 - shift))
    move.l  a3,-12(a6)   ; move new result to current for the next loop
    bra     bitmap16_increment

bitmap16_increment:
    adda.l  #WORDS_PER_ROW,a3   ; current += WORDS_PER_ROW
    move.l  a3,-12(a6)   ; move new result to current for the next loop
    bra     bitmap_16_loop

plot_bitmap_16_done:
    movem.l (sp)+,d0-d3/a0-a4
    unlk    a6
    rts

;-------------------------------------------------------------------------------------------------
;-------------------------ROUTINE TO PLOT A BITMAP_32----------------------------------------------
; void plot_bitmap_32(UINT32 *base, UINT16 row, UINT16 col, UINT16 height, const UINT32 *bitmap)


;-------------------------------------------------------------------------------------------------
;=========================GLOBAL VARIABLES========================================================
base: ds.l	1
;-------------------------ROUTINE TO EXIT THE PROGRAM--------------------------------------------
; terminates the program
exit:   
            clr.w   -(sp)
            trap    #1
;-------------------------------------------------------------------------------------------------

