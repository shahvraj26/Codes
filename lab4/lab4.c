/* Copyright 2023, Neil Kirby.  Not for disclosure without permission */
/* Vraj Shah */

/* system includes go first */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "libpb.h"

/* includes for constants and tyupes are next */
#include "debug.h"
#include "constants.h"
#include "structs.h"

/* includes for functions go last */
#include "n2.h"
#include "input.h"
#include "sim.h"
#include "lab4.h"

/* init value */
bool init()
{
	return(TEXT || ( GRAPHICS && pb_initialize()));

}

/* Teardown graphics */
void teardown()
{
	if(GRAPHICS)pb_teardown();
}

/* Main function */
int main(int argc, char *argv[])
{
	double start, runtime;

	start = now();	// this is the very first executable statement

	// Initiate structs
	struct Sim Balley = { 0.0, 0, NULL, NULL};
        struct Sim *table = &Balley;

	if( init())
	{
		//Run FileIO function
		arguments(argc, argv, table);
		teardown();
	}

	/* at this point we are done, graphics has been torn down*/
	runtime = now() - start;
	/* after graphics has been torn down, we can freely print */
	printf("Total runtime is %.9lf seconds\n", runtime);

	return 0;
}

