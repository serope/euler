/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 14
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "euler.h"

int	collatz_sequence_len(int starting_number, int* list, int list_len);

int main() {
	/*******************************************************************
	 * 1. Create an array in which each index represents a starting
	 *    point and each value represents the length of the starting
	 *    point's Collatz sequence (e.g. lengths[13] = 10)
	 ******************************************************************/
	int limit = 1000000;
	int* lengths = (int*) calloc(limit, sizeof(int));
	if (!lengths) {
		puts("Unable to call calloc()");
		return 1;
	}
	lengths[13] = 10;
	
	
	/*******************************************************************
	 * 2. For every 'x' from 1 to 1 million, determine which one
	 *    creates the longest Collatz sequence
	 ******************************************************************/
	int longest_starting_number = 13;
	int longest_length = 10;
	
	for (int x=1; x<limit; x++) {
		int len = collatz_sequence_len(x, lengths, limit);
		
		if (len > longest_length) {
			longest_starting_number = x;
			longest_length = len;
		}
	}
	
	
	/*******************************************************************
	 * 3. Print, cleanup, and exit
	 ******************************************************************/
	printf("%d creates a Collatz sequence of length %d \n",
												longest_starting_number,
												longest_length);
	free(lengths);
	return 0;
}



int collatz_sequence_len(int starting_number, int* list, int list_len) {
	int64_t x = starting_number;
	int length = 1;
	
	while (x>1) {
		/***************************************************************
		 * Continue the sequence
		 **************************************************************/
		if (x%2==0)
			x /= 2;
		else
			x = 3*x+1;
			
		/***************************************************************
		 * Reference the 'lengths' array to see if the current value
		 * of 'x' has been previously used to create a sequence. If
		 * so, add this previously-acquired length to 'length' and
		 * break early.
		 **************************************************************/
		if (x<list_len && list[x]>0) {
			length += list[x];
			break;
		}
		else
			length++;
	}
	
	
	/*******************************************************************
	 * Record this starting number's length in 'lengths' and return
	 ******************************************************************/
	list[starting_number] = length;
	return length;
}
