/*
 * Project Euler
 * 21.c
 */
#include <stdio.h>
#include <stdbool.h>
#include "array.h"
#include "euler.h"
#include "factor.h"

int* amicable_numbers(int lim, int* len_ptr);
int proper_divisor_sum(int x);

int main() {
	// generate amicable numbers
	int lim = 10000;
	int len;
	int* arr = amicable_numbers(lim, &len);
	
	// sum
	int sum = arr_sum(arr, len);
	
	// end
	printf("sum  %d \n", sum);
	free(arr);
	return 0;
}


/**
 * Generates the amicable numbers from 2 to a given limit.
 * 
 * @param	lim			the range's limit
 * @param	len_ptr		a pointer to an integer to take on the length of
 * 						the output array
 * @return				a heap-allocated array
 */
int* amicable_numbers(int lim, int* len_ptr) {
	#define D(x) proper_divisor_sum(x)
	int* arr = NULL;
	int len = 0;
	for (int n=2; n<lim; n++) {
		int a = D(n);
		int b = D(a);
		if (b==n && a!=b) {
			if (!arr_bsearch(arr, len, a))
				arr = arr_append(arr, a, &len);
			if (!arr_bsearch(arr, len, b))
				arr = arr_append(arr, b, &len);
		}
	}
	*len_ptr = len;
	return arr;
}


/**
 * Computes the sum of x's proper divisors.
 * 
 * @param	x	the integer to check
 * @return		the sum
 */
int proper_divisor_sum(int x) {
	int len;
	int* arr = proper_divisors(x, &len);
	int sum = arr_sum(arr, len);
	free(arr);
	return sum;
}
