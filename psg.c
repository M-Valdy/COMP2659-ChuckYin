#include "psg.h"
#include <stdio.h>
#include <osbind.h>
#include "types.h"

volatile char *PSG_reg_select = 0xFF8800;
volatile char *PSG_reg_write  = 0xFF8802;

UINT8 mixer_val = 0x3F;

/* Helper functions are located here*/
void write_psg(int reg, UINT8 val) {
    long old_ssp = Super(0);
    *PSG_reg_select = reg;
    *PSG_reg_write  = val;
    Super(old_ssp);
}

int channel_check(int channel, int first, int last){
    return (channel < first || channel > last);
}

void read_psg(int reg) {
    /*reads the current value of the psg reg*/
    long old_ssp = Super(0);
    if (reg < 0 || 15 < reg) {
        return;
    }
    *PSG_reg_select = reg;
    printf("reg %d = %u\n", reg, (UINT8)*PSG_reg_write);
    Super(old_ssp);
}

/* FUnctions that are actualy used in the program*/
void set_tone(int channel, int tuning) {
    int fine_tone;
    int coarse_tone;
    if (channel_check(channel, 0, 2)) {
        return;
    }    
    if (tuning >= 0 && tuning <= 0x0fff) {
        fine_tone = tuning & 0xFF; /* lower 8 bits for fine tune */
        coarse_tone = (tuning >> 8) & 0x0F; /* upper 4 bits for coarse tune */
        if (channel == 0) {
            write_psg(0, fine_tone);
            write_psg(1, coarse_tone);
        } else if (channel == 1) {
            write_psg(2, fine_tone);
            write_psg(3, coarse_tone);
        } else if (channel == 2) {
            write_psg(4, fine_tone);
            write_psg(5, coarse_tone);
        }
    }
}

void set_volume(int channel, int volume) {
    if (channel_check(channel, 0, 2)) {
        return;
    }
    if (volume > 0 || volume < 31) {
        if (channel == 0) {
        write_psg(8, volume);
    } else if (channel == 1) {
        write_psg(9, volume);
    } else if (channel == 2) {
        write_psg(10, volume);
    }
    }
}

void enable_channel(int channel, int tone_on, int noise_on) {
    if (channel_check(channel, 0, 2)) {
        return;
    }
    if ((tone_on == 0 || tone_on == 1) && (noise_on == 0 || noise_on == 1)) {
        if (channel == 0) {
            if (tone_on) {
                /* must set to 0 to enable tone */
                mixer_val &= 0xFE; /* set bit 0 to 0 */
            }
            if (noise_on) {
                /* must set to 0 to enable noise*/
                mixer_val &= 0xF7; /* set bit 3 to 0 */
            }
        }
        else if (channel == 1) {
            if (tone_on) {
                mixer_val &= 0xFD; /* set bit 1 to 0 */
            }
            if (noise_on) {
                mixer_val &= 0xEF; /* set bit 4 to 0 */
            }
        }
        if (channel == 2) {
            if (tone_on) {
                mixer_val &= 0xFB; /* set bit 2 to 0 */
            }
            if (noise_on) {
                mixer_val &= 0xDF; /* set bit 5 to 0 */
            }
        }
        write_psg(7, mixer_val);
    }
}

void stop_sound() {
    set_volume(0, 0);
    set_volume(1, 0);
    set_volume(2, 0);
}
