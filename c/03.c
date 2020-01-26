/*
 * Project Euler
 * 03.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "euler.h"
#include "prime.h"

int64_t*	odd_factors_of(int64_t x, int* len);
int64_t*	merge64(int64_t* arr1, int len1, int64_t* arr2, int len2);
int64_t*	append_int64(int64_t* list, int64_t x, int* len_ptr);
int64_t		min_int64(int64_t* set, int len);
#define		IS_ODD(x)			x%2!=0
#define		IS_DIVISIBLE(x,d)	x%d==0

int main() {
	// sieve
	int primes_len;
	int* primes = eratosthenes(1000000, &primes_len);
	
	// get odd factors
	int64_t x = 600851475143;
	int64_t* factors = NULL;
	int len = 0;
	factors = odd_factors_of(x, &len);
	
	// find largest prime
	int64_t largest = 0;
	for (int i=0; i<len; i++) {
		int f = factors[i];
		if (is_prime_trial64(f, primes, primes_len) && f>largest)
			largest = f;
	}
	
	// end
	free(factors);
	printf("%" PRId64 "\n", largest);
	return 0;
}


/**
 * Returns an unordered array of x's odd factors and saves the length.
 * 
 * @param	x			the term to factorize
 * @param	len_ptr		a pointer to an integer representing the array's
 * 						length
 * @return				an array of 64-bit integers
 */
int64_t* odd_factors_of(int64_t x, int* len) {
	// edge cases
	if (x==1 || x==2) {
		int64_t* factors = malloc(sizeof(int64_t));
		factors[0] = 1;
		*len = 1;
		return factors;
	}
	
	// upper = {x}
	int64_t* upper = malloc(sizeof(int64_t));
	upper[0] = x;
	int upper_len = 1;
	
	// lower = {1}
	int64_t* lower = malloc(sizeof(int64_t));
	lower[0] = 1;
	int lower_len = 1;
	
	// factorization
	int64_t factor = 3;
	while (factor < min_int64(upper, upper_len)) {
		if (IS_DIVISIBLE(x, factor)) {
			lower = append_int64(lower, factor, &lower_len);
			if (IS_ODD(x/factor) && factor*factor != x)
				upper = append_int64(upper, x/factor, &upper_len);
		}
		factor += 2;
	}
	
	// end
	int64_t* factors = merge64(upper, upper_len, lower, lower_len);
	*len = upper_len + lower_len;
	free(upper);
	free(lower);
	return factors;
}


/**
 * Merges two arrays of 64-bit integers into a new array.
 * 
 * @param	arr1	the first array
 * @param	len1	the first array's length
 * @param	arr2	the second array
 * @param	len2	the second array's length
 * @return			a new array of length len1+len2
 */
int64_t* merge64(int64_t* arr1, int len1, int64_t* arr2, int len2) {
	int64_t* arr3 = calloc(len1 + len2, sizeof(int64_t));
	size_t size1 = sizeof(int64_t) * len1;
	size_t size2 = sizeof(int64_t) * len2;
	memcpy(arr3, arr1, size1);
	memcpy(&arr3[len1], arr2, size2);
	return arr3;
}


/**
 * Appends a 64-bit integer to an array, incrementing its length by 1.
 * 
 * @param	arr			the array to append to
 * @param	x			the term to append
 * @param	len_ptr		a pointer to an integer representing the array's
 * 						length
 * @return				the array
 */
int64_t* append_int64(int64_t* arr, int64_t x, int* len_ptr) {
	arr = realloc(arr, sizeof(int64_t) * (*len_ptr + 1) );
	arr[*len_ptr] = x;
	*len_ptr += 1;
	return arr;
}


/**
 * Returns the smallest element in an array of 64-bit integers.
 * 
 * @param	arr		the array to search
 * @param	len		the array's length
 * @return			the found element
 */
int64_t min_int64(int64_t* list, int len) {
	int64_t x = list[0];
	for (int i=0; i<len; i++)
		if (list[i]<x)
			x = list[i];
	return x;
}
