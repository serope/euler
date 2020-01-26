/*
 * Project Euler
 * 08.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "euler.h"
#include "strings.h"


int* file_to_arr(const char* filename, int* len_ptr);
int64_t largest_product(int* arr, int len, int adjacency);


int main() {
	int len;
	int* digits = file_to_arr("08_digits", &len);
	
	int adjacency = 13;
	int64_t largest = largest_product(digits, len, 13);
	
	free(digits);
	print64(largest);
	printf("\n");
	return 0;
}


/**
 * Reads a file containing digits into an array of digits and saves its
 * length.
 * 
 * @param	filename	the digits file
 * @param	len_ptr		a pointer to an integer representing the length
 * 						of the output array
 * @return				a heap-allocated array
 */
int* file_to_arr(const char* filename, int* len_ptr) {
	char* text = file_to_string(filename, len_ptr);
	int* digits = calloc(*len_ptr, sizeof(int));
	for (int i=0; i < *len_ptr; i++)
		digits[i] = char_to_int(text[i]);
	free(text);
	return digits;
}


/**
 * Checks an array for the largest possible product formed by multiplying
 * adjacent digits.
 * 
 * @param	arr			an int array
 * @param	len			the array's length
 * @param	adjacency	the amount of adjacent digits to multiply
 * @return				the largest product
 */
int64_t largest_product(int* arr, int len, int adjacency) {
	int64_t largest = 0;
	for (int i=0; i<(len-adjacency)-1; i++) {
		int64_t product = 1;
		for (int j=0; j<adjacency; j++)
			product *= arr[i+j];
		if (product > largest)
			largest = product;
	}
	return largest;
}
