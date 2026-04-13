; author @gaurik   
   
    xdef _vertical_blank_custom
    xref _timer_custom
    xref _ikbd_isr
    xdef _ikbd_custom

; this had to be in Assembly as the registers d0-d2 and a0-a2 maybe modified and also 
; "RTE" statement can't be made in C by the compiler.
; a routine which saves the registers so the game state and CPU can resume exactly where
; the interrupt stopped and calls the "_timer_custom" routine which may modify those and restores the original
; states and data
; and RTE is neccessary for lowering the proirity so other instructions can processed and restoring SR and PC.
_vertical_blank_custom:
    movem.l d0-d2/a0-a2,-(sp)
    jsr     _timer_custom
    movem.l (sp)+,d0-d2/a0-a2
    rte

; there was no mention of scrap regiters so only savig the ones that were mentioed for the previous function
; calls the "_ikbd_isr" fucntion to keep track of the states and returns after clearing in the 
; in-service bit
_ikbd_custom:
    movem.l d0-d2/a0-a2,-(sp)   
    jsr _ikbd_isr
    move.l  #$FFFA11,a0 ; load adrress of MFP chip into a0
    move.b  (a0),d0            ; move the byte for manipulation
    and.b   #$BF,d0            ; clear bit 6
    move.b  d0,(a0)            ; write the cleared bit back to address

    movem.l (sp)+,d0-d2/a0-a2
    rte