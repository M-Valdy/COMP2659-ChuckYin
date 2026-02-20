#include <osbind.h>
#include "raster.h"

int main()
{
	void *base = Physbase();
	clear_screen(base);

	plot_character(base, 100, 160, 'A');
	return 0;
}