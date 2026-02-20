#include <osbind.h>
#include "raster.h"

int main()
{
	void *base = Physbase();
	clear_screen(base);

	plot_string((UINT8 *)base, 100, 160, "Hello world.");
	return 0;
}