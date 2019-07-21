/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 7
 **********************************************************************/
#include "euler.h"

int main() {
	/*******************************************************************
	 * 1. Create a list of primes from 1 to a large upper limit
	 *    (1 million is sufficient)
	 ******************************************************************/
	int limit = 1000000;
	int* list = eratosthenes(limit);
	int list_len = eratosthenes_count(limit);
		

	
	/*******************************************************************
	 * 2. Print the 10,001st term on the list
	 ******************************************************************/
	if (list_len < 10001)
		puts("The 10,001st prime wasn't found. Increase the limit.");
	else
		printf("%d \n", list[10000]);
			
			
	/*******************************************************************
	 * 3. Cleanup and exit
	 ******************************************************************/
	free(list);
	return 0;
}
