/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 37
 **********************************************************************/
#include "euler.h"

int main() {
	/*******************************************************************
	 * 1. Create a list of prime numbers from 1 to 1 million
	 ******************************************************************/
	int* primes = eratosthenes(1000000);
	int primes_len = eratosthenes_count(1000000);

	
	/*******************************************************************
	 * 2. For every prime 'x' on the list, check if its truncated
	 *    stages are also prime. If they are, add 'x' to the sum.
	 * 
	 *    Stop when 11 have been found.
	 ******************************************************************/
	int sum = 0;
	int total_trunc_primes_found = 0;
	
	for (int p=0; p<primes_len; p++) {
		/***********************************************************
		 * 2a. As per the description, skip if x is 2, 3, 5, or 7
		 **********************************************************/
		int x = primes[p];
		if (x==2 || x==3 || x==5 || x==7)
			continue;
		
		/***********************************************************
		 * 2b. Get this prime's truncated stages
		 **********************************************************/
		int* stages		= truncated_stages(x);
		int stages_len	= total_truncated_stages(x);

		
		/***********************************************************
		 * 2c. Check if each stage is prime
		 *     If any stage is NOT prime, then ignore this 'x'
		 **********************************************************/
		bool all_stages_are_prime = true;
		for (int s=0; s<stages_len; s++) {
			if (!contains(primes, stages[s], primes_len)) {
				all_stages_are_prime = false;
				break;
			}
		}
		if (!all_stages_are_prime) {
			free(stages);
			continue;
		}
		
		/***********************************************************
		 * 2d. If 'x' passed the above test, then 'x' is a
		 *     truncatable prime, so add it to the sum.
		 **********************************************************/
		printf("%d is a truncatable prime \t{", x);
		for (int s=0; s<stages_len; s++)
			printf("%d ", stages[s]);
		printf("\b}\n");
		
		sum += x;
		free(stages);
		
		
		/***********************************************************
		 * 2e. If 11 truncatable primes have been found, stop
		 **********************************************************/
		total_trunc_primes_found++;
		if (total_trunc_primes_found==11)
			break;
	}
	
	
	/*******************************************************************
	 * 3. Print, free memory, and exit
	 ******************************************************************/
	printf("sum:     %d \n", sum);
	free(primes);
	return 0;
}
