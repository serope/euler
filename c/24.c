/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 24
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "euler.h"

#define _            -1        //Represents an unknown member of a set
#define SIZE         10
#define TARGET       1000000
#define EXISTS(x)    x!=_


int main() {
	int pool[SIZE]					= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int solution[SIZE]				= {_, _, _, _, _, _, _, _, _, _};
	int solution_len 				= 0;
	int total_possible_permutations = factorial(SIZE);
	int range_size = total_possible_permutations/SIZE;
	int range_marker = 0;
	
	//Perform the pandigital generation method described on the web page
	while (1) {
		/***************************************************************
		 * 1. Find which row is correct
		 **************************************************************/
		int row = 0;
		
		while (range_marker+range_size < TARGET) {
			row += 1;
			range_marker += range_size;
		}
		
		
		/***************************************************************
		 * 2. Create a list of items that remain in the pool
		 **************************************************************/
		int remaining_pool_len = 0;
		for (int p=0; p<SIZE; p++)
			if (EXISTS(pool[p]))
				remaining_pool_len += 1;
		
		int* remaining_pool = calloc(remaining_pool_len, sizeof(int));
		int r = 0;
		for (int p=0; p<SIZE; p++)
			if (EXISTS(pool[p])) {
				remaining_pool[r] = pool[p];
				r += 1;
			}
		
		
		/***************************************************************
		 * 3. Transfer the appropriate item from the remaining_pool into
		 *    the solution
		 **************************************************************/
		int remaining_pool_index = row;
		
		solution[solution_len] = remaining_pool[remaining_pool_index];
		solution_len += 1;
		
		int remove_index = 0;
		while (pool[remove_index] != solution[solution_len-1])
			remove_index += 1;
		
		pool[remove_index] = _;
		free(remaining_pool);
		
		print_set(solution, SIZE);
		
		
		/***************************************************************
		 * 4. Stop if the the solution has the same length as the
		 *    original set S
		 **************************************************************/
		if (solution_len==SIZE)
			break;
		
		
		/***************************************************************
		 * 5. Otherwise, perform another pass with new ranges
		 **************************************************************/
		int range_start = range_marker;				//725760 in 1st pass
		int range_end = range_marker + range_size;	//1088640
		
		range_marker = range_start;
		
		range_size = (range_end-range_start)/(SIZE-solution_len);
	}
	
	return 0;
}
