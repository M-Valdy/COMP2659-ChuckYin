/* @author Gaurik */

#include "ikbd.h"
#include "cisr.h"

volatile UINT8 * const IKBD_control = 0xfffc00;
volatile const UINT8 * const IKBD_status = 0xfffc00;
volatile const SCANCODE * const IKBD_RDR = 0xfffc02;

volatile SCANCODE head = 0;
volatile SCANCODE tail = 0;

volatile SCANCODE input_buffer[BUFFER_SIZE];

void ikbd_isr() {
    /* decided to let go of the loop as in the lab to prevent unneccasry game pauses */
    if (*IKBD_status & RDR_FULL) {
        input_buffer[tail++] = *IKBD_RDR; /* add to the end of the queque */
    }
}

char get_kbd_input() {
    SCANCODE scancode;
    char kb_in = 0;

    if (head != tail) {
        scancode = input_buffer[head++]; /* read from the start of the queue and move on */

        /* ignoring break codes because this game only cares about a singular input on key press
        so key realease is to be ignored to prevent unintended double movement */
        if (!(scancode & BREAK_CODE)) {
            if(scancode == 0x11) kb_in = 'W';
            else if (scancode == 0x1E) kb_in = 'A';
            else if (scancode == 0x1F) kb_in = 'S';
            else if (scancode == 0x20) kb_in = 'D';
            else if (scancode == 0x19) kb_in = 'P';
            else if (scancode == 0x10) kb_in = 'Q';
            else if (scancode == 0x18) kb_in = 'O';
        }
    }
    return kb_in;
}