/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 23
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "euler.h"

int main() {
	/*******************************************************************
	 * 1. Create a list of every abundant number between 1 and the
	 *    limit
	 * 
	 *    Note: All abundant numbers are divisible by either 2 or 5
	 ******************************************************************/
	int limit		= 28123;
	int* abundant	= NULL;
	int len			= 0;
	
	for (int x=12; x<limit; x++) {
		if ((IS_DIVISIBLE(x,2) || IS_DIVISIBLE(x,5)) && is_abundant(x))
			abundant = append(abundant, x, &len);
	}

	

	/*******************************************************************
	 * 2. Create a boolean list in which each index represents a number
	 *    from 1 to the limit and each value represents whether or not
	 *    that number is the sum of two abundant numbers
	 * 
	 *    Example: If 253 is the sum of two abundant numbers, then
	 *             list[253] = true
	 ******************************************************************/
	bool list[limit];
	for (int i=0; i<limit; i++)
		list[i] = false;
		
	for (int x=0; x<len; x++)
		for (int y=x; y<len; y++) {
			int sum = abundant[x] + abundant[y];
			
			if (sum >= limit)
				break;
			else	
				list[sum] = true;
		}
	
	
	
	/*******************************************************************
	 * 3. Sum every index on the list whose value is 'false'
	 ******************************************************************/
	int sum = 0;
	for (int i=0; i<limit; i++)
		if (list[i]==false)
			sum += i;
			
	
	/*******************************************************************
	 * 4. Print, cleanup, and exit
	 ******************************************************************/
	printf("%d \n", sum);
	free(abundant);
	return 0;
}
