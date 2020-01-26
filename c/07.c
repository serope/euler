/*
 * Project Euler
 * 07.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "prime.h"

int main() {
	int limit = 1000000;					// sieve
	int len = 0;
	int* list = eratosthenes(limit, &len);
		
	int n = 10001;							// print
	if (len < n)
		printf("len = %d \n", len);
	else
		printf("%d \n", list[n-1]);
	
	free(list);								// end
	return 0;
}
