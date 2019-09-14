/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 40
 **********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "euler.h"

int main() {
	/*******************************************************************
	 * 1. Prepare an array that will hold the digits of the fractional
	 *    part of Champernowne's constant to 1 million digits
	 ******************************************************************/
	int len = 1000000;
	int* champernowne = (int*) calloc(len, sizeof(int));


	/*******************************************************************
	 * 2. Append consecutive integers to the array until all 1,000,000
	 *    slots have been filled
	 ******************************************************************/
	int x = 1;
	int index = 0;
	
	while (index <= len) {
		//Get digits
		int* digits = digits_of(x);
		int digits_len = digit_count(x);
		
		//Add to array
		for (int d=0; d<digits_len; d++) {
			champernowne[index] = digits[d];
			index++;
		}
		
		//Free and increment
		free(digits);
		x++;
	}
	
	
	/*******************************************************************
	 * 3. Multiply the digits of interest while printing them
	 ******************************************************************/
	int digit_no	= 10;
	int product		= 1;
	index			= digit_no-1;
	
	while (digit_no <= len) {
		int digit = champernowne[index];
		product *= digit;
		
		printf("digit_no       %d \n", digit_no);
		printf("digit          %d \n", digit);
		printf("product        %d \n\n", product);
		
		digit_no *= 10;
		index = digit_no-1;
	}
	
	
	/*******************************************************************
	 * 4. Cleanup and exit
	 ******************************************************************/
	free(champernowne);
	return 0;
}
