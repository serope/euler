/*
 * Project Euler
 * 05.c
 */
#include <stdio.h>
#include <stdbool.h>

bool has_problem5_property(int x);

int main() {
	int x = 20;
	while (!has_problem5_property(x))
		x += 20;
	printf("%d \n", x);
	return 0;
}


/**
 * Checks whether x is divisible by the required divisors. x should
 * always be a multiple of 20, therefore making it divisible by 20, 10,
 * 5, 4, 2, and 1 by default.
 * 
 * @param	x	the term to test
 * @return		true or false
 */
bool has_problem5_property(int x) {
	int list[] = {19, 18, 17, 16, 14, 13, 11};
	int len = 7;
	for (int i=0; i<len; i++)
		if (x%list[i] != 0)
			return false;
	return true;
}
