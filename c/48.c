/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 48
 **********************************************************************/
#include <stdio.h>
#include "euler_bignum.h"

int main() {
	/*******************************************************************
	 * 1. Add every number N^N where N goes from 1 to 1000 while
	 *    only considering the final 10 digits
	 * 
	 *    Note: All Ns which are multiples of 10 (10, 570, 1000, etc.)
	 *          end up being zero
	 ******************************************************************/
	big sum = big_new_1_digit(0);
	
	for (int n=1; n<=999; n++) {
		if (n%10==0)
			continue;
			
		big b;
		
		if (n<=9)
			b = big_new_1_digit(n);
		else if (n<=99)
			b = big_new_2_digits(n);
		else
			b = big_new_3_digits(n);
		
		
		big_pow_last_10_digits(b, n);
		big_add(sum, b);
		printf("n=%d \t n^n = ", n);
		big_print(b);
		
		BIG_FREE(b);
	}
	
	
	/*******************************************************************
	 * 2. Print the final 10 digits of the sum
	 ******************************************************************/
	int digits = sum->len;
	int index = digits-10;
	
	for (int i=index; i<digits; i++)
		printf("%d", sum->array[i]);
	
	
	
	/*******************************************************************
	 * 3. Cleanup and exit
	 ******************************************************************/
	BIG_FREE(sum);
	return 0;
}
