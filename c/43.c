/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 43
 **********************************************************************/
#include "euler.h"

int main() {
	/*******************************************************************
	 * Check every permutation of the set {0 1 2 3 4 5 6 7 8 9}.
	 * 
	 * If it satisfies the problem's requirement, add its integer value
	 * to the sum.
	 ******************************************************************/
	int64_t sum = 0;
	int total_permutations = factorial(10);
	
	for (int n = total_permutations; n>=1; n--) {
		int* pandigital = nth_permutation_of_pandigital(n, 10);
		
		if (has_problem43_property(pandigital)) {
			//Convert the pandigital sequence into an integer
			int64_t x = 0;
			int64_t multiplier = 1;
			
			for (int d=9; d>=0; d--) {
				x += pandigital[d] * multiplier;
				multiplier *= 10;
			}
			
			//Add it to the sum
			sum += x;
			
			//Print and continue
			printf("%lld \n", x);
		}
		
		free(pandigital);
	}
	
	printf("\nsum: \t %lld \n", sum);
}
