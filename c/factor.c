/*
 * Project Euler
 * factor.c
 */
#include "factor.h"


int* factors(int x, int* len_ptr) {
	// edge case
	if (x==1) {
		int* arr = malloc(sizeof(int));
		arr[0] = 1;
		return arr;
	}
	
	// upper = {x}
	int* upper = malloc(sizeof(int));
	int upper_len = 1;
	upper[0] = x;
	
	// lower = {1}
	int* lower = malloc(sizeof(int));
	int lower_len = 1;
	lower[0] = 1;
	
	// if odd, only check odd factors
	int factor, increment;
	if (x%2 == 0) {
		factor = 2;
		increment = 1;
	}
	else {
		factor = 3;
		increment = 2;
	}
	
	// factorize
	while (factor < arr_min(upper, upper_len)) {
		if (x%factor == 0) {
			lower = arr_append(lower, factor, &lower_len);
			if (factor*factor != x)
				upper = arr_append(upper, x/factor, &upper_len);
		}
		factor += increment;
	}
	
	// end
	int* arr = arr_merge(upper, upper_len, lower, lower_len);
	*len_ptr = upper_len+lower_len;
	free(upper);
	free(lower);
	return arr;
}


int factor_count(int x) {
	// edge case
	if (x==1)
		return 1;
	
	// upper = {x}
	int* upper = malloc(sizeof(int));
	upper[0] = x;
	int upper_len = 1;
	
	// if odd, only check odd factors
	int factor, increment;
	if (x%2 == 0) {
		factor = 2;
		increment = 1;
	}
	else {
		factor = 3;
		increment = 2;
	}
	
	// factorize
	int total = 0;
	while (factor < arr_min(upper, upper_len)) {
		if (x%factor == 0) {
			total += 1;
			if (factor*factor != x)
				upper = arr_append(upper, x/factor, &upper_len);
				total += 1;
		}
		factor += increment;
	}
	
	// end
	free(upper);
	return total;
}


int proper_divisor_count(int x) {
	if (x==1 || x==2 || x==3 || x==5 || x==7)
		return 1;
	return factor_count(x)-1;
}


int* proper_divisors(int x, int* len_ptr) {
	// factorize
	int len;
	int* arr = factors(x, &len);
	
	// find x
	int pos;
	for (int i=0; i<len; i++) {
		if (arr[i]==x) {
			pos = i;
			break;
		}
	}
	
	// remove x
	for (int i=pos; i < len-1; i++)
		arr[i] = arr[i+1];
	len--;
	size_t new_size = sizeof(int) * (len);
	arr = realloc(arr, new_size);
	*len_ptr = len;
	return arr;
}
