/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 5
 **********************************************************************/
#include <stdio.h>
#include <stdbool.h>

bool has_problem5_property(int x);

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



bool has_problem5_property(int x) {
	//'x' is always divisible by 20, 10, 5, 4, 2, and 1
	//Divisibility by 19
	if (x%19!=0)
		return false;
	
	//Divisibility by 18 (and thus 2, 3, 6, and 9)
	if (x%18!=0)
		return false;
	
	//Divisibility by 17
	if (x%17!=0)
		return false;
	
	//Divisibility by 16 (and thus 2, 4, and 8)
	if (x%16!=0)
		return false;
	
	//Divisibility by 14 (and thus 7)
	if (x%14!=0)
		return false;
	
	//Divisibility by 13
	if (x%13!=0)
		return false;
	
	//Divisibility by 11
	if (x%11!=0)
		return false;
	
	return true;
}

