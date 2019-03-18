/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 3
 **********************************************************************/
#include "euler.h"

int main() {
	/*******************************************************************
	 * 1. Find the odd factors of 'x'
	 ******************************************************************/
	int64_t x = 600851475143;
	int64_t* factors = odd_factors_of(x);
	int factors_len = odd_factor_count(x);


	/*******************************************************************
	 * 2. Pick out the largest prime one
	 ******************************************************************/
	int64_t largest_prime = 0;
	
	for (int i=0; i<factors_len; i++)
		if (is_prime_int64(factors[i]) && factors[i]>largest_prime)
			largest_prime = factors[i];
	
	
	/*******************************************************************
	 * 3. Cleanup, print, and exit
	 ******************************************************************/
	free(factors);
	printf("%lld \n", largest_prime);
	return 0;
}
