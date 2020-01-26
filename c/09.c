/*
 * Project Euler
 * 09.c
 */
#include <stdio.h>
#include "euler.h"

int main() {
	bool solved = false;
	for (int c=1; c<1000; c++) {
		if (solved)
			break;
		for (int b=1; b<c; b++) {
			if (solved)
				break;
			for (int a=1; a<b; a++) {
				if (is_pythagorean_triplet(a, b, c) && a+b+c==1000) {
					printf("a:      %d \n", a);
					printf("b:      %d \n", b);
					printf("c:      %d \n", c);
					printf("a*b*c:  %d \n", a*b*c);
					solved = true;
					break;
				}
			}
		}
	}
	return 0;
}
