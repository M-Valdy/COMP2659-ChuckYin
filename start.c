/* @author Gaurik */

#include <osbind.h>
#include "start.h"

/* 16x16 Bitmap for 'C' */
const unsigned int the_c[16] = {
    0x07E0, 0x1FF0, 0x3838, 0x701C, 
    0x6000, 0xE000, 0xE000, 0xE000, 
    0xE000, 0xE000, 0x6000, 0x701C, 
    0x3838, 0x1FF0, 0x07E0, 0x0000
};

/* 16x16 Bitmap for 'H' */
const unsigned int the_h[16] = {
    0xE007, 0xE007, 0xE007, 0xE007, 
    0xE007, 0xE007, 0xFFFF, 0xFFFF, 
    0xFFFF, 0xE007, 0xE007, 0xE007, 
    0xE007, 0xE007, 0xE007, 0x0000
};

/* 16x16 Bitmap for 'U' */
const unsigned int the_u[16] = {
    0xE007, 0xE007, 0xE007, 0xE007, 
    0xE007, 0xE007, 0xE007, 0xE007, 
    0xE007, 0xE007, 0xE007, 0x700E, 
    0x381C, 0x1FF8, 0x07F0, 0x0000
};

/* 16x16 Bitmap for 'K' */
const unsigned int the_k[16] = {
    0xE00F, 0xE01E, 0xE03C, 0xE078, 
    0xE0F0, 0xE1E0, 0xFE00, 0xFF00, 
    0xFE00, 0xE1E0, 0xE0F0, 0xE078, 
    0xE03C, 0xE01E, 0xE00F, 0x0000
};

/* 16x16 Bitmap for ':' */
const unsigned int the_colon[16] = {
    0x0000, 0x0000, 0x0C00, 0x0C00, 
    0x0C00, 0x0000, 0x0000, 0x0000, 
    0x0000, 0x0C00, 0x0C00, 0x0C00, 
    0x0000, 0x0000, 0x0000, 0x0000
};

/* 16x16 Bitmap for 'T' */
const unsigned int the_tee[16] = {
    0xFFFF, 0xFFFF, 0xFFFF, 0x1800, 
    0x1800, 0x1800, 0x1800, 0x1800, 
    0x1800, 0x1800, 0x1800, 0x1800, 
    0x1800, 0x1800, 0x1800, 0x0000
};

/* 16x16 Bitmap for 'E' */
const unsigned int the_e[16] = {
    0xFFFF, 0xFFFF, 0xE000, 0xE000, 
    0xE000, 0xE000, 0xFFF0, 0xFFF0, 
    0xE000, 0xE000, 0xE000, 0xE000, 
    0xFFFF, 0xFFFF, 0xFFFF, 0x0000
};

/* 16x16 Bitmap for 'G' */
const unsigned int the_g[16] = {
    0x07F0, 0x1FF8, 0x381C, 0x700E, 
    0x6000, 0xE000, 0xE000, 0xE7FF, 
    0xE007, 0xE007, 0x6007, 0x7007, 
    0x381F, 0x1FF7, 0x07F3, 0x0000
};

/* 16x16 Bitmap for 'A' */
const unsigned int the_a[16] = {
    0x03C0, 0x07E0, 0x0E70, 0x1C38, 
    0x1C38, 0x381C, 0x381C, 0x7FFE, 
    0x7FFE, 0xE007, 0xE007, 0xE007, 
    0xE007, 0xE007, 0xE007, 0x0000
};

/* 16x16 Bitmap for 'M' */
const unsigned int the_m[16] = {
    0xE007, 0xF00F, 0xF81F, 0xDC3B, 
    0xCE73, 0xC663, 0xC243, 0xC003, 
    0xC003, 0xC003, 0xC003, 0xC003, 
    0xC003, 0xC003, 0xC003, 0x0000
};

UINT16 hor_start = 100; /* for aligning things */

void plot_title(UINT32 *base){
    hor_start = hor_start + 50;
    plot_16_bitmap(base, 10, hor_start, 16, the_c);
    plot_16_bitmap(base, 10, (hor_start+17), 16, the_h);
    plot_16_bitmap(base, 10, (hor_start+34), 16, the_u);
    plot_16_bitmap(base, 10, (hor_start+51), 16, the_c);
    plot_16_bitmap(base, 10, (hor_start+68), 16, the_k);

    plot_16_bitmap(base, 10, (hor_start+85), 16, the_colon);

    plot_16_bitmap(base, 10, (hor_start+119), 16, the_tee);
    plot_16_bitmap(base, 10, (hor_start+136), 16, the_h);
    plot_16_bitmap(base, 10, (hor_start+153), 16, the_e);

    plot_16_bitmap(base, 10, (hor_start+187), 16, the_g);
    plot_16_bitmap(base, 10, (hor_start+204), 16, the_a);
    plot_16_bitmap(base, 10, (hor_start+221), 16, the_m);
    plot_16_bitmap(base, 10, (hor_start+238), 16, the_e);

}

void prompt_sq(UINT32 *base) {
    plot_string(base, 30, (hor_start-10), "(Enter P to play or Q to quit.)");
}

void make_quitButton(UINT32 *base){
    plot_rectangle(base, 230, hor_start-20, 20, 80);
    plot_string(base, 237, (hor_start+3), "Quit");
}

void make_playButton(UINT32 *base) {
    plot_rectangle(base, 230, hor_start+195, 20, 80);
    plot_string(base, 237, hor_start+218, "Play");
}

void splashscreen_chars(UINT32 *base) {
    int i, j;
    
    plot_32_bitmap(base, 5, hor_start-40, 32, Chuck_bitmap);

    plot_32_bitmap(base, 200, hor_start-20, 32, womenSwimming_forward_bitmap);
    plot_32_bitmap(base, 200, hor_start+25, 32, womenSwimming_forward_bitmap);

    plot_32_bitmap(base, 200, hor_start+197, 32, womenSwimming_backward_bitmap);
    plot_32_bitmap(base, 200, hor_start+242, 32, womenSwimming_backward_bitmap);

    plot_32_bitmap(base, 100, hor_start, 32, womenWalking_bitmap);
    plot_32_bitmap(base, 132, hor_start+220, 32, womenWalking_bitmap);

    for (i = 0; i <=640; i+=32) {
        plot_32_bitmap(base, 100, i, 32, road_bitmap_upper);
    }

    for (i = 0; i <=640; i+=32) {
        plot_32_bitmap(base, 132, i, 32, road_bitmap_lower);
    }

}

int make_splashscreen(UINT32 *base) {
    int key;
    plot_title(base);
    prompt_sq(base);
    make_quitButton(base);
    make_playButton(base);
    splashscreen_chars(base);

    while (get_kbd_input() != 0);
    while (1) {
        /* Use your custom driver instead of Cnecin() */
        key = (int)get_kbd_input(); 

        if (key != 0) {
            if (key == 'P') {
                return 0;
            } 
            else if (key == 'Q') {
                return 1;
            }
        }
    }
    return -1;
}
