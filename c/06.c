/*
 * Project Euler
 * 06.c
 */
#include <stdio.h>

int max = 100;

int main() {
	int sum = 0;				// sum of squares
	for (int x=1; x<=max; x++)
		sum += x*x;
	
	int square = 0;				// square of sum
	for (int x=1; x<=max; x++)
		square += x;
	square *= square;
	
	int diff = square-sum;		// end
	printf("%d \n", diff);
	return 0;
}
