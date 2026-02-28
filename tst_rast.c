#include <osbind.h>
/* #include "raster.h" */
#include "Chuck.h"

extern void	clear_screen();
extern void clear_region();
extern void plot_pixel();
extern void	plot_horizontal_line();
extern void	plot_vertical_line();
extern void plot_line();
extern void plot_rectangle();
extern void plot_square();
extern void	plot_triangle();


/* @author Gaurik */
int main()
{
	void *base = Physbase();
	clear_screen(base);
	plot_pixel(base, 10, 10);
	plot_horizontal_line(base, 105, 100, 10);
	plot_vertical_line(base, 105, 100, 10);
	plot_line(base, 10, 10, 10, 20);
	plot_rectangle(base, 200, 200, 10, 20);
	plot_square(base, 10, 100, 50);
	plot_triangle(base, 300, 300, 10, 10, 0);
	/* plot_string(base, 50, 50, "My bad?");*/

	/* plot_bitmap_8(base, 200, 200, 8, invader_8x8); */
	/* plot_bitmap_16(base, 100, 100, 16, invader_16x16); */
	/* plot_bitmap_32(base, 300, 300, 32, Chuck_bitmap); */
	return 0;
}