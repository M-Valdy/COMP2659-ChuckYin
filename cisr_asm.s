; @author Gaurik
    xdef _vbl_custom
    xref _isr_timer

_vbl_custom:
        movem.l d0-d2/a0-a2,-(sp)
        jsr     _isr_timer
        movem.l (sp)+,d0-d2/a0-a2
        rte
