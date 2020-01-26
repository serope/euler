/*
 * Project Euler
 * 10.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "prime.h"

int main() {
	// sieve
	int limit = 2000000;
	int* list = NULL;
	int len = 0;
	list = eratosthenes(limit, &len);
	
	// sum
	int64_t sum = 0;
	for (int i=0; i<len; i++)
		sum += list[i];	
			
	// end
	free(list);
	printf("%" PRId64 "\n", sum);	
	return 0;
}
