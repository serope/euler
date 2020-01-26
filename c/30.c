/*
 * Project Euler
 * 30.c
 */
#include <stdlib.h>
#include <stdio.h>
#include "euler.h"

bool has_problem30_property(int x);

int main() {
	int limit = 200000;
	int sum = 0;
	for (int x=2; x<limit; x++)
		if (has_problem30_property(x))
			sum += x;
	printf("sum: %d \n", sum);
	return 0;
}


/**
 * Returns true if x is the sum of its digits' 5th powers.
 * 
 * @param	x	the term to evaluate
 * @return		true or false
 */
bool has_problem30_property(int x) {
	int* arr = digits_of(x);
	int len = digit_count(x);
	int sum = 0;
	
	for (int i=0; i<len; i++) {
		sum += int_pow(arr[i], 5);
		if (sum > x)
			break;
	}
	
	free(arr);
	return (x == sum);
}
