/*
 * Project Euler
 * 13.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "big.h"
#include "strings.h"

big_t** bigs_from_file(const char* filename, int* len_ptr);
big_t* big_sum(big_t** arr, int len);
void free_bigs(big_t** arr, int len);

int main() {
	// read
	int arr_len;
	big_t** arr = bigs_from_file("13_bignums", &arr_len);
	
	// sum
	big_t* sum = big_sum(arr, arr_len);
	printf("sum: ");
	big_print(sum);
	
	// end
	free_bigs(arr, arr_len);
	big_destroy(sum);
	return 0;
}


/**
 * Returns an array of bignums from a file of newline-separated bignums.
 * 
 * @param	filename	the file to open
 * @param	len_ptr		a pointer to an integer to take on the length
 * 						of the output array
 * @return				an array of type big_t*
 */
big_t** bigs_from_file(const char* filename, int* len_ptr) {
	// read
	int file_len;
	char* file = file_to_string(filename, &file_len);
	
	// split
	int lines_len;
	char** lines = string_split(file, file_len, '\n', &lines_len);
	
	// create array of bigs
	int arr_len = lines_len-1;		// ignore final line (empty newline)
	big_t** arr = calloc(arr_len, sizeof(big_t*));
	for (int i=0; i<arr_len; i++)
		arr[i] = big_new(lines[i]);
	
	// end
	free(file);
	free_string_split(lines, lines_len);
	*len_ptr = arr_len;
	return arr;
}


/**
 * Computes the sum of an array of bignums.
 * 
 * @param	arr		an array of bignums
 * @param	len		the array's length
 * @return			the bignums' sum
 */
big_t* big_sum(big_t** arr, int len) {
	big_t* sum = big_new("0");
	for (int i=0; i<len; i++)
		big_pluseq(&sum, arr[i]);
	return sum;
}


/**
 * Frees an array of bignums.
 * 
 * @param	arr		an array of bignums
 * @param	len		the array's length
 */
void free_bigs(big_t** arr, int len) {
	for (int i=0; i<len; i++)
		big_destroy(arr[i]);
	free(arr);
}
