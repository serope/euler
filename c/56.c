/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 56
 **********************************************************************/
#include <stdio.h>
#include "euler_bignum.h"

int main() {
	int max_sum = 0;
	
	for (int a=2; a<=99; a++) {
		if (a%10==0)
			continue;
		
		big big_a;
		if (a<=9)
			big_a = big_new_1_digit(a);
		else
			big_a = big_new_2_digits(a);
		
		for (int b=2; b<=a; b++) {
			big pow = big_new_1_digit(1);
			big_copy(big_a, pow);
			big_pow(pow, b);
			
			int sum = big_sum_of_digits(pow);
			
			if (sum > max_sum) {
				printf("a^b = %d^%d -> %d \n", a, b, sum);
				max_sum = sum;
			}
			
			BIG_FREE(pow);
		}
		
		BIG_FREE(big_a);
	}
	
	printf("%d \n", max_sum);
	return 0;
}
