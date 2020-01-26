/*
 * Project Euler
 * 16.c
 */
#include <stdio.h>
#include "big.h"

int main() {
	big_t* x = big_new("2");
	big_t* y = big_pow_ui(x, 1000);
	
	big_print(y);
	printf("%d \n", big_sum_of_digits(y));
	
	big_destroy(x);
	big_destroy(y);
	return 0;
}
