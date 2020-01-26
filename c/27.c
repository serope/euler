/*
 * Project Euler
 * 27.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "array.h"
#include "prime.h"


#define formula(a, b, n) n*n + a*n + b
bool may_be_prime(int x);


int main() {
	// sieve (1000 is sufficient for this problem)
	int primes_len;
	int* primes = eratosthenes(1000, &primes_len);
	
	/*
	 * Plug every possible value for a and b into the formula
	 * 
	 * 'a' goes from -999 to 999
	 * 'b' goes from -1000 to 1000
	 * 'n' goes from 0 to infinity
	 * 
	 * After a and b have been established, keep plugging in increasing
	 * values of n until the result is a nonprime
	 */
	int most_consec = 0;
	for (int a=-999; a < 1000; a++) {
		for (int b=-1000; b <= 1000; b++) {
			int n = 0;
			int f = formula(a, b, n);
			while (may_be_prime(f)) {
				f = formula(a, b, n);
				if (arr_bsearch(primes, primes_len, f))
					n++;
				else
					break;
			}
			if (n > most_consec) {
				most_consec = n;
				printf("a, b, n             %d, %d, %d \n", a, b, n);
				printf("formula(a, b, c)    %d \n", formula(a,b,n));
				printf("a*b                 %d \n\n", a*b);
			}
		}
	}
	
	// end
	free(primes);
	return 0;
}


/**
 * Returns true if x has a possibility of being prime, i.e. it's a
 * positive odd number.
 * 
 * @param	x	the term to check
 * @return		true or false
 */
bool may_be_prime(int x) {
	return (x>0 && x%2!=0);
}
