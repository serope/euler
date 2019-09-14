/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 38
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "euler.h"
#define _ 0


int main() {
	int largest_pandigital	= 0;
	int limit				= 10000;
	int rows				= 9;
	
	int multiply[9][9] = {
		{1,_,_,_,_,_,_,_,_},
		{1,2,_,_,_,_,_,_,_},
		{1,2,3,_,_,_,_,_,_},
		{1,2,3,4,_,_,_,_,_},
		{1,2,3,4,5,_,_,_,_},
		{1,2,3,4,5,6,_,_,_},
		{1,2,3,4,5,6,7,_,_},
		{1,2,3,4,5,6,7,8,_},
		{1,2,3,4,5,6,7,8,9}
	};
	
	
	/*******************************************************************
	 * Check every 'x' between 1 and the limit
	 * (10,000 is sufficient for this problem)
	 ******************************************************************/
	for (int x=1; x<limit; x++)
		for (int r=0; r<rows; r++) {
			/***********************************************************
			 * 1. Prepare a list of every product that will be formed
			 *    with respect to the current row
			 **********************************************************/
			int list_len = r+1;
			int* list = (int*) calloc(list_len, sizeof(int));
			
			
			/***********************************************************
			 * 2. Multiply 'x' by every term in the row
			 *    Save each result on the list
			 **********************************************************/
			for (int c=0; c<list_len; c++)
				if (multiply[r][c] != _)
					list[c] = x*multiply[r][c];
	
				
			/***********************************************************
			 * 3. If the total digits among every item on the list
			 *    isn't exactly 9, skip this 'x'
			 **********************************************************/
			int list_digit_count = 0;
			
			for (int l=0; l<list_len; l++)
				list_digit_count += digit_count(list[l]);
			
			if (list_digit_count != 9) {
				free(list);
				continue;
			}
			
			
			/***********************************************************
			 * 4. Concatenate all of the items on the list into one big
			 *    number
			 **********************************************************/
			int number = 0;
			int multiplier = 1;
			
			//For each item, going from backwards to forwards...
			for (int i=list_len-1; i>=0; i--) {
				//1. Get the item
				int item = list[i];
				
				//2. Get the digits of the item
				int* digits = digits_of(item);
				int count = digit_count(item);
				
				//3. Put them into the big number
				for (int d=count-1; d>=0; d--) {
					number += digits[d]*multiplier;
					multiplier *= 10;
				}
			}
			
			
			/***********************************************************
			 * 5. If the big number is pandigital 1 to 9, record it if
			 *    it's the largest one so far
			 **********************************************************/
			if (is_pandigital_1_to_9(number))
				if (number > largest_pandigital) {
					//Print details
					printf("%d \t %d \t {", number, x);
					for (int c=0; c<rows; c++) {
						if (multiply[r][c] == _)
							printf("_ ");
						else
							printf("%d ", multiply[r][c]);
						}
					printf("\b} \n");
					
					//Replace largest
					largest_pandigital = number;
				}
			
			//Free list and continue
			free(list);
		}
	
	printf("\nlargest: \t %d \n", largest_pandigital);
	return 0;
}
