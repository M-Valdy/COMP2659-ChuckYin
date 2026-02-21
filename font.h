#ifndef FONT_H
#define FONT_H

#include "types.h"

/*
    This file defines the constants, types, and function prototypes related to the font used in the game.
    It also includes the declaration of the font bitmap, which is an 8x8 pixel representation 
    of the characters used in the game. Along with definitions of what characters are considered printable 
    and how to calculate the starting address of a character's glyph in the font bitmap.
*/

extern const UINT8 font[];     /* 8x8 system font */

#define FONT_HEIGHT 8
#define CHAR_BEL    7
#define CHAR_TAB    9
#define CHAR_LF    10
#define CHAR_VT    11
#define CHAR_FF    12
#define CHAR_CR    13
#define CHAR_DEL  127

#define IS_PRINTABLE(i) ((i) >= ' ' && (i) <= '~')
#define GLYPH_START(i) (font + (((i) - ' ') << 3))
/* needed help from the internet and google gemini to under the header
 * file definitions */
#endif
