#include <osbind.h>
#include "start.h"

/* @author Gaurik */
int main()
{

	void *base = Physbase();
	clear_screen(base);
	
    make_splashscreen(base);
	return 0;
}


