
/* driver for expand */

#include <stdlib.h>
#include <stdio.h>


#include "shims.h"


int main()
{
	char buffer[1024], *ptr;
	int count;

	ptr = "1 + 1 = 2";
	printf("exptest:\nExpanding %s\n", ptr);
	count = ex_shim(ptr, buffer);
    printf("%d bytes to expand '%s' to '%s'\n\n", count, ptr, buffer);

}


