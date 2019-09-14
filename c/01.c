/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 1
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "euler.h"

int main() {
	/*******************************************************************
	 * 1. Prepare a set of every multiple of 3 or 5 that exists between
	 *    1 and 1000
	 ******************************************************************/
	int* multiples = NULL;
	int length = 0;
	
	for (int x=1; x<1000; x++)
		if (x%3==0 || x%5==0)
			multiples = append(multiples, x, &length);
	
	
	/*******************************************************************
	 * 2. Sum them
	 ******************************************************************/
	int sum = 0;
	for (int x=0; x<length; x++)
		sum += multiples[x];
	
	
	/*******************************************************************
	 * 3. Print, free memory, and exit
	 ******************************************************************/
	printf("sum: %d \n", sum);
	free(multiples);
	exit(EXIT_SUCCESS);
}
