/* @author Gaurik and Meagan */
#ifndef START_H
#define START_H

#include "renderer.h"
#include "model.h"
#include "raster.h"
#include "ikbd.h"
#include "cisr.h" 

extern const unsigned int the_c[16];
extern const unsigned int the_h[16];
extern const unsigned int the_u[16];
extern const unsigned int the_k[16];
extern const unsigned int the_colon[16];
extern const unsigned int the_tee[16];
extern const unsigned int the_e[16];
extern const unsigned int the_g[16];
extern const unsigned int the_a[16];
extern const unsigned int the_m[16];
extern const unsigned int pointer_bitmap[16];

/*@author Gaurik
    This function takes in the base address of the screen and 
    plots the title "Chuck The Game" on the screen using the 16x16 bitmaps 
    defined above. It also uses a global variable hor_start to align the title 
    and other elements on the screen.
*/
void plot_title(UINT32 *base);


/* @author Gaurik
    This function takes in the base address of the screen and 
    plots the prompt "(Enter P to play or Q to quit.)" on the screen. */
void prompt_sq(UINT32 *base);


/* @author Gaurik
    This function takes in the base address of the screen and 
    plots a rectangle for the button and the texts inside the rectangle.
*/
void splashscreen_chars(UINT32 *base);

/* @author Gaurik
    This function takes in the base address of the screen and 
    plots a rectangle for the quit button and the text "Quit" inside the rectangle.
*/
void make_quitButton(UINT32 *base);

/* @author Gaurik
    This function takes in the base address of the screen and 
    plots a rectangle for the quit button and the text "Quit" inside the rectangle.
*/
void make_playButton(UINT32 *base);

/* @author Meagan
    This function takes in the base address of the screen and 
    plots the mouse cursor on the screen. Taking into account the position of the cursor. 
*/
void plot_mouse(UINT32 *base, UINT16 x, UINT16 y);

/* @author Gaurik and Meagan
    This function takes in the base address of the screen and 
    displays the splash screen with the title, prompt, and buttons. It allows the user
    to interact with the buttons and press "Quit" to quit the game or "Play" to continue. 
    It still allows you to press "Q" to quit and "P" to play as well. 
    It returns 0 if the user wants to play and 1 if the user wants to quit.
*/
int make_splashscreen(UINT32 *base);


#endif
