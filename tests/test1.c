//
// Created by Jonathan CARRA on 1/10/18.
//

#include "malloc.h"

int main()
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		FT_DEBUG("addr %p", addr);
		addr[0] = 42;
		i++;
	}
	return (0);
}