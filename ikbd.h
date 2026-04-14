/* @author Gaurik */
#ifndef IKBD_H
#define IKBD_H

#include <osbind.h>
#include <stdio.h>
#include "types.h"
#include "cisr.h"

#define RX_ENABLED  0x7f
#define RX_DISABLED 0x80

#define RDR_FULL 0x01 /* bit 0 */
#define BREAK_CODE 0x80 /* bit 7 */
#define BUFFER_SIZE 256 /* 2^8, since head and tail are 8bit values, only go 0-255 circling around 0 as they unsigned */

typedef UINT8 SCANCODE;

extern volatile SCANCODE head; /* the front of the circular queue values are popped off here */
extern volatile SCANCODE tail; /* the back of the cirxular queque, values are pushed onto here */

extern volatile SCANCODE input_buffer[BUFFER_SIZE]; /* an array to serve as the circular input */
/* ciccular as its unsigned 8 bit vlaues this going over 255 overflows to 0 */

/* stuff from the IKBD lab */
extern volatile UINT8 * const IKBD_control;
extern volatile const UINT8 * const IKBD_status;
extern volatile const SCANCODE * const IKBD_RDR;

/* mouse variables */
extern volatile int mouse_x;
extern volatile int mouse_y;
extern volatile SCANCODE mouse_buttons;

/* mouse packet variables */
extern volatile int mouse_packet_state;   /* 0=expect header, 1=expect dx, 2=expect dy */
extern volatile UINT8 mouse_header;
extern volatile int mouse_dx;
extern volatile int mouse_dy;

/* the assembly function */
extern void ikbd_custom();

/* @author Meagan, Gaurik
 Enqueues a keyboard byte into the circular buffer. Checks if the buffer is full before adding.
 If the buffer is full, the byte is discarded.
*/
static void enqueue_kbd_byte(SCANCODE byte) {
    SCANCODE next_tail = (tail + 1) % BUFFER_SIZE;

    if (next_tail != head) {
        input_buffer[tail] = byte;
        tail = next_tail;
    }
}

/* @author Meagan
    For gettting mouse input for convenience to be used in the splashscreen loop.
    Keeps track of whether the mouse is moving and whether the buttons are being pressed.
    get_mouse_buttons() looks at both the left and the right keys so the game allows for both
    to be pressed.  
*/
extern int get_mouse_x();
extern int get_mouse_y();
extern SCANCODE get_mouse_buttons();

/* @author Meagan.
 * Processes a mouse input byte.
*/
void mouse_input(UINT8 byte);

/* @author Meagan, Gaurik
    handles the ISR. recieves an input and adds to the tail. This function is in charge
    of knowing whether the user is doing keyboard input or mouse input. 
*/
void ikbd_isr();

/*  @author Gaurik
* The fucntion that accesses the buffer and pops of values from the queue to process the input.
  This function is exclusively in charge of 
*/
char get_kbd_input();


#endif