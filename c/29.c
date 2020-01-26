/*
 * Project Euler
 * 29.c
 * TODO: Get rid of compiler warnings about void* casts
 */
#include <stdio.h>
#include <stdlib.h>
#include "big.h"

int cmp(const void* a_ptr, const void* b_ptr);
big_t** append(big_t** arr, big_t* x, int* len_ptr);
void big_arr_free(big_t** arr, int len);

int main() {
	// init
	big_t** arr = NULL;
	int arr_len = 0;
	
	// generate every a^b
	for (unsigned int a=2; a<=100; a++) {
		for (unsigned int b=2; b<=100; b++) {
			// compute a^b = c
			big_t* a_big = big_new_ui(a);
			big_t* c = big_pow_ui(a_big, b);
			
			// append
			arr = append(arr, c, &arr_len);
			
			// free
			big_destroy(a_big);
			big_destroy(c);
		}
	}
	
	// sort
	qsort(arr, arr_len, sizeof(big_t*), cmp);
	
	// filter unique elements
	int unique_len;
	big_t** unique = arr_filter_repeats(arr, arr_len, big_cmp, big_copy,
															&unique_len);
	
	// end
	printf("distinct elements   %d \n", unique_len);
	printf("array arr_len       %d \n", arr_len);
	big_arr_free(arr, arr_len);
	big_arr_free(unique, unique_len);
	return 0;
}


/**
 * Copies a big into an existing array of bigs.
 * 
 * @param	arr			the array to append to
 * @param	x			the big to append
 * @param	len_ptr		a pointer to the array's length, which will be
 * 						incremented accordingly
 * @return				the array
 */
big_t** append(big_t** arr, big_t* x, int* len_ptr) {
	size_t new_size = sizeof(big_t*) * (*len_ptr + 1);
	arr = realloc(arr, new_size);
	arr[*len_ptr] = big_copy(x);
	*len_ptr += 1;
	return arr;
}


/**
 * Compares two bigs. This is a wrapper around big_cmp() so it can be
 * passed to qsort() without warnings.
 * 
 * @param	a	the first big
 * @param	b	the second big
 * @return		1 if a>b
 * 				0 if a==b
 * 				-1 if a<b
 */
int cmp(const void* a_ptr, const void* b_ptr) {
	big_t* a = *((big_t**) a_ptr);
	big_t* b = *((big_t**) b_ptr);
	return big_cmp(a, b);
}


/**
 * Frees an array of bigs.
 * 
 * @param	arr		an array of type big_t*
 * @param	len		the array's length
 */
void big_arr_free(big_t** arr, int len) {
	for (int i=0; i<len; i++)
		big_destroy(arr[i]);
	free(arr);
}
