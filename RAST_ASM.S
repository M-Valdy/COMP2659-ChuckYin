; @author Gaurik for the raster library and Paolo for set_video_base

    XDEF _clear_screen
    XDEF _clear_region
    XDEF _plot_pixel
    XDEF _plot_horizontal_line
    XDEF _plot_vertical_line
    XDEF _plot_line
    XDEF _plot_rectangle
    XDEF _plot_square
    XDEF _plot_triangle
    XDEF _plot_8_bitmap
    XDEF _plot_16_bitmap
    XDEF _plot_32_bitmap
    XDEF _plot_character
    XDEF _plot_string
    XDEF _set_video_base
;=====================CONSTANTS=====================================================================

SCREEN_WIDTH	EQU	640	
SCREEN_HEIGHT	EQU	400

MAX_COL  EQU  (SCREEN_WIDTH-1)
MAX_ROW  EQU  (SCREEN_HEIGHT-1)

BYTES_PER_ROW	EQU (SCREEN_WIDTH>>3)
WORDS_PER_ROW	EQU (BYTES_PER_ROW>>1)	
LONGS_PER_ROW	EQU (BYTES_PER_ROW>>2) 

PIXEL_COUNT	EQU	(SCREEN_WIDTH*SCREEN_HEIGHT)

HOR_LONG_MASK	EQU	$FFFFFFFF

VER_LONG_MASK	EQU $80000000

TRUE	EQU	-1	
FALSE	EQU	-2	
;=========================FUNCTIONS AND HELPER FUNCTIONS===========================================
;--------------CHECK FOR PIXEL COORDINATES BEING WITHIN BOUNDS-------------------------------------
_px_in_bounds:
	link	a6,#0	
	move.l	d0,-(sp)	
	move.w	8(a6),d0
	cmpi.w	#MAX_COL,d0
	bhi		out_of_bounds

	move.w	10(a6),d0
	cmpi.w	#MAX_ROW,d0
	bhi		out_of_bounds

	move.w	#TRUE,12(a6)
	bra	px_in_bounds_end 

out_of_bounds:
	move.w	#FALSE,12(a6) 

px_in_bounds_end:
	move.l	(sp)+,d0
	unlk	a6
	
	rts
;-------------------------------------------------------------------------------------------------
;----------------------ROUTINE FOR CLEARING THE SCREEN--------------------------------------------
_clear_screen:
	link	a6,#0	
	movem.l	d0/a0,-(sp)

	move.l	8(a6),a0 
	
	move.l	#PIXEL_COUNT,d0 
	lsr.l	#5,d0
	subq.l	#1,d0

clear_screen_loop:
	move.l	#0,(a0)
	adda.l	#4,a0
	dbra	d0,clear_screen_loop

	movem.l	(sp)+,d0/a0
	unlk	a6
	
	rts
;-------------------------------------------------------------------------------------------------
;-----------------ROUTINE FOR CLEARING A SPECIFIED RECTANGULAR REGION-----------------------------
_clear_region:
    link    a6,#-8  
    movem.l a0-a2/d0-d5,-(sp)

    ; if (length or width == 0 return )
    move.w  16(a6),d0   ; length
    ble     clear_region_done
    move.w  18(a6),d0   ; width
    ble     clear_region_done

    ; c_end calculation  col + width - 1
    move.w  18(a6),d1   
    add.w   14(a6),d1   
    subq    #1,d1

    ; span calculation span = (c_end >> 5) - (col >> 5)
    move.w  d1,d2       
    lsr.w   #5,d2       
    move.w  14(a6),d0  
    
    move.w  d0,d3
    
    lsr.w   #5,d0
    sub.w   d0,d2

    ; left mask value calculations
    move.w  d3,d0      
    move.l  #HOR_LONG_MASK,d4 
    and.w   #31,d0
    lsr.l   d0,d4      
    not.l   d4 
    move.l  d4,-4(a6)   ; THE LEFT MASK
   
    ; right mask value calculations
    move.w  d1,d0 
    and.w   #31,d0
    
    move.w  #31,d4 
    sub.w   d0,d4  
    move.l  #HOR_LONG_MASK,d0 
    lsl.l   d4,d0
    not.l   d0
    move.l  d0,-8(a6)   ; THE RIGHT MASK

    ; row_ptr calculation
    move.l  8(a6),a1 
    
    clr.l   d3          
    move.w  14(a6),d3  
    lsr.w   #5,d3 
    lsl.w   #2,d3

    clr.l   d4          
    move.w  12(a6),d4  
    lsl.w   #4,d4 
    move.w  d4,d0       
    lsl.w   #2,d4  
    add.w   d0,d4
    
    ; calculate final start address for row_ptr
    adda.l  d4,a1
    adda.l  d3,a1

    ; prime the loop counters
    move.w  16(a6),d3 
    subq.w  #1,d3   ; for dbra

clear_region_outer_loop:
    move.l  a1,a0
    move.w  d2,d4
    
    tst.w   d4
    bne     handle_multiple_long_clear

    ; single longword clearing
    move.l  -4(a6),d0 
    or.l    -8(a6),d0  
    and.l   d0,(a0)     
    bra     clear_region_next_row

handle_multiple_long_clear:
    ; left edge
    move.l  -4(a6),d0   
    and.l   d0,(a0)+ 
    
    ; clear all the middle
    subq.w  #1,d4   
    subq.w  #1,d4    
    bmi     handle_no_middle

clear_region_middle_loop:
    clr.l   (a0)+       
    dbra    d4,clear_region_middle_loop

handle_no_middle:
    ; right edge
    move.l  -8(a6),d0
    and.l   d0,(a0)

clear_region_next_row:
    adda.w  #80,a1
    dbra    d3,clear_region_outer_loop

clear_region_done:
    movem.l (sp)+,a0-a2/d0-d5
    unlk    a6
    rts
;-------------------------------------------------------------------------------------------------
;---------------ROUTINE FOR PLOTTING A SINGLE PXIEL ONTO SPECIFIED COORDINATES--------------------
_plot_pixel:
    link a6,#0
    movem.l d0-d2/a0,-(sp)
    
    subq.l  #2,sp ; reserves space for a return value
    move.w  14(a6),-(sp) 
    move.w  12(a6),-(sp)
    
    jsr     _px_in_bounds
    
    move.w (sp)+,d0 
    addq.l  #4,sp

    cmpi.w  #FALSE,d0
    beq     plot_pixel_end

    ; main logic if in bounds 
    move.w  12(a6),d1 
    lsl.w   #4,d1    
    move.w  d1,d0         
    lsl.w   #2,d1     
    add.w   d0,d1
    
    move.w  14(a6),d2    
    move.w  d2,d0      
    lsr.w   #3,d2
    
    add.l   d2,d1 

    move.l  8(a6),a0 
    adda.l  d1,a0
    
    move.w  #7,d1 
    moveq   #1,d2
    
    and.w   #7,d0 
    sub.w   d0,d1 
    lsl.b   d1,d2

    or.b    d2,(a0)
    
plot_pixel_end:
    movem.l (sp)+,d0-d2/a0
    unlk    a6
    rts
;-------------------------------------------------------------------------------------------------
;---------------------ROUTINE FOR PLOTTING A HORIZONTAL LINE--------------------------------------
_plot_horizontal_line:
    link    a6,#-10 
    movem.l d0-d3/a0-a2,-(sp) 

    move.w  16(a6),d2 
    ble     plot_horizontal_line_end 
    move.w  14(a6),d1 
    
    ; end calculations
    subq.w  #1,d2       
    add.w   d1,d2      
    move.w  d2,-10(a6) 

    ; left mask value claculations
    move.l  d1,d3      
    andi.l  #31,d3   
    move.l  #HOR_LONG_MASK,d0
    lsr.l   d3,d0
    move.l  d0,-4(a6) ; LEFTMASK
    
    ; rightmask value calculations
    move.w  -10(a6),d3  
    andi.w  #31,d3 
    move.w  #31,d2
    sub.w   d3,d2 
    move.l  #HOR_LONG_MASK,d0
    lsl.l   d2,d0
    move.l  d0,-8(a6)   ; RIGHTMASK

    ; Row offset calculations
    move.w  12(a6),d1    
    lsl.w   #4,d1  
    move.w  d1,d0         
    lsl.w   #2,d1 
    add.w   d0,d1

    ; start point calcualtion
    move.w  14(a6),d2 
    lsr.w   #5,d2 
    lsl.w   #2,d2
    
    move.l  8(a6),a0     
    adda.w  d1,a0
    adda.w  d2,a0

    ; end point calcultions
    move.w  -10(a6),d2 
    lsr.w   #5,d2
    lsl.w   #2,d2

    move.l  8(a6),a1     
    adda.w  d1,a1
    adda.w  d2,a1

    ; main plotting logic
    move.l  -4(a6),d0   ; the leftmask
    move.l  -8(a6),d1   ; rightmask

    cmp.l   a0,a1
    bne     multiplot_horizontal_line
    
    and.l   d1,d0   ; leftmask & rightmask 
    or.l    d0,(a0) 
    bra plot_horizontal_line_end

multiplot_horizontal_line:
    move.l  a0,a2
    
    or.l    d0,(a2)+

fill_h_line_loop:
    cmp.l   a2,a1
    beq     fill_h_line_loop_done
    move.l  #HOR_LONG_MASK,(a2)+
    bra     fill_h_line_loop

fill_h_line_loop_done:
    or.l    d1,(a1)

plot_horizontal_line_end:
    movem.l (sp)+,d0-d3/a0-a2 
    unlk    a6
    rts
;-------------------------------------------------------------------------------------------------
;---------------------ROUTINE FOR PLOTTING A VERTICAL LINE--------------------------------------
_plot_vertical_line:
    link    a6,#-6 
    movem.l d0-d4/a0-a2,-(sp) 

    move.w  16(a6),d3 
    ble     plot_vertical_line_end 
    
    ; end Calculations
    move.w  12(a6),d1      
    
    move.w  d3,d4 
    subq.w  #1,d3   
    add.w   d1,d3  
    move.w  d3,-6(a6)

    ; col offset calculation for reuse
    move.w  14(a6),d2
    
    ; determine the BIT MASK for the vertical line
    move.l  #VER_LONG_MASK,d0
    move.l  d2,d3
    andi.l  #31,d3
    lsr.l   d3,d0
    move.l  d0,-4(a6)

    ; calculate the column byte offset
    lsr.w   #5,d2
    lsl.w   #2,d2
    
    ; start point calculation
    lsl.w   #4,d1
    move.w  d1,d0           
    lsl.w   #2,d1
    add.w   d0,d1
    
    move.l  8(a6),a0
    adda.w  d1,a0
    adda.w  d2,a0

    ; end point calculations
    move.w  -6(a6),d1
    lsl.w   #4,d1    
    move.w  d1,d0           
    lsl.w   #2,d1  
    add.w   d0,d1  
    
    move.l  8(a6),a1         
    adda.w  d1,a1  
    adda.w  d2,a1 

    ; main plotting logic
    move.l  -4(a6),d0
    move.l  a0,a2    

vertical_line_loop:
    or.l    d0,(a2)  
    cmp.l   a2,a1           
    beq.s   plot_vertical_line_end
    adda.w  #80,a2   
    bra      vertical_line_loop

plot_vertical_line_end:
    movem.l (sp)+,d0-d4/a0-a2
    unlk    a6
    rts
;-------------------------------------------------------------------------------------------------
;------------------------------ROUTINE TO PLOT A LINE BETWEEN ANY TWO GIVEN POINT-----------------
_plot_line:
    link    a6,#-12 
    movem.l d3-d7/a1,-(sp) 

set_regs:
    move.l  8(a6),a1  
    move.w  12(a6),d3 
    move.w  14(a6),d4 
    move.w  16(a6),d5 
    move.w  18(a6),d6 

calculate_difference:
    cmp.w   d4,d6 
    bhi     dx_true
    move.w  d4,d7 
    sub.w   d6,d7 
    move.w  d7,-12(a6)
    bra     dy_calc
dx_true:
    move.w  d6,d7     
    sub.w   d4,d7     
    move.w  d7,-12(a6)
dy_calc:
    cmp.w   d3,d5
    bhi     dy_true
    move.w  d3,d7 
    sub.w   d5,d7 
    neg.w   d7
    move.w  d7,-10(a6) 
    bra     step_direction
dy_true:
    move.w  d5,d7 
    sub.w   d3,d7 
    neg.w   d7    
    move.w  d7,-10(a6)

step_direction:
    moveq   #1,d7
    move.w  d7,-8(a6)
    cmp.w   d4,d6
    bhi     sx_done
    moveq   #-1,d7
    move.w  d7,-8(a6)
sx_done:
    moveq   #1,d7
    move.w  d7,-6(a6)
    cmp.w   d3,d5
    bhi     err_val
    moveq   #-1,d7
    move.w  d7,-6(a6)

err_val:
    move.w    -12(a6),d7
    add.w     -10(a6),d7
    move.w    d7,-4(a6)

plotting_loop:
    move.w  d4,-(sp)
    move.w  d3,-(sp)
    move.l  a1,-(sp)
    jsr     _plot_pixel
    adda.l  #8,sp

;   if (start_col == end_col && start_row == end_row)
    cmp.w   d4,d6
    bne     not_equal
    cmp.w   d3,d5
    beq     plot_line_done 

not_equal:

    move.w  -4(a6),d7
    add.w   d7,d7
    move.w  d7,-2(a6)
first_if:
;   if (err2 >= dy) { err += dy; start_col += sx; }
    move.w  -2(a6),d7
    move.w  -10(a6),d0  
    cmp.w   d7,d0      
    bgt     second_if
    add.w   d0,-4(a6)  
    move.w  -8(a6),d7  
    add.w   d7,d4 
second_if:
;   if (err2 <= dx) { err += dx; start_row += sy; }
    move.w  -2(a6),d7
    move.w  -12(a6),d0 
    cmp.w   d7,d0 
    blt     plotting_loop
    add.w   d0,-4(a6) 
    move.w  -6(a6),d7
    add.w   d7,d3 
    bra     plotting_loop

plot_line_done:
    movem.l (sp)+,d3-d7/a1
    unlk    a6
    rts
;-------------------------------------------------------------------------------------------------
;--------------------ROUTINE TO PLOT A RECTANGLE--------------------------------------------------
_plot_rectangle:
    link    a6,#0
    movem.l d0-d1,-(sp)

    move.w  18(a6),d1  
    tst.w   d1          ; check if width == 0
    ble     plot_rectangle_done
    move.w  16(a6),d0  
    tst.w   d0          ; check if length == 0
    ble     plot_rectangle_done

    add.w   12(a6),d0  
    subq    #1,d0 

    
    add.w   14(a6),d1
    subq    #1,d1

;   /* top line */
    move.w  18(a6),-(sp)
    move.w  14(a6),-(sp)
    move.w  12(a6),-(sp)
    move.l  8(a6),-(sp)
    jsr     _plot_horizontal_line
    adda.l  #10,sp

;   /* bottom line */
    move.w  18(a6),-(sp)
    move.w  14(a6),-(sp)
    move.w  d0,-(sp)
    move.l  8(a6),-(sp)
    jsr     _plot_horizontal_line
    adda.l  #10,sp          

;   /* left line */
    move.w  16(a6),-(sp) 
    move.w  14(a6),-(sp)
    move.w  12(a6),-(sp)
    move.l  8(a6),-(sp) 
    jsr     _plot_vertical_line
    adda.l  #10,sp          

;   /* right line */
    move.w  16(a6),-(sp)
    move.w  d1,-(sp) 
    move.w  12(a6),-(sp)
    move.l  8(a6),-(sp)
    jsr     _plot_vertical_line
    adda.l  #10,sp          

plot_rectangle_done:
    movem.l (sp)+,d0-d1
    unlk    a6
    rts
;-------------------------------------------------------------------------------------------------
;--------------------ROUTINE TO PLOT A SQUARE-----------------------------------------------------
_plot_square:
    link    a6,#0

    move.w  16(a6),d0 
    ble     plot_square_done

    move.w  d0,-(sp)
    move.w  d0,-(sp)
    move.w  14(a6),-(sp)
    move.w  12(a6),-(sp)
    move.l  8(a6),-(sp) 
    
    jsr     _plot_rectangle 
    adda.l  #12,sp          
    
plot_square_done:
    unlk    a6
    rts
;-------------------------------------------------------------------------------------------------
;-------------------------ROUTINE TO PLOT A TRIANGLE----------------------------------------------
_plot_triangle:
    link    a6,#0
    movem.l d0-d4/a0,-(sp)

;    if (trianglebase == 0 || height == 0) return;
    move.w  18(a6),d0
    ble     plot_triangle_end
    move.w  16(a6),d1 
    ble     plot_triangle_end 

    move.w  20(a6),d2   ; get direction
    cmpi.w  #0,d2
    beq     plot_top_left_triangle
    cmpi.w  #1,d2
    beq     plot_top_right_triangle
    cmpi.w  #2,d2
    beq     plot_bottom_left_triangle
    cmpi.w  #3,d2
    beq     plot_bottom_right_triangle
    bra     plot_triangle_end

plot_top_left_triangle:

    move.w  16(a6),-(sp) 
    move.w  14(a6),-(sp)
    move.w  12(a6),-(sp)
    move.l  8(a6),-(sp) 
    jsr     _plot_horizontal_line
    adda.l  #10,sp

    move.w  18(a6),-(sp) 
    move.w  14(a6),-(sp)
    move.w  12(a6),-(sp)
    move.l  8(a6),-(sp) 
    jsr     _plot_vertical_line
    adda.l  #10,sp

    move.w  14(a6),d1 
    move.w  16(a6),d0 
    add.w   d1,d0
    subq.w  #1,d0     
    move.w  d0,-(sp)  
    move.w  12(a6),-(sp)
    move.w  14(a6),-(sp)
    move.w  12(a6),d0   
    add.w   18(a6),d0   
    subq.w  #1,d0       
    move.w  d0,-(sp)    
    move.l  8(a6),-(sp) 
    jsr     _plot_line
    adda.l  #12,sp
    bra     plot_triangle_end

plot_top_right_triangle:
    move.w  16(a6),-(sp) 
    move.w  14(a6),d0    
    sub.w   16(a6),d0    
    addq.w  #1,d0        
    move.w  d0,-(sp)     
    move.w  12(a6),-(sp) 
    move.l  8(a6),-(sp) 
    
    jsr     _plot_horizontal_line
    adda.l  #10,sp

    move.w  18(a6),-(sp)
    move.w  14(a6),-(sp)
    move.w  12(a6),-(sp)
    move.l  8(a6),-(sp) 
    jsr     _plot_vertical_line
    adda.l  #10,sp

    move.w  14(a6),d0  
    sub.w   16(a6),d0  
    addq.w  #1,d0      
    move.w  d0,-(sp)   
    move.w  12(a6),-(sp)
    move.w  14(a6),-(sp)
    move.w  12(a6),d0   
    add.w   18(a6),d0   
    subq.w  #1,d0       
    move.w  d0,-(sp)    
    move.l  8(a6),-(sp) 
    jsr     _plot_line
    adda.l  #12,sp
    bra     plot_triangle_end

plot_bottom_left_triangle:
    move.w  16(a6),-(sp)
    move.w  14(a6),-(sp)
    move.w  12(a6),-(sp)
    move.l  8(a6),-(sp)
    jsr     _plot_horizontal_line
    adda.l  #10,sp

    move.w  18(a6),-(sp)
    move.w  14(a6),-(sp)
    move.w  12(a6),d0   
    sub.w   18(a6),d0   
    addq.w  #1,d0       
    move.w  d0,-(sp)    
    move.l  8(a6),-(sp) 
    jsr     _plot_vertical_line
    adda.l  #10,sp

    move.w  14(a6),d0 
    add.w   16(a6),d0 
    subq.w  #1,d0     
    move.w  d0,-(sp)  
    move.w  12(a6),-(sp)
    move.w  14(a6),-(sp)
    move.w  12(a6),d0   
    sub.w   18(a6),d0   
    addq.w  #1,d0       
    move.w  d0,-(sp)    
    move.l  8(a6),-(sp) 
    jsr     _plot_line
    adda.l  #12,sp
    bra     plot_triangle_end

plot_bottom_right_triangle:
    move.w  16(a6),-(sp)
    move.w  14(a6),d0
    sub.w   16(a6),d0
    addq.w  #1,d0
    move.w  d0,-(sp)
    move.w  12(a6),-(sp)
    move.l  8(a6),-(sp)
    jsr     _plot_horizontal_line
    adda.l  #10,sp

    move.w  18(a6),-(sp)
    move.w  14(a6),-(sp)
    move.w  12(a6),d0
    sub.w   18(a6),d0
    addq.w  #1,d0
    move.w  d0,-(sp)
    move.l  8(a6),-(sp)
    jsr     _plot_vertical_line
    adda.l  #10,sp

    move.w  14(a6),d0
    sub.w   16(a6),d0
    addq.w  #1,d0
    move.w  d0,-(sp)      
    move.w  12(a6),-(sp)  
    move.w  14(a6),-(sp)  
    move.w  12(a6),d0
    sub.w   18(a6),d0
    addq.w  #1,d0
    move.w  d0,-(sp)   
    move.l  8(a6),-(sp)
    jsr     _plot_line
    adda.l  #12,sp

plot_triangle_end:
    movem.l (sp)+,d0-d4/a0
    unlk    a6
    rts
;-------------------------------------------------------------------------------------------------
;-------------------------ROUTINE TO PLOT A BITMAP 8 BITS WIDE------------------------------------
_plot_8_bitmap:
    link    a6,#-4 
    movem.l d0-d7/a0-a1,-(sp)
    
    ; if (height == 0) return;
    move.w  16(a6),d2  
    ble     plot_8_bitmap_done
    
    ; if (row + height > 400) height = 400 - row; 
    move.w  12(a6),d1   
    move.w  d1,d0
    add.w   d2,d0
    cmpi.w  #400,d0
    ble     bitmap_8_size_done
    move.w  #400,d2
    sub.w   d1,d2 

bitmap_8_size_done:
    move.w  d2,-4(a6)   

    ; shift = (col & 7); 
    move.w  14(a6),d3     
    andi.w  #7,d3         
    move.w  d3,-2(a6)  

    ; start_point = base + (row * 80) + (col >> 3);
    lsl.w   #4,d1    
    move.w  d1,d0
    lsl.w   #2,d1    
    add.w   d0,d1   
    
    move.w  14(a6),d0  
    lsr.w   #3,d0 
    add.w   d0,d1               
    
    move.l  8(a6),a0    
    adda.w  d1,a0       
    
    move.l  18(a6),a1   
    
    move.w  -4(a6),d2  
    subq.w  #1,d2               ; for dbra
    
    move.w  -2(a6),d6  
    move.w  #8,d7
    sub.w   d6,d7 

plot_bitmap_8_loop:
    moveq   #0,d0
    move.b  (a1)+,d0  
    move.w  d0,d1     
    
    lsr.w   d6,d0     
    eor.b    d0,(a0)   
    
    ; if (shift > 0 && ((col >> 3) < (BYTES_PER_ROW - 1)))
    tst.w   d6
    beq     bitmap_8_next_row
    
    move.w  14(a6),d3           
    lsr.w   #3,d3
    cmpi.w  #79,d3
    bge     bitmap_8_next_row
    
    lsl.w   d7,d1
    eor.b    d1,1(a0)

bitmap_8_next_row:
    adda.w  #80,a0 
    dbra    d2,plot_bitmap_8_loop

plot_8_bitmap_done:
    movem.l (sp)+,d0-d7/a0-a1
    unlk    a6
    rts
;-------------------------------------------------------------------------------------------------
;-------------------------ROUTINE TO PLOT A BITMAP 16 BITS WIDE-----------------------------------
_plot_16_bitmap:
    link    a6,#-4            
    movem.l d0-d7/a0-a2,-(sp)

    ; if (height == 0) return;
    move.w  16(a6),d2
    ble     plot_16_bitmap_done

    ; if (row + height > 400) height = 400 - row;
    move.w  12(a6),d1
    move.w  d1,d0
    add.w   d2,d0 
    cmpi.w  #400,d0
    ble     plot_16_size_done
    move.w  #400,d2
    sub.w   d1,d2   

plot_16_size_done:
    move.w  d2,d7    
    subq.w  #1,d7    
    
    ; shift = (col & 15);
    move.w  14(a6),d3    
    andi.w  #15,d3
    move.w  d3,-2(a6) 

    ; start_point = base + (row * 40) + (col >> 4);
    move.w  d1,d0 
    lsl.w   #6,d1 
    lsl.w   #4,d0 
    add.w   d0,d1 

    move.w  14(a6),d0 
    lsr.w   #4,d0 
    lsl.w   #1,d0 
    add.w   d0,d1 

    move.l  8(a6),a0 
    adda.w  d1,a0    

    move.l  18(a6),a1 
    
    move.w  -2(a6),d6 
    move.w  #16,d5
    sub.w   d6,d5  

plot_16_loop:
    ; *current |= (bitmap[i] >> shift);
    move.w  (a1)+,d0   
    move.w  d0,d1               
    
    lsr.w   d6,d0
    eor.w    d0,(a0)

    ; if (shift > 0 && ((col >> 4) < (WORDS_PER_ROW - 1)))
    tst.w   d6
    beq     plot_16_next_row
    
    move.w  14(a6),d3
    lsr.w   #4,d3
    cmpi.w  #39,d3
    bge     plot_16_next_row

    ; *(current + 1) |= (bitmap[i] << (16 - shift));
    lsl.w   d5,d1 
    eor.w    d1,2(a0) 

plot_16_next_row:
    adda.w  #80,a0 
    dbra    d7,plot_16_loop

plot_16_bitmap_done:
    movem.l (sp)+,d0-d7/a0-a2
    unlk    a6
    rts
;-------------------------------------------------------------------------------------------------
;-------------------------ROUTINE TO PLOT A BITMAP 32 BITS WIDE-----------------------------------
_plot_32_bitmap:
    link    a6,#-4    
    movem.l d0-d7/a0-a2,-(sp)

    ; if (height == 0) return;
    move.w  16(a6),d2 
    ble     plot_32_bitmap_done

    ; if (row + height > 400) height = 400 - row;
    move.w  12(a6),d1  
    move.w  d1,d0
    add.w   d2,d0      
    cmpi.w  #400,d0
    ble     plot_32_size_done
    move.w  #400,d2
    sub.w   d1,d2 

plot_32_size_done:
    move.w  d2,d7 
    subq.w  #1,d7 
    
    ; shift = (col & 31);
    move.w  14(a6),d3 
    andi.w  #31,d3
    move.w  d3,-2(a6) 

    ; start_point = base + (row * 20LONGS) + (col >> 5);
    move.w  d1,d0
    lsl.w   #6,d1  
    lsl.w   #4,d0  
    add.w   d0,d1

    move.w  14(a6),d0 
    lsr.w   #5,d0 
    lsl.w   #2,d0 
    add.w   d0,d1 

    move.l  8(a6),a0 
    adda.w  d1,a0    

    move.l  18(a6),a1
    
    move.w  -2(a6),d6
    move.w  #32,d5
    sub.w   d6,d5 

plot_32_loop:
    ; *current |= (bitmap[i] >> shift);
    move.l  (a1)+,d0
    move.l  d0,d1               
    
    lsr.l   d6,d0
    eor.l    d0,(a0) 

    ; if (shift > 0 && ((col >> 4) < (WORDS_PER_ROW - 1)))
    tst.w   d6
    beq     plot_32_next_row
    
    move.w  14(a6),d3
    lsr.w   #5,d3
    cmpi.w  #19,d3
    bge     plot_32_next_row

    ; *(current + 1) |= (bitmap[i] << (32 - shift));
    lsl.l   d5,d1     
    eor.l    d1,4(a0) 

plot_32_next_row:
    adda.w  #80,a0   
    dbra    d7,plot_32_loop

plot_32_bitmap_done:
    movem.l (sp)+,d0-d7/a0-a2
    unlk    a6
    rts
;-------------------------------------------------------------------------------------------------
;------------------------------ROUTINE TO PLOT A CHARACTER----------------------------------------
_plot_character:
    link    a6,#0
    movem.l d0-d7/a0-a1,-(sp)

    ; IS_PRINTABLE(i) = (i >= ' ' && i <= '~')
    move.w  16(a6),d0 
    andi.w  #$FF,d0   
    cmpi.b  #32,d0   
    blt     plot_char_done  
    cmpi.b  #126,d0 
    bgt     plot_char_done

    ; GLYPH_START(i) (font + (((i) - ' ') << 3))
    sub.w   #32,d0 
    lsl.w   #3,d0 
    xref    _font 
    lea     _font,a1
    adda.w  d0,a1

    ; start_point = base + (row * 80) + (col >> 3)
    move.w  12(a6),d1 
    move.w  d1,d2
    lsl.w   #6,d1  
    lsl.w   #4,d2  
    add.w   d2,d1  

    move.w  14(a6),d0
    move.w  d0,d3  
    lsr.w   #3,d0  
    add.w   d0,d1  

    move.l  8(a6),a0
    adda.w  d1,a0   

    ; shifts
    andi.w  #7,d3   
    move.w  #8,d4
    sub.w   d3,d4   

    moveq   #7,d5               ; for dbra

plot_char_loop:
    moveq   #0,d0
    move.b  (a1)+,d0 
    
    move.w  d0,d1  
    lsr.w   d3,d0  
    or.b    d0,(a0) 

    ; if (shift > 0) 
    tst.w   d3
    beq     plot_char_next_row

    lsl.w   d4,d1   
    or.b    d1,1(a0) 

plot_char_next_row:
    adda.w  #80,a0   
    dbra    d5,plot_char_loop

plot_char_done:
    movem.l (sp)+,d0-d7/a0-a1
    unlk    a6
    rts
;-------------------------------------------------------------------------------------------------
;------------------------------ROUTINE TO PLOT A STRING-------------------------------------------
_plot_string:
    link    a6,#0
    movem.l d0-d4/a0-a2,-(sp) 

    move.l  8(a6),a0 
    move.w  12(a6),d2 
    move.w  14(a6),d3 
    move.l  16(a6),a2 

plot_string_loop:
    clr.l   d4               
    move.b  (a2)+,d4  
    cmpi.b  #0,d4     
    beq     plot_string_done    

    move.w  d4,-(sp) 
    move.w  d3,-(sp) 
    move.w  d2,-(sp) 
    move.l  a0,-(sp) 
    
    jsr     _plot_character     
    adda.l  #10,sp   

    addq.w  #8,d3 
    bra     plot_string_loop    

plot_string_done:
    movem.l (sp)+,d0-d4/a0-a2
    unlk    a6
    rts
;-------------------------------------------------------------------------------------------------
;-------------------------------ROUTINE TO SET SCREEN---------------------------------------------
_set_video_base:
    link    a6,#-4            ; reserve 4 bytes for old_ssp

        ; old_ssp = Super(0)
        clr.l   -(sp)
        move.w  #32,-(sp)
        trap    #1
        addq.l  #6,sp
        move.l  d0,-4(a6)

        ; load addr argument
        move.l  8(a6),d0
        lsr.l   #8,d0             ; d0 low word becomes [high][mid]

        lea     $FFFF8201,a0

        ; write middle byte to $FFFF8203
        move.b  d0,2(a0)

        ; shift high byte into low byte position
        lsr.w   #8,d0

        ; write high byte to $FFFF8201
        move.b  d0,(a0)

        ; Super(old_ssp)
        move.l  -4(a6),-(sp)
        move.w  #32,-(sp)
        trap    #1
        addq.l  #6,sp

        unlk    a6
        rts

;-------------------------------------------------------------------------------------------------
;-------------------------ROUTINE TO EXIT THE PROGRAM---------------------------------------------
exit:   
            clr.w   -(sp)
            trap    #1
