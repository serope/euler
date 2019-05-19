/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 44
 **********************************************************************/
#include "euler.h"

int main() {
	/*******************************************************************
	 * 1. Create a list of pentagonal numbers
	 *    (10k is sufficient for this problem)
	 ******************************************************************/
	int limit = 10000;
	int64_t* set = (int64_t*) calloc(limit, sizeof(int64_t));
	
	for (int n=0; n<limit; n++)
		set[n] = nth_pentagonal_number_int64(n+1);
	

	/*******************************************************************
	 * 2. Add and subtract each possible pair on the list
	 *    If the both sum and difference are on the list, print them
	 * 
	 *    Note: All (most?) pentagonal numbers end with
	 *          either 0, 1, 2, 5, 6, or 7
	 * 
	 *          Therefore, all sums and differences that do NOT end
	 *          in one of those digits may be ignored
	 ******************************************************************/
	int digit;
	int64_t sum;
	int64_t dif;
	int64_t smallest_dif		= set[limit-1];
	int64_t largest_pentagon	= smallest_dif;
	
	for (int a=0; a<limit-1; a++) {
		for (int b=a+1; b<limit; b++) {
			//if (a%10==0 && b%1000==0)
				//printf("(%d, %d) \n", a,b);
			
			//Sum
			sum 	= set[a]+set[b];
			digit	= final_digit_of(sum);
			
			if (digit==3 || digit==4 || digit==8 || digit==9)
				continue;
			else if (sum>largest_pentagon || IS_NEGATIVE(sum))
				break;
				
			//Difference
			dif 	= set[b]-set[a];
			digit	= final_digit_of(dif);
			if (digit==3 || digit==4 || digit==8 || digit==9)
				continue;
			else if (IS_NEGATIVE(dif))
				break;
				
			//List check
			if (dif < smallest_dif) {
				if (contains_int64(set, sum, limit)) {
					if (contains_int64(set, dif, limit)) {
						smallest_dif = dif;
						printf("(%lld, %lld) \t", set[a], set[b]);
						printf("sum %lld, ", sum);
						printf("dif %lld \n", dif);
					}
				}
			}
		}
	}
	
	
	/*******************************************************************
	 * 3. Print, cleanup, and exit
	 ******************************************************************/
	printf("smallest dif: %lld \n", smallest_dif);
	free(set);
	return 0;
}
