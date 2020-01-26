/*
 * Project Euler
 * 41.c
 */
#include <stdlib.h>
#include <stdio.h>
#include "euler.h"
#include "prime.h"
#include "pandigital.h"

int main() {
	// sieve
	int primes_len;
	int* primes = eratosthenes(100000, &primes_len);
	
	// permute pandigitals in descending order starting from n=9
	int answer = 0;
	for (int n=9; n>=1; n--) {
		int perms = factorial(n);
		for (int i=perms; i>=0; i--) {
			pand_t* p = pand_permute_ith(i, n);
			int x = pand_to_int(p, n);
			pand_free(p);
			if (is_prime_trial(x, primes, primes_len)) {
				answer = x;
				break;
			}
		}
		if (answer > 0)
			break;
	}
	
	// end
	printf("%d \n", answer);
	free(primes);
	return 0;
}
