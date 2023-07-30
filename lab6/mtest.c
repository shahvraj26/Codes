

/* driver for middle */

#include <stdlib.h>
#include <stdio.h>


#include "shims.h"

int main()
{
	char buffer[1024], *ptr;
	int count;

	ptr = "1 + 1 = 2";
	printf("mtest: Expanding %s\n", ptr);
	count = m_shim(ptr );
	printf("	took %d bytes.\n\n", count );

	ptr = "1 + 2 - 3 * 4 / 6 = + 1";
	printf("mtest: Expanding %s\n", ptr);
	count = m_shim(ptr );
	printf("	took %d bytes.\n\n", count );

	ptr = "This string only seems long";
	printf("mtest: Expanding %s\n", ptr);
	count = m_shim(ptr );
	printf("	took %d bytes.\n\n", count );

	return 0;
}



