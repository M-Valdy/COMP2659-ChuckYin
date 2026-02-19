#include <osbind.h>
#include "raster.h"

int main()
{
	void *base = Physbase();

	clear_screen(base);
	plot_pixel(base, 100, 100);
	plot_pixel(base, 200, 200);

	return 0;
}
