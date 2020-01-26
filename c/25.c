/*
 * Project Euler
 * 25.c
 */
#include <stdio.h>
#include "euler.h"
#include "big.h"

int fibonacci_index_n_digit(int n);

int main() {
	int n = 1000;
	int i = fibonacci_index_n_digit(n);
	printf("%d \n", i);
	return 0;
}


/**
 * Determines the index of the first Fibonacci number to have n digits.
 * 
 * @param	n	the target digit count
 * @return		the index
 */
int fibonacci_index_n_digit(int n) {
	big_t* x = big_new("1");
	big_t* y = big_new("2");
	int i = 3;
	while (x->len < n) {
		big_pluseq(&x, y);
		if (x->len >= n) {
			i += 1;
			break;
		}
		else {
			big_pluseq(&y, x);
			i += 2;
		}
	}
	big_destroy(x);
	big_destroy(y);
	return i;
}
