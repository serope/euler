/*
 * Project Euler
 * 40.c
 */
#include <stdlib.h>
#include <stdio.h>
#include "euler.h"

int* champernowne(int max);

int main() {
	// generate
	int max = 1000000;
	int* arr = champernowne(max);
	
	// product
	int product = 1;
	int digit_no = 10;
	int i = digit_no-1;
	while (digit_no <= max) {
		product *= arr[i];
		digit_no *= 10;
		i = digit_no-1;
	}
	
	// end
	printf("%d \n", product);
	free(arr);
	return 0;
}


/**
 * Creates an array containing the digits of the fractional part of
 * Champernowne's constant.
 * 
 * @param	max			the amount of digits to generate up to
 * @return				a heap-allocated array
 */
int* champernowne(int max) {
	int* arr = calloc(max, sizeof(int));
	int x = 1;
	int i = 0;
	while (i < max) {
		int* digits = digits_of(x);
		int digits_len = digit_count(x);
		for (int j=0; j<digits_len; j++) {
			arr[i] = digits[j];
			i++;
			if (i == max)
				break;
		}
		free(digits);
		x++;
	}
	return arr;
}
