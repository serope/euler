/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 32
 **********************************************************************/
#include "euler.h"

int main() {
	/*******************************************************************
	 * 1. Prepare the list
	 ******************************************************************/
	int* list = NULL;
	int list_len = 0;
	
	
	/*******************************************************************
	 * 2. How many possible pandigitals (1-9) are there?
	 ******************************************************************/
	int permutations = factorial(9);
	
	
	/*******************************************************************
	 * 3. Generate every possible permutation, and if it satisfies
	 *    the problem's condition, append it to the list
	 ******************************************************************/
	for (int p=0; p<permutations; p++) {
		int* x = nth_permutation_of_pandigital(p+1, 9);
		if (has_problem32_property(x)) {
			int product = 1000*x[5] + 100*x[6] + 10*x[7] + x[8];
			list = append(list, product, &list_len);
			print_pandigital(x, 9);
		}
		free(x);
	}
	
	
	/*******************************************************************
	 * 3. If any item on the list has a repeat, replace the repeat with
	 *    zero
	 * 
	 *    For every item list[i], check the list[m] that comes after it
	 *    If list[m] is the same, change it to zero
	 ******************************************************************/
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
	
	
	/*******************************************************************
	 * 4. Sum the remaining items
	 ******************************************************************/
	int sum = 0;
	for (int i=0; i<list_len; i++)
		sum += list[i];
	
	
	/*******************************************************************
	 * 5. Print, free memory, and exit
	 ******************************************************************/
	printf("sum:   %d \n", sum);
	free(list);
	return 0;
}
