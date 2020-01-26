/*
 * Project Euler
 * 38.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "euler.h"
#include "pandigital.h"

bool has_problem38_property(int* arr, int arr_len);
int* compute_products(int x, int* len_ptr);

int main() {
	int lim = 9999;
	int largest = 0;
	
	for (int x=1; x<lim; x++) {
		int len;
		int* arr = compute_products(x, &len);
		if (has_problem38_property(arr, len)) {
			arr_print(arr, len);
			int cat = arr_cat_elems(arr, len);
			if (cat > largest)
				largest = cat;
		}
		free(arr);
	}
	
	printf("%d \n", largest);
	return 0;
}


/**
 * Returns true if a series of products, as described in the problem
 * text, are able to be concatenated into a 9-digit pandigital.
 * 
 * @param	arr			an array of products
 * @param	arr_len		the array's length
 * @return				true or false
 */
bool has_problem38_property(int* arr, int arr_len) {
	if (!arr)	// compute_products() failed
		return false;
	int cat = arr_cat_elems(arr, arr_len);
	bool result = false;
	if (is_pand(cat))
		result = true;
	return result;
}


/**
 * Computes a series of products x*1, x*2, ... x*n until the total digits
 * in the series reaches 9. If the series exceeds 9 digits, null is
 * returned.
 * 
 * @param	x			the base term
 * @param	len_ptr		a pointer to an integer that will take on the
 * 						output array's length
 * @return				a heap-allocated array of products, or NULL
 */
int* compute_products(int x, int* len_ptr) {
	// arr = {x}
	int* arr = malloc(sizeof(int));
	arr[0] = x;
	*len_ptr = 1;
	int total_digits = digit_count(x);
	
	// multiply x*2, x*3, ... x*n
	int n = 2;
	while (total_digits < 9) {
		int prod = x*n;
		total_digits += digit_count(prod);
		arr = arr_append(arr, prod, len_ptr);
		n++;
	}
	
	// end
	if (total_digits != 9) {
		free(arr);
		arr = NULL;
	}
	return arr;
}
