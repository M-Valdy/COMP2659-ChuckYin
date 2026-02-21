#include <osbind.h>
#include "raster.h"

int main()
{

	/* 8x8 bitmap: 1 byte per row */
static const UINT8 invader_8x8[8] = {
    0x18,  /* XX    */
    0x3C,  /* XXXX   */
    0x7E,  /* XXXXXX  */
    0xDB,  /* XX XX XX */
    0xFF,  /* XXXXXXXX */
    0x24,  /* X  X   */
    0x5A,  /* X XX X  */
    0xA5   /* X X  X X */
};

	const UINT16 invader_16x16[16] =
	{
		0x0000,
		0x0810,
		0x0810,
		0x0420,
		0x0240,
		0x1FF8,
		0x2004,
		0x4662,
		0x4002,
		0x43C2,
		0x2424,
		0x1008,
		0x0FF0,
		0x0000,
		0x0000,
		0x0000,
	};

	/* 32x32 bitmap: 1 long (4 bytes) per row */
	const UINT32 boss_32x32[32] = {
    0x00000000, 0x00018000, 0x0003C000, 0x0007E000,
    0x000FF000, 0x001FF800, 0x003FFC00, 0x007FFE00,
    0x00FFFF00, 0x01FFFF80, 0x03FFFFC0, 0x07FFFFE0,
    0x0FDBDBF0, 0x1FDBDBF8, 0x3FDBDBFC, 0x7FDBDBFE,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0x7E00007E, 0x3C00003C, 0x18000018, 0x00000000,
    0x80000001, 0xC0000003, 0xE0000007, 0xF000000F,
    0x7800001E, 0x3C00003C, 0x1E000078, 0x0F0000F0
};

	void *base = Physbase();
	clear_screen(base);

	plot_string(base, 50, 50, "Can we have sex now?");

	plot_bitmap_8(base, 200, 200, 8, invader_8x8);
	plot_bitmap_16(base, 100, 100, 16, invader_16x16);
	plot_bitmap_32(base, 300, 300, 32, boss_32x32);
	return 0;
}