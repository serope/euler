/*
 * Project Euler
 * 34.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "euler.h"
#include "array.h"

int* make_problem34_dict();
bool has_problem34_property(int x, int* dict);

int main() {
	// init
	int* arr = NULL;
	int len = 0;
	int limit = 99999;
	int* dict = make_problem34_dict();
	
	// solve
	for (int x=3; x<=limit; x++) {
		if (has_problem34_property(x, dict)) {
			printf("%d \n", x); 
			arr = arr_append(arr, x, &len);
		}
	}
	
	// end
	int sum = arr_sum(arr, len);
	printf("result: %d \n", sum);
	free(arr);
	free(dict);
	return 0;
}


/**
 * Generates an array in which each element is its index's factorial.
 * 
 * @return	a heap-allocated array
 */
int* make_problem34_dict() {
	int* dict = calloc(10, sizeof(int));
	dict[0] = factorial(0);
	dict[1] = factorial(1);
	dict[2] = factorial(2);
	dict[3] = factorial(3);
	dict[4] = factorial(4);
	dict[5] = factorial(5);
	dict[6] = factorial(6);
	dict[7] = factorial(7);
	dict[8] = factorial(8);
	dict[9] = factorial(9);
	return dict;
}


/**
 * Returns true if x is equal to the sum of its digits' factorials.
 * 
 * @param	x		the term to test
 * @param	dict	a map-esque array of factorials for every decimal
 * 					digit
 * @return			true or false
 */
bool has_problem34_property(int x, int* dict) {
	int* digits = digits_of(x);
	int digits_len = digit_count(x);
	int sum = 0;
	for (int i=0; i<digits_len; i++) {
		sum += dict[digits[i]];
		if (sum > x)
			break;
	}
	free(digits);
	return (sum == x);
}
