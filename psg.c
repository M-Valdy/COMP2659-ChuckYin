#include "psg.h"

volatile char *PSG_reg_select = 0xFF8800;
volatile char *PSG_reg_write  = 0xFF8802;

void write_psg(int reg, UINT8 val) {
    long old_ssp = Super(0);
    *PSG_reg_select = reg;
    *PSG_reg_write  = val;
    Super(old_ssp);
    return 0;
}


void set_tone(int channel, int tuning) {
    int rough_tone = tuning | 0x0f; /* lower 4 bits for fine tune */
    int coarse_tone = tuning >> 4; /* upper 8 bits for coarse tune */
    if (channel == 0) {
        write_psg(0, rough_tone);
        write_psg(1, coarse_tone);
    } else if (channel == 1) {
        write_psg(2, rough_tone);
        write_psg(3, coarse_tone);
    } else if (channel == 2) {
        write_psg(4, rough_tone);
        write_psg(5, coarse_tone);
    }
    return 0;
}

set_volume(int channel, int volume) {
    if (channel == 0) {
        write_psg(8, volume);
    } else if (channel == 1) {
        write_psg(9, volume);
    } else if (channel == 2) {
        write_psg(10, volume);
    }
}

 enable_channel(int channel, int tone_on, int noise_on) {
    
}