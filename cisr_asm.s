    xdef _vertical_blank_custom
    xref _timer_custom

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