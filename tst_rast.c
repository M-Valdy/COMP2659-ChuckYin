#include <osbind.h>
#include "raster.h"

/* @author Gaurik */
int main()
{

	const UINT16 womenSwimming_forward_bitmap[16] =
{
    0x1ff8,
    0x3ffc,
    0x7ffe,
    0xffff,
    0xffff,
    0xc813,
    0xc423,
    0xc243,
    0xcdb3,
    0xcc33,
    0xc003,
    0xcff3,
    0xdffb,
    0xdffb,
    0xdffb,
    0xc003
};

	void *base = Physbase();
	clear_screen(base);
	
	plot_16_bitmap(base, 200, 250, 16, womenSwimming_forward_bitmap);
	
	plot_character(base, 350, 200, 'A');
	plot_string(base, 350, 210, "Hello there.");
	
	return 0;
}