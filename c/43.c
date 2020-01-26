/*
 * Project Euler
 * 43.c
 * TODO: Rewrite this using dynamic programming
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "array.h"
#include "euler.h"
#include "pandigital.h"


int** new_problem43_list(int divisor, int* len_ptr);
int* prepend_zero(int* arr);
bool has_problem43_match(int* seq1, int* seq2);
bool has_repeats(int* set , int set_len);
bool has_common_element(int* arr1, int len1, int* arr2, int len2);


int main() {
	/*
	 * Generate arrays of 3-digit sequences whose integer forms are
	 * divisible by 2, 3, 5, etc.
	 */
	int len2, len3, len5, len7, len11, len13, len17;
	int** list2		= new_problem43_list(2, &len2);
	int** list3		= new_problem43_list(3, &len3);
	int** list5		= new_problem43_list(5, &len5);
	int** list7		= new_problem43_list(7, &len7);
	int** list11	= new_problem43_list(11, &len11);
	int** list13	= new_problem43_list(13, &len13);
	int** list17	= new_problem43_list(17, &len17);
	
	/*
	 * Try combining every term from every list into a pandigital
	 * sequence as shown in the example.
	 * 
	 * If the combination is a valid pandigital, add its integer form
	 * to the sum.
	 */
	int lists_len = 7;
	int64_t sum = 0;
	for (int i2=0; i2<len2; i2++) {
		int* x2 = list2[i2];
		
		for (int i3=0; i3<len3; i3++) {
			int* x3 = list3[i3];
			if (has_problem43_match(x2, x3))
				continue;
			
			for (int i5=0; i5<len5; i5++) {
				int* x5 = list5[i5];
				if (has_problem43_match(x3, x5))
					continue;
				
				for (int i7=0; i7<len7; i7++) {
					int* x7 = list7[i7];
					if (has_problem43_match(x5, x7))
						continue;
					
					for (int i11=0; i11<len11; i11++) {
						int* x11 = list11[i11];
						if (has_problem43_match(x7, x11))
							continue;
						
						for (int i13=0; i13<len13; i13++) {
							int* x13 = list13[i13];
							if (has_problem43_match(x11, x13))
								continue;
								
							for (int i17=0; i17<len17; i17++) {
								int* x17 = list17[i17];
								if (has_problem43_match(x13, x17))
									continue;
								
								/*
								 * Form the last 9 digits of the
								 * pandigital sequence as shown in the
								 * example
								 */
								pand_t* pan = calloc(10, sizeof(int));
								pan[1] = x2[0];
								pan[2] = x2[1];
								pan[3] = x2[2];
								pan[4] = x7[0];
								pan[5] = x7[1];
								pan[6] = x7[2];
								pan[7] = x17[0];
								pan[8] = x17[1];
								pan[9] = x17[2];
								
								// Fill in the missing 1st digit
								for (int i=0; i<10; i++) {
									if (arr_bsearch(pan, 10, i))
										continue;
									else {
										pan[0] = i;
										break;
									}
								}
								
								/*
								 * If any digits repeat, then this is
								 * NOT a valid pandigital
								 */
								if (has_repeats(pan, 10)) {
									pand_free(pan);
									continue;
								}
								
								// add to sum
								pand_print(pan, 10);
								int64_t x = pand_to_int(pan, 10);
								sum += x;
								pand_free(pan);
							}
						}
					}
				}
			}
		}
	}
	
	// end
	arr_free_full(list2, len2);
	arr_free_full(list3, len3);
	arr_free_full(list5, len5);
	arr_free_full(list7, len7);
	arr_free_full(list11, len11);
	arr_free_full(list13, len13);
	arr_free_full(list17, len17);
	printf("sum: %lld \n", sum);
	return 0;
}


/**
 * Returns true if two 3-digit sequences can't be used to form a
 * pandigital as described in the problem text.
 * 
 * @param	seq1	the first sequence
 * @param	seq2	the second sequence
 * @return			true or false
 */
bool has_problem43_match(int* seq1, int* seq2) {
	if (seq1[1] != seq2[0] || seq1[2] != seq2[1])
		return true;
	return false;
}


/**
 * Returns true if an array has a repeating element.
 * 
 * @param	arr		the array to check
 * @param	len		the array's length
 * @return			true or false
 */
bool has_repeats(int* arr , int len) {
	for (int i=0; i<len-1; i++)
		for (int j=i+1; j<len; j++)
			if (arr[i] == arr[j])
				return true;
	return false;
}


/**
 * Returns true if two int arrays share a common element.
 * 
 * @param	arr1	the first array
 * @param	len1	the first array's length
 * @param	arr2	the second array
 * @param	len2	the second array's length
 * @return			true or false
 */
bool has_common_element(int* arr1, int len1, int* arr2, int len2) {
	for (int i=0; i<len1; i++)
		for (int j=0; j<len2; j++)
			if (arr1[i]==arr2[j])
				return true;
	return false;
}


/**
 * Creates an array of 3-digit sequences which are divisible by the given
 * divisor. It should later be freed with arr_free_full().
 * 
 * @param	divisor		the number that every sequence will be divisible
 * 						by
 * @param	len_ptr		a pointer to an integer to take on the length of
 * 						the output array
 * @return				a heap-allocated array (of heap-allocated arrays)
 */
int** new_problem43_list(int divisor, int* len_ptr) {
	int** list = NULL;
	if (*len_ptr != 0)
		*len_ptr = 0;
	
	for (int x=12; x<=999; x++) {
		if (x%divisor == 0) {
			// digits
			int* digits = digits_of(x);
			int len = digit_count(x);
			if (has_repeats(digits, len)) {
				free(digits);
				continue;
			}

			// prepend 0 if only 2 digits
			if (len == 2)
				digits = prepend_zero(digits);
			
			// append to list
			size_t new_size = sizeof(int*) * (*len_ptr + 1);
			list = realloc(list, new_size);
			list[*len_ptr] = digits;
			*len_ptr += 1;
		}
	}
	return list;
}


/**
 * Prepends a zero to a 2-element array.
 * 
 * @param	arr		the array to modify
 * @return			the array, after it has been modified
 */
int* prepend_zero(int* arr) {
	size_t new_size = sizeof(int) * 3;
	arr = realloc(arr, new_size);
	arr[2] = arr[1];
	arr[1] = arr[0];
	arr[0] = 0;
	return arr;
}
