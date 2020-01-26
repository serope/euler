/*
 * Project Euler
 * 35.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "euler.h"
#include "prime.h"


int* rotations_of(int x);
bool is_circular_prime(int x, int* primes, int primes_len);


int main() {
	// sieve
	int limit = 1000000;
	int primes_len;
	int* primes = eratosthenes(limit, &primes_len);
	
	// count circular primes
	int total = 0;
	for (int i=0; i<primes_len; i++) {
		if (is_circular_prime(primes[i], primes, primes_len)) {
			printf("%d \n", primes[i]);
			total++;
		}
	}
	
	// end
	printf("total %d \n", total);
	free(primes);
	return 0;
}


/**
 * Generates x's rotations, excluding x itself. The output array's length
 * is 1 less than x's total digits.
 * 
 * @param	x	the term to evaluate
 * @return		a heap-allocated array
 */
int* rotations_of(int x) {
	int* digits = digits_of(x);
	int digits_len = digit_count(x);
	int* rots = calloc(digits_len-1, sizeof(int));
	for (int i=0; i<digits_len-1; i++) {
		digits = arr_shift_left(digits, digits_len);
		int rot = digits_to_int(digits, digits_len);
		rots[i] = rot;
	}
	free(digits);
	return rots;
}


/**
 * Returns true if x is a circular prime as described in the problem
 * text.
 * 
 * @param	x			the term to test
 * @param	primes		an array of primes
 * @param	primes_len	the array's length
 * @return				true or false
 */
bool is_circular_prime(int x, int* primes, int primes_len) {
	int* rots = rotations_of(x);
	int rots_len = digit_count(x)-1;
	int total_primes = 0;
	for (int i=0; i<rots_len; i++) {
		if (arr_bsearch(primes, primes_len, rots[i]))
			total_primes++;
		else
			break;
	}
	free(rots);
	return (total_primes == rots_len);
}
