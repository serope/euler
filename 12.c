/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 12
 **********************************************************************/
#include "euler.h"

int main() {
	/*******************************************************************
	 * Prepare values
	 ******************************************************************/
	int triangle = 0;
	int factors = 0;
	int n = 0;
	
	
	/*******************************************************************
	 * Find a reasonable starting point for n
	 * (checking every nth triangular number from n=1 is unnecessary)
	 ******************************************************************/
	while (factors < 500) {
		n += 100;
		triangle = nth_triangular_number(n);
		factors = factor_count(triangle);
	}
	n = n/2;
	
	
	/*******************************************************************
	 * Find the triangular number requested by the problem
	 ******************************************************************/
	triangle = 0;
	factors = 0;
	
	while (factors < 500) {
		n++;
		triangle = nth_triangular_number(n);
		factors = factor_count(triangle);
	}
	
	printf("triangle     %d \n", triangle);
	printf("factors      %d \n", factors);
	printf("n            %d \n", n);
	return 0;
}
