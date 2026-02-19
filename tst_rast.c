#include <osbind.h>
#include "raster.h"

int main()
{
	void *base = Physbase();
	clear_screen(base);

	plot_line(base, 10, 10, 30, 10);
	plot_rectangle(base, 20, 20, 40, 50);
	plot_square(base, 200, 200, 40);
	return 0;
}