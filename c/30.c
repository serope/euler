/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 30
 **********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "euler.h"

int main() {
	//Make a list of every digit's 5th power
	int* powers = (int*) calloc(10, sizeof(int));
	for (int i=0; i<10; i++)
		powers[i] = i*i*i*i*i;
	
	//Make a list of every number that meets the problem's criteria
	int* list = NULL;
	int list_len = 0;
	
	//For every index from 2 to the limit...
	int limit = 200000;
	for (int i=2; i<limit; i++) {
		//Get the digits of this index
		int* digits = digits_of(i);
		int digits_len = digit_count(i);
		
		//Sum the associated powers
		int sum = 0;
		for (int j=0; j<digits_len; j++)
			sum += powers[digits[j]];
		
		//Append if it equals the original number
		if (sum==i) {
			printf("%d \n", sum);
			list = append(list, i, &list_len);
		}
		
		//Free
		free(digits);
	}
	
	//Sum every member of the list
	int sum = 0;
	for (int i=0; i<list_len; i++)
		sum += list[i];
	
	//End
	printf("sum: %d \n", sum);
	free(powers);
	free(list);
	return 0;
	
}
