/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 25
 **********************************************************************/
#include "euler_bignum.h"

int main() {
	/*******************************************************************
	 * 1. Prepare the Fibonacci sequence
	 ******************************************************************/
	big x = big_new("1");
	big y = big_new("2");
	int fibonacci_index = 3;
	
	
	/*******************************************************************
	 * 2. Continuously generate Fibonacci numbers until 'x' has 1000
	 *    digits
	 ******************************************************************/
	while (x->len < 1000) {
		big_add(x, y);
		
		if (x->len >= 1000) {
			fibonacci_index += 1;
			break;
		}
		
		else {
			big_add(y, x);
			fibonacci_index += 2;
		}
	}
	
	
	/*******************************************************************
	 * 3. Print, free memory, and exit
	 ******************************************************************/
	printf("%d \n", fibonacci_index);
	BIG_FREE(x);
	BIG_FREE(y);
	return 0;
}
