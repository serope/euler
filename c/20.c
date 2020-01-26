/*
 * Project Euler
 * 20.c
 */
#include <stdio.h>
#include "big.h"

int main() {
	// x = 100!
	big_t* x = big_new("1");
	for (int i=1; i<=100; i++) {
		big_t* y = big_new_ui(i);
		big_t* z = big_mul_slow(x, y);
		big_destroy(x);
		x = big_copy(z);
		big_destroy(y);
		big_destroy(z);
	}
	
	big_print(x);
	printf("%d \n", big_sum_of_digits(x));
	big_destroy(x);
	return 0;
}
