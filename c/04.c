/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 4
 **********************************************************************/
#include "euler.h"

int main() {
	int product;
	int largest = 0;
	
	/*******************************************************************
	 * Multiply every 3-digit number (every number from 100 to 999) with
	 * every other 3-digit number.
	 * 
	 * Pick out the largest one which returns true from the other
	 * function.
	 ******************************************************************/
	for (int a=100; a<=999; a++)
		for (int b=a; b<=999; b++) {
			product = a*b;
			
			if (is_palindromic_int(product) && product>largest)
				largest = product;
		}
	
	printf("%d \n", largest);
	return 0;
}
