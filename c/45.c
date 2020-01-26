/*
 * Project Euler
 * 45.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "array.h"
#include "euler.h"


int64_t* triangular_numbers(int n, int limit, int64_t t);
int64_t* pentagonal_numbers(int n, int limit);
int64_t* hexagonal_numbers(int n, int limit);
int64_t nth_hexagonal_number(int n);
int cmp64(const void* a_ptr, const void* b_ptr);


int main() {
	/*
	 * Build lists of triangular, pengatonal, and hexagonal numbers that
	 * start at n=286, n=166, and n=144, respectively
	 * (100k is sufficient for this problem)
	 */
	int limit = 100000;
	int64_t t = 40755;
	int64_t* tri_list = triangular_numbers(286, limit, t);
	int64_t* pen_list = pentagonal_numbers(166, limit);
	int64_t* hex_list = hexagonal_numbers(144, limit);
	
	// search for a common number among all three lists
	int64_t number;
	bool solved = false;
	for (int t=0; t<limit; t++) {
		number = tri_list[t];
		if (arr_bsearch64(pen_list, limit, number)) {
			if (arr_bsearch64(hex_list, limit, number)) {
				solved = true;
				break;
			}
		}
	}
	
	// end
	printf("largest triangle:  "); print64(tri_list[limit-1]); printf("\n");
	printf("largest pentagon:  "); print64(pen_list[limit-1]); printf("\n");
	printf("largest hexagon:   "); print64(hex_list[limit-1]); printf("\n");
	if (solved)
		print64(number);
	else
		puts("The answer wasn't found (try increasing the limit)");
	free(tri_list);
	free(pen_list);
	free(hex_list);
	return 0;
}


/**
 * Generates a list of triangular numbers, starting with the nth
 * triangular number.
 * 
 * @param	n		the iteration to start at
 * @param	limit	the iteration to generate up to
 * @param	t		the nth triangular number
 * @return			a heap-allocated array of length limit
 */
int64_t* triangular_numbers(int n, int limit, int64_t t) {
	int64_t* arr = calloc(limit, sizeof(int64_t));
	int i = 0;
	while (i < limit) {
		t += n;
		arr[i] = t;
		i++;
		n++;
	}
	return arr;
}


/**
 * Generates a list of pentagonal numbers, starting with the nth
 * pentagonal number.
 * 
 * @param	n		the iteration to start at
 * @param	limit	the iteration to generate up to
 * @return			a heap-allocated array of length limit
 */
int64_t* pentagonal_numbers(int n, int limit) {
	int64_t* arr = calloc(limit, sizeof(int64_t));
	int i = 0;
	while (i < limit) {
		int64_t p = nth_pentagonal_number(n);
		arr[i] = p;
		i++;
		n++;
	}
	return arr;
}


/**
 * Generates a list of hexagonal numbers, starting with the nth
 * hexagonal number.
 * 
 * @param	n		the iteration to start at
 * @param	limit	the iteration to generate up to
 * @return			a heap-allocated array of length limit
 */
int64_t* hexagonal_numbers(int n, int limit) {
	int64_t* arr = calloc(limit, sizeof(int64_t));
	int i = 0;
	while (i < limit) {
		int64_t h = nth_hexagonal_number(n);
		arr[i] = h;
		i++;
		n++;
	}
	return arr;
}


/**
 * Compares two 64-bit integers.
 * 
 * @param	a_ptr	a pointer to the first term
 * @param	b_ptr	a pointer to the second term
 * @return			1 if a>b
 * 					-1 if a<b
 * 					0 if a==b
 */
int cmp64(const void* a_ptr, const void* b_ptr) {
	int64_t a = *((int64_t*) a_ptr);
	int64_t b = *((int64_t*) b_ptr);
	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	return 0;
}


/**
 * Computes the nth hexagonal number.
 * 
 * @param	n	the iteration to compute
 * @return		a 64-bit hexagonal number
 */
int64_t nth_hexagonal_number(int n) {
	int64_t h = 2*n-1;
	return h*n;
}
