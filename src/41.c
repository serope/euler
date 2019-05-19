/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 41
 **********************************************************************/
#include "euler.h"

int main() {
	/*******************************************************************
	 * Starting at the largest 9-digit pandigital number, check every
	 * n-digit pandigital number below it.
	 * 
	 * Stop when a prime one is found.
	 ******************************************************************/
	int64_t largest_prime_pandigital = 0;
	
	
	for (int n=9; n>=1; n--) {
		/***************************************************************
		 * Get the amount of total permutations for the current n
		 **************************************************************/
		int total_permutations = factorial(n);
		
		
		/***************************************************************
		 * Check every permutation for the current n
		 **************************************************************/
		for (int t=total_permutations; t>=1; t--) {
			/***********************************************************
			 * 1. Get the current permutation's sequence
			 **********************************************************/
			int* sequence = nth_permutation_of_pandigital(t, n);
			
			
			/***********************************************************
			 * 2. Convert it into an integer, then free it
			 **********************************************************/
			int64_t integer = 0;
			int multiplier = 1;
			
			for (int i=n-1; i>=0; i--) {
				integer += sequence[i]*multiplier;
				multiplier *= 10;
			}
			
			free(sequence);
			
			
			/***********************************************************
			 * 3. Check the primality of the integer
			 *    Break if it's prime
			 **********************************************************/
			if (is_prime_int64(integer)) {
				largest_prime_pandigital = integer;
				break;
			}
		}
	
		if (largest_prime_pandigital>0)
			break;
	}
	
	
	/*******************************************************************
	 * Print and exit
	 ******************************************************************/
	printf("%lld \n", largest_prime_pandigital);
	return 0;
}
