/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 16
 **********************************************************************/
#include <stdio.h>
#include "euler_bignum.h"

int main() {
	//Compute 2^1000
	big x = big_new("2");
	big_pow(x, 1000);

	//Sum the digits
	int sum = big_sum_of_digits(x);
	
	//End
	big_print(x);
	printf("%d \n", sum);
	BIG_FREE(x);
	return 0;
}
