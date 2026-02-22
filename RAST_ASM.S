;=====================CONSTANTS=====================================================================

SCREEN_WIDTH	EQU	640	; #define SCREEN_WIDTH
SCREEN_HEIGHT	EQU	400 ; #define SCREEN_HEIGHT

MAX_COL  EQU  (SCREEN_WIDTH-1)
MAX_ROW  EQU  (SCREEN_HEIGHT-1)

BYTES_PER_ROW	EQU (SCREEN_WIDTH >> 3)	; #define BYTES_PER_ROW (SCREEN_WIDTH >> 3)
WORDS_PER_ROW	EQU (BYTES_PER_ROW >> 1)	; #define WORDS_PER_ROW (BYTES_PER_ROW >> 1)
LONGS_PER_ROW	EQU (BYTES_PER_ROW >> 2) ; #define LONGS_PER_ROW (BYTES_PER_ROW >> 2)

; the total pixels to be considered
PIXEL_COUNT	EQU	(SCREEN_WIDTH * SCREEN_HEIGHT)	; #define PIXEL_COUNT (SCREEN_WIDTH * SCREEN_HEIGHT) 

; masks
HOR_BYTE_MASK	EQU	#$FF	; #define HOR_BYTE_MASK ((UINT8)0xFF)
HOR_WORD_MASK	EQU	#$FFFF	; #define HOR_WORD_MASK ((UINT16)0xFFFF)
HOR_LONG_MASK	EQU	#$FFFFFFFF	; #define HOR_LONG_MASK ((UINT32)0xFFFFFFFF)

VER_BYTE_MASK	EQU #$80	; #define VER_BYTE_MASK ((UINT8)0x80)
VER_WORD_MASK	EQU #$8000	; #define VER_WORD_MASK ((UINT16)0x8000)
VER_LONG_MASK	EQU #$80000000	; #define VER_LONG_MASK ((UINT32)0x80000000)

; for "boolean operations", using negative values to prevent mixups
TRUE	EQU	-1	
FALSE	EQU	-2	

;=========================FUNCTIONS AND HELPER FUNCTIONS===========================================

;--------------CHECK FOR PIXEL COORDINATES BEING WITHIN BOUNDS-------------------------------------
;  PURPOSE: Checks if a coordinate is within the 640x400 screen limits.
;  INPUT: x-coordinate (column), y-coordinate (row)
;  RETURN: -1 if in bounds, -2 if out of bounds.
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
px_in_bounds_end
	move.l	(sp)+,d0	; return orginal values to the register(s)
	unlk	a6
	
	rts
;-------------------------------------------------------------------------------------------------
;----------------------ROUTINE FOR CLEARING THE SCREEN--------------------------------------------
; PURPOSE: Clears the entire screen.
; INPUT: Address(UINT32*): to the start of the screen
; OUTPUT: None

;void clear_screen(UINT32 *base);
clear_screen:
	link	a6,#0	; no local variables
	movem.l	d0/a0,-(sp)

	move.l	8(a6),a0 ; load address of base
	
	move.l	#PIXEL_COUNT,d0 ; load pixel count
	lsr.l	#5,d0	; get the number of longwords on the screen
	subq.l	#1,d0

clear_screen_loop:
	clr.l	(a0)+	; set the entire longword to zero
	dbra	d0,clear_screen_loop

	movem.l	(sp)+,d0/a0
	unlk	a6
	
	rts

;-------------------------------------------------------------------------------------------------
;-----------------ROUTINE FOR CLEARING A SPECIFIED RECTANGULAR REGION-----------------------------

;-------------------------------------------------------------------------------------------------
;---------------ROUTINE FOR PLOTTING A SINGLE PXIEL ONTO SPECIFIED COORDINATES--------------------
; void plot_pixel(UINT8 *base, UINT16 row, UINT16 col);
; PURPOSE: Plots a single pixel onto the screen
; INPUT: Address of the starting byte of the board
;-------------------------------------------------------------------------------------------------
;-------------------------------------------------------------------------------------------------
;=========================GLOBAL VARIABLES========================================================