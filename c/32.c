/*
 * Project Euler
 * 32.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "array.h"
#include "euler.h"
#include "pandigital.h"

bool has_problem32_property(pand_t* p);
int* clear_repeats(int* arr, int len);

int main() {
	// init
	int* arr = NULL;
	int len = 0;
	int limit = factorial(9);	// total possible permutations
	
	// find satisfying pandigitals
	for (int i=0; i<limit; i++) {
		pand_t* p = pand_permute_ith(i+1, 9);
		if (has_problem32_property(p)) {
			pand_print(p, 9);
			int prod = 1000*p[5] + 100*p[6] + 10*p[7] + p[8];
			arr = arr_append(arr, prod, &len);
		}
		pand_free(p);
	}
	
	// remove repeats
	arr = clear_repeats(arr, len);
	
	// end
	int sum = arr_sum(arr, len);
	printf("len   %d \n", len);
	printf("sum   %d \n", sum);
	free(arr);
	return 0;
}


/**
 * Checks whether the given pandigital has the property described in
 * problem 23; that is, whether its digits can form a valid 
 * multiplication equation. If the pandigital is abcdefghi, then at
 * least one of the following equations must hold true:
 * 		1.	a * bcde = fghi
 * 		2.	ab * cde = fghi
 * 		3.	abc * de = fghi
 * 		4.	abcd * e = fghi
 * 
 * @param	p	the pandigital to check
 * @return		true or false
 */
bool has_problem32_property(pand_t* p) {
	// 1
	int a = p[0];
	int b = 1000*p[1] + 100*p[2] + 10*p[3] + p[4];
	int c = 1000*p[5] + 100*p[6] + 10*p[7] + p[8];
	if (a*b==c)
		return true;
	
	// 2
	a = 10*p[0] + p[1];
	b = 100*p[2] + 10*p[3] + p[4];
	if (a*b==c)
		return true;
	
	// 3
	a = 100*p[0] + 10*p[1] + p[2];
	b = 10*p[3] + p[4];
	if (a*b==c)
		return true;
		
	// 4
	a = 1000*p[0] + 100*p[1] + 10*p[2] + p[3];
	b = p[4];
	if (a*b==c)
		return true;
	return false;
}


/**
 * Zeroes repeating nonzero elements from an array and returns it.
 * 
 * @param	arr		the array to be edited
 * @param	len		the array's length
 * @return			the array
 */
int* clear_repeats(int* arr, int len) {
	for (int i=0; i<len-1; i++) {
		if (arr[i]==0)
			continue;
		for (int j=i+1; j<len; j++) {
			if (arr[i]==arr[j]) {
				arr[j] = 0;
			}
		}
	}
	return arr;
}
