/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 20
 **********************************************************************/
#include "euler_bignum.h"

int main() {
	/*******************************************************************
	 * 1. Prepare the base 'hundred_factorial'
	 ******************************************************************/
	big hundred_factorial = big_new_1_digit(1);
	
	
	/*******************************************************************
	 * 2. For every 'x' between 1 and 100, multiply the base by it
	 ******************************************************************/
	for (int x=1; x<=100; x++) {
		big multiplier;
		
		if (x<=9)
			multiplier = big_new_1_digit(x);
		else if (x<=99)
			multiplier = big_new_2_digits(x);
		else
			multiplier = big_new_3_digits(x);
		
		big_multiply(hundred_factorial, multiplier);
		
		BIG_FREE(multiplier);
	}
	
	
	/*******************************************************************
	 * 3. Sum every digit
	 ******************************************************************/
	int sum = big_sum_of_digits(hundred_factorial);
	
	
	/*******************************************************************
	 * 4. Print, cleanup, and exit
	 ******************************************************************/
	big_print(hundred_factorial);
	printf("%d \n", sum);
	BIG_FREE(hundred_factorial);
	return 0;
}
