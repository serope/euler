/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 28
 **********************************************************************/
#include <stdio.h>


int main() {
	/*******************************************************************
	 * When a spiral of numbers is uncurled, it's merely a list of
	 * numbers.
	 * 
	 * To find the sum of every corner point 'x' within the spiral,
	 * starting at the center point:
	 *  
	 * 1. Add the current point ('x') to the sum
	 * 2. Jump forward a certain amount ('jump') of spaces from
	 *    the current point
	 * 3. Repeat until 4 jumps have been made, then 
	 *    increase 'jump' by 2
	 * 
	 * Repeat the above process until 'x' is equal to the top-right
	 * outermost corner of the 1001*1001 spiral.
	 ******************************************************************/
	int x			= 1;
	int sum			= 0;
	int jump		= 2;
	int jumps_made	= 0;
	int limit		= 1001*1001;
	
	while (x < limit) {
		sum += x;
		x += jump;
		
		jumps_made += 1;
		
		if (jumps_made==4) {
			jumps_made = 0;
			jump += 2;
		}
	}
	
	sum += x;
	printf("%d \n", sum);
	
	return 0;
}
