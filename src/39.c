/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 39
 **********************************************************************/
#include "euler.h"

int main() {
	/*******************************************************************
	 * 1. Prepare a list in which each index represents a perimeter 
	 *    and each value is a score representing how many Pythagorean
	 *    triplet solutions that perimeter has
	 * 
	 *    Example: If the perimeter p=45 has 7 solutions, then
	 *             perimeter_scores[45] = 7
	 ******************************************************************/
	int limit = 1000;
	int* perimeter_scores = calloc(limit, sizeof(int));
	
	
	/*******************************************************************
	 * 2. For every possible 'a', 'b', and 'c' between 1 and the
	 *    limit, if the three form a Pythagorean triplet, then find its
	 *    perimeter value, then increment that perimeter's score on
	 *    the list
	 * 
	 *    Note: In a Pythagorean triplet, at least one term is
	 *          divisible by 5
	 ******************************************************************/
	for (int a=1; a<limit; a++) {
		for (int b=a+1; b<limit; b++) {
			for (int c=b+1; c<limit; c++) {
				if (NOT_DIVISIBLE(a,5) && NOT_DIVISIBLE(b,5) && NOT_DIVISIBLE(c,5))
					continue;
				
				int perimeter = a+b+c;
				
				if (perimeter<limit && is_pythagorean_triplet(a, b, c))
					perimeter_scores[perimeter]++;
			}
		}
	}
	
	
	/*******************************************************************
	 * 3. Find which perimeter has the highest score
	 ******************************************************************/
	int highest_score = 0;
	int perimeter;
	for (int p=0; p<limit; p++) {
		if (perimeter_scores[p] > highest_score) {
			highest_score = perimeter_scores[p];
			perimeter = p;
		}
	}
	
	
	/*******************************************************************
	 * 4. Print, cleanup, and exit
	 ******************************************************************/
	printf("The perimeter p=%d has %d Pythagorean solutions \n",
											perimeter, highest_score);
			
	free(perimeter_scores);
	return 0;
}
