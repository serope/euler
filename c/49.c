/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 49
 **********************************************************************/
#include "euler.h"

int main() {
	/*******************************************************************
	 * 1. Create a list of primes from 1 to 9999
	 ******************************************************************/
	int* list = eratosthenes(9999);
	int list_len = eratosthenes_count(9999);
	
	
	/*******************************************************************
	 * 2. Remove the 3 example terms (1487, 4817, 8147) and any term
	 *    which does not have exactly 4 digits
	 ******************************************************************/
	for (int i=0; i<list_len; i++)
		if (list[i]==1487 || list[i]==4817 || list[i]==8147 || list[i]<1000)
			list[i] = 0;
			
	
	/*******************************************************************
	 * 3. Find 3 terms that satisfy the problem's requirements
	 ******************************************************************/
	int answer1;
	int answer2;
	int answer3;
	
	//Find the 1st term
	for (int i=0; i<list_len; i++) {
		int term1 = list[i];
		if (term1==0)
			continue;
			
		//Find the 2nd term
		for (int j=i+1; j<list_len; j++) {
			int term2 = list[j];
			if (term2==0)
				continue;
			
			if (has_problem49_property(term1, term2)) {
				
				//Find the 3rd term
				for (int k=j+1; k<list_len; k++) {
					int term3 = list[k];
					if (term3==0)
						continue;
						
					if (term3 != term1)
						if (has_problem49_property(term2, term3)) {
							answer1 = term1;
							answer2 = term2;
							answer3 = term3;
							goto nested_break;
						}
				}
			}
		}
	}
	
	
	/*******************************************************************
	 * 4. Print, cleanup, and exit
	 ******************************************************************/
	nested_break:
	printf("%d %d %d \n", answer1, answer2, answer3);
	free(list);
	return 0;
}
