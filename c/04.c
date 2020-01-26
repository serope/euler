/*
 * Project Euler
 * 04.c
 */
#include <stdio.h>
#include "euler.h"

int main() {
	int product;
	int largest = 0;
	for (int a=100; a<=999; a++) {
		for (int b=a; b<=999; b++) {
			product = a*b;
			if (is_palindromic_int(product) && product>largest)
				largest = product;
		}
	}
	printf("%d \n", largest);
	return 0;
}
