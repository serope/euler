/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 9
 **********************************************************************/
#include <stdio.h>
#include "euler.h"

int main() {
	for (int a=1; a<1000-2; a++) {
		for (int b=a+1; b<1000-1; b++) {
			for (int c=b+1; c<1000; c++) {
				if (is_pythagorean_triplet(a, b, c) && a+b+c==1000) {
					printf("a:      %d \n", a);
					printf("b:      %d \n", b);
					printf("c:      %d \n", c);
					printf("a*b*c:  %d \n", a*b*c);
					return 0;
				}
			}
		}
	}
	return 0;
}
