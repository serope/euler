/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 32
 **********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "euler.h"

bool has_problem32_property(int* x);

int main() {
	//Prepare list
	int* list = NULL;
	int list_len = 0;
	
	//How many possible 1-9 pandigitals are there?
	int permutations = factorial(9);
	
	/*
	 * Generate every permutation, and if it satisfies the problem's
	 * conditions, append it to the list
	 */
	for (int p=0; p<permutations; p++) {
		int* x = nth_permutation_of_pandigital(p+1, 9);
		if (has_problem32_property(x)) {
			int product = 1000*x[5] + 100*x[6] + 10*x[7] + x[8];
			list = append(list, product, &list_len);
			print_pandigital(x, 9);
		}
		free(x);
	}
	
	
	//Replace repeating elements with 0
	for (int i=0; i<list_len-1; i++) {
		if (list[i]==0)
			continue;
		for (int m=i+1; m<list_len; m++) {
			if (list[i]==list[m]) {
				printf("remove an instance of %d \n", list[i]);
				list[m] = 0;
			}
		}
	}
	
	
	//Sum
	int sum = 0;
	for (int i=0; i<list_len; i++)
		sum += list[i];
	
	//End
	printf("sum:   %d \n", sum);
	free(list);
	return 0;
}




bool has_problem32_property(int* x) {
	/*
	 * This should be rewritten to perform in a loop
	 * Note: c is always 4 digits long
	 */
	
	//First product
	int a = x[0];
	int b = 1000*x[1] + 100*x[2] + 10*x[3] + x[4];
	int c = 1000*x[5] + 100*x[6] + 10*x[7] + x[8];
	if (a*b==c)
		return true;
	
	//Second product
	a = 10*x[0] + x[1];
	b = 100*x[2] + 10*x[3] + x[4];
	if (a*b==c)
		return true;
	
	//Third product
	a = 100*x[0] + 10*x[1] + x[2];
	b = 10*x[3] + x[4];
	if (a*b==c)
		return true;
	
	return false;
}

