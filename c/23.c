/*
 * Project Euler
 * 23.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "factor.h"

int* abundant_numbers(int n, int* len_ptr);
bool is_abundant(int x);
bool* new_problem23_dict(int* arr, int len, int limit);

int main() {
	// generate
	int limit = 28123;
	int len;
	int* arr = abundant_numbers(limit, &len);
	
	/*
	 * create problem 23 map
	 * key:	abundant number
	 * val:	whether the key can be written as the sum of two abundant
	 * 		numbers
	 */
	bool* dict = new_problem23_dict(arr, len, limit);
	
	// sum non-abundant terms
	int sum = 0;
	for (int i=0; i<limit; i++)
		if (!dict[i])
			sum += i;
	
	// end
	printf("%d \n", sum);
	free(arr);
	free(dict);
	return 0;
}


/**
 * Generates every abundant number (number whose proper divisors' sum is
 * greater than itself) from 12 to n.
 * 
 * @param	n			the number to generate up to
 * @param	len_ptr		a pointer to an integer to take on the length of
 * 						the output array
 * @return				a heap-allocated array
 */
int* abundant_numbers(int n, int* len_ptr) {
	int* arr = NULL;
	int len = 0;
	for (int x=12; x<n; x++)
		if (is_abundant(x))
			arr = arr_append(arr, x, &len);
	*len_ptr = len;
	return arr;
}


/**
 * Checks if x is an abundant number (if the sum of its proper divisors
 * exceeds itself).
 * Note: All abundant numbers are divisible by either 2 or 5.
 * 
 * @param	x	the integer to check
 * @return		true or false
 */
bool is_abundant(int x) {
	if (x%2!=0 && x%5!=0)	// must be divisible by 2 or 5
		return false;
		
	int len;
	int* arr = proper_divisors(x, &len);
	int sum = 0;
	
	for (int i=0; i<len; i++) {
		sum += arr[i];
		if (sum > x)
			break;
	}
	free(arr);
	return (sum > x);
}


/**
 * Creates a boolean array wherein each index is a number from 1 to the
 * limit and each value represents whether that number can be written as
 * the sum of two abundant numbers.
 *
 * @param	arr		an array of abundant numbers
 * @param	len		the array's length
 * @param	limit	the limit (28123 in the problem text)
 * @return			a heap-allocated array of length limit
 */
bool* new_problem23_dict(int* arr, int len, int limit) {
	bool* dict = calloc(limit, sizeof(bool));
	for (int x=0; x<len; x++) {
		for (int y=x; y<len; y++) {
			int sum = arr[x] + arr[y];
			if (sum >= limit)
				continue;
			else	
				dict[sum] = true;
		}
	}
	return dict;
}
