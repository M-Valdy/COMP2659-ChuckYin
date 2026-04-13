/* @author Gaurik */

#include "ikbd.h"
#include "cisr.h"

volatile UINT8 * const IKBD_control = 0xfffc00;
volatile const UINT8 * const IKBD_status = 0xfffc00;
volatile const SCANCODE * const IKBD_RDR = 0xfffc02;
volatile UINT8 * const MFP_ISRB = 0xFFFA11;

volatile int mouse_x = 0;
volatile int mouse_y = 0;
volatile SCANCODE mouse_buttons = 0;

volatile int mouse_packet_state = 0;   /* 0=expect header, 1=expect dx, 2=expect dy */
volatile UINT8 mouse_header = 0;
volatile int mouse_dx = 0;
volatile int mouse_dy = 0;


volatile SCANCODE head = 0;
volatile SCANCODE tail = 0;

volatile SCANCODE input_buffer[BUFFER_SIZE];

int get_mouse_x() {
    return mouse_x;
}

int get_mouse_y() {
    return mouse_y;
}

SCANCODE get_mouse_buttons() {
    return mouse_buttons;
}

/* handles one byte that is known to belong to a mouse packet */
void mouse_input(UINT8 byte) {
    if (mouse_packet_state == 0) {
        /* only accept real mouse headers: 111110LR */
        if ((byte & 0xFC) == 0xF8) {
            mouse_header = byte;
            mouse_packet_state = 1;
        }
    }
    else if (mouse_packet_state == 1) {
        mouse_dx = (int)(char)byte;   /* signed widen */
        mouse_packet_state = 2;
    }
    else if (mouse_packet_state == 2) {
        mouse_dy = (int)(char)byte;   /* signed widen */

        /* header format is 111110LR */
        mouse_buttons = mouse_header & 0x03;

        mouse_x += mouse_dx;
        mouse_y += mouse_dy;   /* change to -= if Y is inverted */

        /* clamp to screen bounds */
        if (mouse_x < 0)   mouse_x = 0;
        if (mouse_x > 319) mouse_x = 319;
        if (mouse_y < 0)   mouse_y = 0;
        if (mouse_y > 199) mouse_y = 199;

        mouse_packet_state = 0;
    }
}


void ikbd_isr(void) {
    UINT8 byte;

    if (*IKBD_status & RDR_FULL) {
        byte = *IKBD_RDR;

        /* if already in a mouse packet, or this byte starts one, treat as mouse */
        if (mouse_packet_state != 0 || ((byte & 0xFC) == 0xF8)) {
            mouse_input(byte);
        } else {
            enqueue_kbd_byte(byte);
        }
    }

    /* also remember: your full ISR likely still needs MFP end-of-interrupt handling */
    *MFP_ISRB &= 0xBF; /* acknowledge the interrupt in the MFP */

}


char get_kbd_input() {
    SCANCODE scancode;
    char kb_in = 0;

    if (head != tail) {
        scancode = input_buffer[head]; /* read from the start of the queue and move on */
        head = (head + 1) % BUFFER_SIZE;

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