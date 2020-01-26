/*
 * Project Euler
 * 36.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "euler.h"
#include "binary.h"

bool has_problem36_property(int x);
bool int_is_palindrome(int x);


int main() {
	// init
	int lim = 1000000;
	int* arr = NULL;
	int len = 0;
	
	// find terms
	for (int i=1; i<lim; i++)
		if (has_problem36_property(i))
			arr = arr_append(arr, i, &len);
	
	// end
	arr_print(arr, len);
	printf("sum %d \n", arr_sum(arr, len));
	free(arr);
	return 0;
}


/**
 * Returns true if x is a palindrome in both base 10 and base 2.
 * 
 * @param	x	the term to check
 * @return		true or false
 */
bool has_problem36_property(int x) {
	// base 10
	if (!int_is_palindrome(x))
		return false;
	
	// base 2
	int len;
	bin_t* bin = bin_new(x, &len);
	bool is_palindrome = arr_is_palindrome((int*) bin, len);
	bin_free(bin);
	return is_palindrome;
}


/**
 * Returns true if x is a palindrome.
 * 
 * @param	x	the term to check
 * @return		true or false
 */
bool int_is_palindrome(int x) {
	int* arr = digits_of(x);
	int len = digit_count(x);
	bool is_palindrome = arr_is_palindrome(arr, len);
	free(arr);
	return is_palindrome;
}
