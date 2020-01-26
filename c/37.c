/*
 * Project Euler
 * 37.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "euler.h"
#include "prime.h"

bool has_problem37_property(int x, int* primes, int primes_len);
int* truncated_stages(int x, int* len_ptr);

int main() {
	// sieve
	int lim = 1000000;
	int primes_len;
	int* primes = eratosthenes(lim, &primes_len);

	// find 11 truncatable primes
	int* trunc = NULL;
	int trunc_len = 0;
	for (int i=0; i<primes_len; i++) {
		int x = primes[i];
		if (has_problem37_property(x, primes, primes_len)) {
			trunc = arr_append(trunc, x, &trunc_len);
			if (trunc_len == 11)
				break;
		}
	}
	
	// end
	arr_print(trunc, trunc_len);
	printf("sum %d \n", arr_sum(trunc, trunc_len));
	free(primes);
	free(trunc);
	return 0;
}


/**
 * Returns true if all of x's truncated stages are in the given primes
 * array.
 * 
 * @param	x			the term to test
 * @param	primes		an array of primes
 * @param	primes_len	the array's length
 * @return				true or false
 */
bool has_problem37_property(int x, int* primes, int primes_len) {
	if (x==2 || x==3 || x==5 || x==7)	// skip as per problem text
		return false;
	int stages_len;
	int* stages = truncated_stages(x, &stages_len);
	bool all_prime = true;
	for (int i=0; i<stages_len; i++) {
		if (!arr_bsearch(primes, primes_len, stages[i])) {
			all_prime = false;
			break;
		}
	}
	free(stages);
	return all_prime;
}


/**
 * Returns an array of x's truncated stages, excluding x itself.
 * e.g. 3797 -> {797, 97, 7, 379, 37, 3}
 * Note that the amount of stages is always equal to digit_len * 2 - 2.
 * 
 * @param	x			the term to evaluate
 * @param	len_ptr		a pointer to an integer which takes on the
 * 						length of the returned array
 * @return				an array of x's truncated stages
 */
int* truncated_stages(int x, int* len_ptr) {
	// init
	int* digits = digits_of(x);
	int digits_len = digit_count(x);
	int stages_len = digits_len*2-2;
	int* stages = calloc(stages_len, sizeof(int));
	int stages_i = 0;
	int m = int_pow(10, digits_len-1);	// multiplier
	
	// truncate left to right
	int stage = x;
	for (int i=0; i<digits_len-1; i++) {
		stage -= digits[i]*m;
		m = m/10;
		stages[stages_i] = stage;
		stages_i++;
	}
	
	// truncate right to left
	stage = x;
	for (int i=digits_len-1; i>0; i--) {
		stage -= digits[i];
		stage = stage/10;
		stages[stages_i] = stage;
		stages_i++;
	}
	
	// end
	free(digits);
	*len_ptr = stages_len;
	return stages;
}
