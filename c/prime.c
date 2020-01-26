/*
 * Project Euler
 * prime.c
 */
#include <stdlib.h>
#include <stdio.h>
#include "prime.h"


int* eratosthenes(int n, int* len_ptr) {
	int* numbers = calloc(n, sizeof(int));	// natural numbers
	for (int i=0; i<n; i++)
		numbers[i] = i+1;
	
	int* primes = NULL;						// sieve (0 = crossed out)
	int len = 0;
	for (int i=1; i<n; i++) {
		if (numbers[i]>0) {
			primes = realloc(primes, sizeof(int)*(len+1));	// append
			primes[len] = numbers[i];
			len += 1;
			
			int cross_out_index = i+numbers[i];				// cross out
			while (cross_out_index < n) {
				numbers[cross_out_index] = 0;
				cross_out_index += numbers[i];
			}
		}
	}
	
	free(numbers);	// end
	*len_ptr = len;
	return primes;
}



bool is_prime_trial(int x, int* primes, int primes_len) {
	if (x <= 1)
		return false;
	int lim = (int) sqrt(x);
	for (int i=0; i<primes_len; i++) {
		int p = primes[i];
		if (p > lim)
			break;
		else if (x%p == 0)
			return false;
	}
	return true;
}


bool is_prime_trial64(int64_t x, int* primes, int primes_len) {
	if (x <= 1)
		return false;
	int lim = (int) sqrt(x);
	for (int i=0; i<primes_len; i++) {
		int p = primes[i];
		if (p > lim)
			break;
		else if (x%p == 0)
			return false;
	}
	return true;
}
