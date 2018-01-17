//
// Created by Jonathan CARRA on 1/16/18.
//

#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>			/* |printf()| */
#include <inttypes.h>		/* |PRIu64| */
#include <stdint.h>			/* |uint64_t| */


int		main()
{
	struct rusage	rusage1;
	struct rusage	rusage2;

	void			*addr;
	size_t			size;


	getrusage(RUSAGE_SELF, &rusage1);
	printf("Page reclaim %" PRIu64 "\n", (uint64_t)rusage1.ru_minflt);

	size = getpagesize() * 25;

	for (int i = 0 ; i < 1024 ; ++ i)
	{
		addr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON,
					-1, 0);
		((char *) addr)[0] = 42;

		munmap(addr, size);
	}

	getrusage(RUSAGE_SELF, &rusage2);
	printf("Page reclaim %" PRIu64 "\n", (uint64_t)rusage2.ru_minflt);

	return 0;
}