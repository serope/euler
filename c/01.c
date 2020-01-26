/*
 * Project Euler
 * 01.c
 */
#include <stdio.h>

int main() {
	int sum = 0;
	for (int x=1; x<1000; x++)
		if (x%3==0 || x%5==0)
			sum += x;
	printf("sum: %d \n", sum);
	return 0;
}
