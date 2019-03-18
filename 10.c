/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 10
 **********************************************************************/
#include "euler.h"

int main() {
	/*******************************************************************
	 * 1. Create a list of primes from 1 to 2 million
	 ******************************************************************/
	int* list = eratosthenes(2000000);
	int list_len = eratosthenes_count(2000000);
	
	
	/*******************************************************************
	 * 2. Add the primes
	 ******************************************************************/
	int64_t sum = 0;
	for (int i=0; i<list_len; i++)
		sum += list[i];	
			
			
	/*******************************************************************
	 * 3. Print, cleanup, and exit
	 ******************************************************************/
	printf("%lld \n", sum);	
	free(list);
	return 0;
}