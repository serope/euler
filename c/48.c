/*
 * Project Euler
 * 48.c
 */
#include <stdio.h>
#include <string.h> // for memcpy()
#include "big.h"

void big_resize(big_t** x_ptr, int n);
big_t* big_pow_p48(big_t* x, unsigned int ui, int n);

int main() {
	// compute 1^1 + 2^2 + ... + 1000^1000
	big_t* sum = big_new("0");
	for (int n=1; n <= 1000; n++) {
		big_t* x = big_new_ui(n);				// x = n
		big_t* y = big_pow_p48(x, n, 10);		// y = x^n
		big_pluseq(&sum, y);					// sum += y
		big_destroy(x);
		big_destroy(y);
	}
	
	// end
	big_resize(&sum, 10);
	big_print(sum);
	big_destroy(sum);
	return 0;
}


/**
 * Resizes the internal array of the given bignum so that it consists
 * of only the final n digits.
 * 
 * @param	x_ptr		a pointer to the bignum to be modified
 * @param	n			the new length of the internal array
 */
void big_resize(big_t** x_ptr, int n) {
	big_t* x = *x_ptr;
	if (x->len <= n)
		return;
	size_t new_size = sizeof(short int) * n;
	x->arr = realloc(x->arr, new_size);
	x->len = n;
}


/**
 * Computes x^ui while constantly resizing x so that it never exceeds n
 * digits.
 * 
 * @param	x	the base
 * @param	ui	the exponent
 * @param	n	the result's maximum digit length
 * @return		x^ui
 */
big_t* big_pow_p48(big_t* x, unsigned int ui, int n) {
	// edge cases
	if (ui == 0)
		return big_new("1");
	else if (ui == 1)
		return big_copy(x);
	else if (big_is_zero(x))
		return big_new("0");
	
	// x^ui = y
	big_t* y = big_copy(x);
	for (int p=0; p<ui-1; p++) {
		big_t* m = big_mul_slow(y, x);
		big_resize(&m, n);
		big_destroy(y);
		y = big_copy(m);
		big_destroy(m);
	}
	return y;
}
