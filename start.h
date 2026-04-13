/* @author Gaurik */
#ifndef START_H
#define START_H

#include "renderer.h"
#include "model.h"
#include "raster.h"

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

void plot_title(UINT32 *base);
void prompt_sq(UINT32 *base);
void splashscreen_chars(UINT32 *base);
void make_quitButton(UINT32 *base);
void make_playButton(UINT32 *base);
int make_splashscreen(UINT32 *base);


#endif
