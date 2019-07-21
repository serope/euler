/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 34
 **********************************************************************/
#include "euler.h"


int main() {
	/*******************************************************************
	 * 1. Prepare the list
	 ******************************************************************/
	int* list = NULL;
	int list_len = 0;
	
	
	
	/*******************************************************************
	 * 2. For every 'x' from 3 to the limit, check if it's equal to the
	 *    summed factorials of its digits
	 * 
	 *    If it is, then record it on the list
	 ******************************************************************/
	int limit = 999999;
	
	for (int x=3; x<=limit; x++) {
		/***************************************************************
		 * 2a. Create the list of digits of 'x'
		 **************************************************************/
		int* list_of_digits = digits_of(x);
		int list_of_digits_len = digit_count(x);
		
		
		/***************************************************************
		 * 2b. Add every digit's factorial
		 **************************************************************/
		int sum = 0;
		for (int l=0; l<list_of_digits_len; l++)
			sum += factorial(list_of_digits[l]);
		
		
		/***************************************************************
		 * 2c. If 'x' and the sum are the same, put 'x' on the list
		 **************************************************************/
		if (x==sum) {
			printf("%d! \n", x);
			list = append(list, x, &list_len);
		}
		
		
		/***************************************************************
		 * 2d. Free the list and continue
		 **************************************************************/
		free(list_of_digits);
	}
	
	
	
	
	/*******************************************************************
	 * 3. Sum every item on the list
	 ******************************************************************/
	int sum = 0;
	for (int l=0; l<list_len; l++)
		sum += list[l];
		
	
	
	/*******************************************************************
	 * 4. Print, free memory, and exit
	 ******************************************************************/
	printf("result:    %d \n", sum);
	free(list);
	return 0;
}
