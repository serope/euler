/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 2
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "euler.h"

int main() {
	/*******************************************************************
	 * 1. Initialize the set of Fibonacci numbers
	 ******************************************************************/
	int* fibonacci = calloc(2, sizeof(int));
	int fibonacci_len = 2;
	
	fibonacci[0] = 1;
	fibonacci[1] = 2;
	
	
	/*******************************************************************
	 * 2. Generate the Fibonacci numbers 
	 *    If the current one is even, add it to the sum
	 *    Break when the sum reaches 4,000,000
	 ******************************************************************/
	int limit = 4000000;
	int sum = 2;
	
	while (sum < limit) {
		int index_a = fibonacci_len-2;
		int index_b = fibonacci_len-1;
		int current = fibonacci[index_a] + fibonacci[index_b];
		
		fibonacci = append(fibonacci, current, &fibonacci_len);
		
		if (IS_EVEN(current))
			sum += current;
	}
	
	
	/*******************************************************************
	 * 3. Print, free memory, and exit
	 ******************************************************************/
	printf("sum              %d \n", sum);
	printf("fibonacci_len    %d \n", fibonacci_len);
	free(fibonacci);
	return 0;
}
