
/* COpyright 2023 Neil Kirby */
/* Vraj Shah */

#include <stdlib.h>
#include <stdio.h>

#include "altmem.h"
#include "structs.h"
#include "debug.h"

#include "memory.h"

/* Allocates Ball */
struct Ball *allocate_ball()
{
	struct Ball *bp;
	static int allocations = 0;
	
	//alternative calloc
	if( bp = alternative_calloc(1, sizeof(struct Ball)))
	{
	    //Allocate ball
	    allocations++;
	    if(TEXT)printf("DIAGNOSTIC: %d balls allocated\n", allocations);
	}
	else
	{
	    if(TEXT)printf("ERROR: failed to allocate ball\n");
	}
	return bp;
}

// I might get called as an action function, hence the signature
/* Frees Ball */
void free_ball(void *data)
{
	static int freed = 0;

	if(data)
	{
	    freed++;
	    //Changes to alternative free function
	    alternative_free(data);
	    if(TEXT)printf("DIAGNOSTIC: %d balls freed\n", freed);
	}
	else
	{
	    if(TEXT)printf("ERROR: tried to free NULL pointer.\n");
	}

}
