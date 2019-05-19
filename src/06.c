/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 6
 **********************************************************************/
#include <stdio.h>

int max = 100;

int main() {
	int sum_of_squares = 0;
	for (int x=0; x<max+1; x++)
		sum_of_squares += x*x;
	
	int square_of_sum = 0;
	for (int x=0; x<max+1; x++)
		square_of_sum += x;
	square_of_sum *= square_of_sum;
	
	int difference = square_of_sum - sum_of_squares;
	
	printf("%d \n", difference);
	
	return 0;
}
