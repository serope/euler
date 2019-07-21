/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 29
 **********************************************************************/
#include "euler_bignum.h"

int main() {
	/*******************************************************************
	 * 1. Prepare the list of big integers
	 ******************************************************************/
	big* list = NULL;
	int list_len = 0;
	
	
	/*******************************************************************
	 * 2. Compute every possible value of a^b, where a goes from 2 to
	 *    100 and b also goes from 2 to 100
	 * 
	 *    Put each result on the list
	 ******************************************************************/
	for (int a=2; a<=100; a++)
		for (unsigned int b=2; b<=100; b++) {
			/***********************************************************
			 * Prepare the base
			 **********************************************************/
			big x;
			if (a<=9)
				x = big_new_1_digit(a);
			else if (a<=99)
				x = big_new_2_digits(a);
			else
				x = big_new_3_digits(a);
			
			
			/***********************************************************
			 * Perform the calculation
			 **********************************************************/
			big_pow(x, b);
			
			
			/***********************************************************
			 * Add the result to the list
			 **********************************************************/
			list = (big*) realloc(list, sizeof(big) * (list_len+1) );
			list[list_len] = big_new(NULL);
			big_copy(x, list[list_len]);
			list_len++;
			
			
			/***********************************************************
			 * Free the current instance of 'x' and repeat
			 **********************************************************/
			BIG_FREE(x);
		}
	
	
	
	/*******************************************************************
	 * 3. Replace all repeating terms with zero.
	 * 
	 *    For every item list[l], check every item list[m] that comes
	 *    after it.
	 *    If list[l] and list[m] are equal, then set list[m] as zero.
	 ******************************************************************/
	for (int l=0; l<list_len-1; l++)
		for (int m=l+1; m<list_len; m++)
			if (big_equals(list[l], list[m])) {
				BIG_FREE(list[m]);
				list[m] = big_new_1_digit(0);
			}
	
	
	/*******************************************************************
	 * 4. Count how many items on the list are NOT zero.
	 ******************************************************************/
	int total = 0;
	big zero = big_new_1_digit(0);
	
	for (int l=0; l<list_len; l++)
		if (!big_equals(list[l], zero))
			total += 1;
	
	BIG_FREE(zero);
	
	
	
	/*******************************************************************
	 * 5. Print, cleanup, and exit
	 ******************************************************************/
	printf("distinct items:   %d \n", total);
	printf("list length:      %d \n", list_len);
	
	for (int l=0; l<list_len; l++) {
		BIG_FREE(list[l]);
	}
	
	free(list);
	return 0;
}
