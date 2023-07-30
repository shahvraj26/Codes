
/* lab 6 driver program */


#include <stdlib.h>
#include <stdio.h>

#include "shims.h"




int main()
{
	char *strings[] = {
		"1 + 1 = 2",  
		"1 + 2 - 3 * 4 / 6 = + 1",
		"This string only seems long",
		NULL};

	int count = sizeof(strings)/ sizeof(strings[0]) - 1;
	char *best;

	best = s_shim(strings, count);
	printf("Lab 6: %s had the longest conversion.\n", best);

	return 0;
}


