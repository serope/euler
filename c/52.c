/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 52
 **********************************************************************/
#include <stdio.h>
#include "euler.h"

int main() {
	int x, x2, x3, x4, x5, x6;
	
	for (int y=1; y<9999999; y++) {
		x = y;
		x2 = y*2;
		x3 = y*3;
		x4 = y*4;
		x5 = y*5;
		x6 = y*6;

		if (!is_permutation(x, x2))
			continue;
		else if (!is_permutation(x, x3))
			continue;
		else if (!is_permutation(x, x4))
			continue;
		else if (!is_permutation(x, x5))
			continue;
		else if (!is_permutation(x, x6))
			continue;
		else
			break;
	}
	
	printf("x  \t %d \n", x);
	printf("2x \t %d \n", x2);
	printf("3x \t %d \n", x3);
	printf("4x \t %d \n", x4);
	printf("5x \t %d \n", x5);
	printf("6x \t %d \n", x6);
	return 0;
}
