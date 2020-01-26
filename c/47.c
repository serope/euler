/*
 * Project Euler
 * 47.c
 * TODO: Write a better, shorter solution for this
 */
#include <stdio.h>
#include <stdlib.h>
#include "array.h"

int* consecutive_subarr(int* arr, int len, int chain, int* len_ptr);
int dpf_count(int x, int* primes, int primes_len);
int arr_prod(int* arr, int len);

int main() {
	// 500k numbers
	int limit = 500000;
	int* numbers = natural_numbers(limit);
	
	// sieve of Eratosthenes: turn nonprimes to zero
	for (int i=1; i<limit; i++) {
		if (numbers[i] > 0) {
			int cross_out_index = i+numbers[i];
			while (cross_out_index < limit) {
				numbers[cross_out_index] = 0;
				cross_out_index += numbers[i];
			}
		}
	}
	numbers[0] = 0; // cross 1 out
	
	// separate primes from nonprimes
	int* primes			= NULL;
	int primes_len		= 0;
	int* nonprimes		= NULL;
	int nonprimes_len	= 0;
	for (int i=0; i<limit; i++) {
		if (numbers[i] == 0)
			nonprimes = arr_append(nonprimes, i+1, &nonprimes_len);
		else
			primes = arr_append(primes, numbers[i], &primes_len);
	}
	
	// create list of nonprimes that are consecutive with at least 4
	// other terms
	int chain = 4;
	int consec_nps_len;
	int* consec_nps = consecutive_subarr(nonprimes, nonprimes_len, chain,
														&consec_nps_len);
	
	// solve
	chain = 0;
	int goal = 4;
	int answer;
	for (int i=1; i<consec_nps_len; i++) {
		// next 2 terms
		int n = consec_nps[i];
		int last_n = consec_nps[i-1];
		
		// skip if not consecutive
		if (n != last_n+1) {
			chain = 0;
			continue;
		}
		
		// does it have 4 DPFs? if not, reset
		if (dpf_count(n, primes, primes_len) == 4)
			chain++;
		else {
			chain = 0;
			continue;
		}
		
		// solved
		if (chain == goal) {
			answer = n-(goal-1);
			break;
		}
	}
	
	// end
	printf("limit              %d \n", limit);
	printf("primes             %p \n", primes);
	printf("primes_len         %d \n", primes_len);
	printf("nonprimes          %p \n", nonprimes);
	printf("nonprimes_len      %d \n", nonprimes_len);
	printf("consec_nps         %p \n", consec_nps);
	printf("consec_nps_len     %d \n\n", consec_nps_len);
	if (chain == goal) {
		printf("answer             %d \n", answer);
		printf("                   %d \n", answer+1);
		printf("                   %d \n", answer+2);
		printf("                   %d \n", answer+3);
	}
	else
		puts("Didn't find the answer. Try increasing the limit.");
	free(numbers);
	free(primes);
	free(nonprimes);
	free(consec_nps);
	return 0;
}

/**
 * Read the given array for consecutive terms that create a chain, and
 * return a new array containing every term in those chains.
 * 
 * @param	arr		the base array
 * @param	len		the base array's length
 * @param	chain	the lowest amount of consecutive terms in one chain
 * @param	len_ptr	a pointer to an integer to take on the length of the
 * 					output array
 * @return			a heap-allocated array
 */
int* consecutive_subarr(int* arr, int len, int chain, int* len_ptr) {
	int* consec = NULL;
	int consec_len = 0;
	int consecutive = 0;
	for (int i=1; i<len; i++) {
		int prev = arr[i-1];
		int current = arr[i];
		if (current == prev+1)
			consecutive++;
		else {
			if (consecutive >= chain) {
				for (int c=consecutive; c>0; c--)
					consec = arr_append(consec, arr[i-c], &consec_len);
			}
			consecutive = 0;
		}
	}
	*len_ptr = consec_len;
	return consec;
}


/**
 * Counts the amount of x's DPFs.
 * 
 * @param	x			the term to factorize
 * @param	primes		an array of primes
 * @param	primes_len	the length of the array
 * @return				the amount of x's DPFs
 */
int dpf_count(int x, int* primes, int primes_len) {
	// primes have only 1 DPF
	if (arr_bsearch(primes, primes_len, x))
		return 1;
	
	// squares of primes have only 1 DPF
	for (int i=0; i<primes_len; i++) {
		int sq = primes[i] * primes[i];
		if (sq == x)
			return 1;
		else if (sq > x)
			break;
	}
	
	// factorize
	int* factors = NULL;
	int len = 0;
	int y = x;
	for (int i=0; i < primes_len; i++) {
		int p = primes[i];
		if (p > x)
			break;
		if (y%p == 0) {
			factors = arr_append(factors, p, &len);
			y = y/p;
			while (arr_bsearch(primes, primes_len, y)) {
				factors = arr_append(factors, y, &len);
				if (y%p == 0)
					y = y/p;
				else
					break;
			}
		}
		if (arr_prod(factors, len) == x)
			break;
	}
	
	// remove repeats
	for (int i=0; i<len-1; i++) {
		if (factors[i]==0)
			continue;
		for (int j=i+1; j<len; j++) {
			if (factors[i]==factors[j]) {
				factors[j] = 0;
			}
		}
	}

	// count remaining
	int count = 0;
	for (int i=0; i<len; i++)
		if (factors[i] > 0)
			count++;
	
	// end
	free(factors);
	return count;
}


/**
 * Computes the product of an array.
 * 
 * @param	arr		the array to evaluate
 * @param	len		the array's length
 * @return			an integer
 */
int arr_prod(int* arr, int len) {
	int p = 1;
	for (int i=0; i<len; i++)
		p *= arr[i];
	return p;
}
