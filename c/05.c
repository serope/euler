/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 5
 **********************************************************************/
#include "euler.h"

int main() {
	/*******************************************************************
	 * Check every 'x' which is a multiple of 20.
	 * 
	 * When an 'x' that is divisible by 1, 2, 3, 4, ..., 20 is found,
	 * print it and exit.
	 ******************************************************************/
	int x = 20;
	
	while (!has_problem5_property(x))
		x += 20;
	
	printf("%d \n", x);
	return 0;
}
