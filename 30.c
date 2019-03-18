/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 30
 **********************************************************************/
#include "euler.h"

#define LIMIT          9999999
#define POW_5(x)       x*x*x*x*x


int main() {
	int* set = NULL;
	int set_len = 0;
	
	/*******************************************************************
	 * 1. Find every number between 2 and the limit which is the sum
	 *    of the 5th power of its digits
	 ******************************************************************/
	for (int x=2; x<LIMIT; x++) {
		/***************************************************************
		 * A. Prepare the set of x's digits
		 **************************************************************/
		int* digits = NULL;
		int digits_len = 0;
		
		
		/***************************************************************
		 * B. Get the digits
		 **************************************************************/
		int digit_column = (LIMIT+1)/10;
		int current_digit;
		
		while (digit_column>0) {
			/***********************************************************
			 * a. Get the current digit
			 **********************************************************/
			current_digit = x/digit_column - 10*(x/(digit_column*10));
			
			
			/***********************************************************
			 * b. If the digit is NOT zero, add it to 'digits'
			 **********************************************************/
			if (current_digit!=0)
				digits = append(digits, current_digit, &digits_len);
			
			
			/***********************************************************
			 * c. Proceed to the next digit column
			 **********************************************************/
			digit_column = digit_column/10;
			
		}
		
		
		/***************************************************************
		 * C. Sum the 5th power of each digit from step B
		 **************************************************************/
		int sum = 0;
		for (int d=0; d<digits_len; d++)
			sum += POW_5(digits[d]);
			
		
		
		/***************************************************************
		 * D. Put the sum in 'set' if it meets the problem's criteria
		 **************************************************************/
		if (sum==x) {
			printf("%d \n", x);
			set = append(set, x, &set_len);
		}
		
		
		/***************************************************************
		 * E. Cleanup and continue
		 **************************************************************/
		free(digits);
	}
	
	
	
	/*******************************************************************
	 * 2. Add the numbers that were gathered in step 1
	 ******************************************************************/
	int solution = 0;
	
	for (int x=0; x<set_len; x++)
		solution += set[x];



	/*******************************************************************
	 * 3. Print, free memory, and exit
	 ******************************************************************/
	printf("solution: %d \n", solution);
	free(set);
	return 0;
}
