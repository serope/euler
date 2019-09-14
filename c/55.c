/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 55
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "euler_bignum.h"

int main() {
	int total_lychrels = 0;
	
	for (int x=0; x<10000; x++) {
		/***************************************************************
		 * 1. Turn 'x' into a string
		 **************************************************************/
		char* x_str = malloc(sizeof(char));
		sprintf(x_str, "%d", x);
		
		
		/***************************************************************
		 * 2. Turn 'x_str' into a big
		 **************************************************************/
		big base = big_new(x_str);
		
		
		/***************************************************************
		 * 3. Perform the first iteration of the Lychrel sequence
		 **************************************************************/
		big lychrel = big_reverse(base);
		big_add(lychrel, base);
		int iterations = 1;
		
		
		/***************************************************************
		 * 4. Continue iterating until either...
		 * 
		 *    a) 'lychrel' becomes a palindrome
		 *    b) the 50th iteration has been reached
		 **************************************************************/
		while (true) {
			if (big_is_palindrome(lychrel))
				break;
			
			else if (iterations==50) {
				total_lychrels++;
				break;
			}
			
			iterations++;
			big reverse = big_reverse(lychrel);
			big_add(lychrel, reverse);
			BIG_FREE(reverse);
		}
		
		
		/***************************************************************
		 * 5. Cleanup and continue to the next 'x'
		 **************************************************************/
		free(x_str);
		BIG_FREE(lychrel);
		BIG_FREE(base);
	}
	
	printf("%d \n", total_lychrels);
}
