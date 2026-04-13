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

/* the assembly function */
extern void ikbd_custom();

/* 
 * handles the ISR. recieves an input and adds to the tail.
*/
void ikbd_isr();

/*
* The fucntion that accesses the buffer and pops of values from the queue to proces
 * the input.
*/
char get_kbd_input();


#endif