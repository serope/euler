/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 27
 **********************************************************************/
#include <stdio.h>
#include "euler.h"

#define FORMULA(a, b, n)      n*n + a*n + b

int main() {
	int most_consecutive_primes = 0;
	int product = 0;
	
	
	/*******************************************************************
	* 'a' goes from -999 to 999
	* 'b' goes from -1000 to 1000
	* 'n' goes from 0 to infinity
	* 
	* Plug every possible value for 'a' and 'b' into the formula
	* 
	* After 'a' and 'b' have been established, keep plugging in
	* increasing values of 'n' until the result is a non-prime number
	******************************************************************/
	for (int a=-999; a<999+1; a++) {
		for (int b=-1000; b<1000+1; b++) {
			
			int consecutive_primes = 0;
			int n = 0;
			
			while (is_prime(FORMULA(a, b, n))) {
				consecutive_primes += 1;
				n += 1;
			}
			
			
			if (consecutive_primes > most_consecutive_primes) {
				most_consecutive_primes = consecutive_primes;
				product = a*b;
				printf("consecutive_primes      %d \n", consecutive_primes);
				printf("a, b                    %d, %d \n", a, b);
				printf("product                 %d \n\n", product);
			}
		}
	}
}
