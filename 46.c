/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 46
 **********************************************************************/
#include "euler.h"
#include <math.h>

bool is_square(int x);
bool has_problem46_property(int x, int* primes, int primes_len);

int main() {
	/*******************************************************************
	 * 1. Prepare two lists: prime numbers and odd composite numbers
	 *    (10k is sufficient)
	 ******************************************************************/
	int limit = 10000;
	
	int* primes	= (int*) calloc(limit, sizeof(int));
	for (int x=0; x<limit; x++)
		primes[x] = x+1;
		
	int* odd_composites	= NULL;
	int odd_composites_len = 0;
	
		
	
	/*******************************************************************
	 * 2. Use the sieve of Eratosthenes to populate both lists
	 * 
	 *    When a non-prime number is found, remove it from the primes
	 *    list, BUT if it's odd, add it to the odd composites list
	 *    first
	 ******************************************************************/
	int cross_out_index;
	
	for (int i=1; i<limit; i++) {
		if (primes[i] > 0) {
			cross_out_index = i+primes[i];
			while (cross_out_index < limit) {
				//Insert this number into the odd composite list
				if (IS_ODD(primes[cross_out_index]))
					odd_composites = insert(odd_composites, primes[cross_out_index], &odd_composites_len);
				
				//Then "remove" it from the primes list (make it 0)
				primes[cross_out_index] = 0;
				cross_out_index += primes[i];
			}
		}
	}
	primes[0] = 0; //Cross 1 out
	
	
	
	/*******************************************************************
	 * 3. Find the first odd composite number which does NOT satisfy
	 *    the requirements for Goldbach's other conjecture
	 ******************************************************************/
	int answer;
	bool solved = false;
	
	for (int i=0; i<odd_composites_len; i++) {
		int odd_composite = odd_composites[i];
		
		if (!has_problem46_property(odd_composite, primes, limit)) {
			answer = odd_composite;
			solved = true;
			break;
		}
	}
	
	
	/*******************************************************************
	 * 4. Print, cleanup, and exit
	 ******************************************************************/
	if (solved)
		printf("%d \n", answer);
	else
		puts("Didn't find the answer. Try increasing the limit.");
		
	free(primes);
	free(odd_composites);
	return 0;
}




bool is_square(int x) {
	float a		= sqrt(x);
	int b		= (int) a;
	float c		= (float) b;
	
	if (a>c)
		return false;
		
	return true;
}



bool has_problem46_property(int x, int* primes, int primes_len) {
	/*******************************************************************
	 * Check whether x satisfies Goldbach's other conjecture.
	 * 
	 * By taking any of the problem's examples and solving for the
	 * squared term, the result is s=(x-p)/2, where p is some prime
	 * number which is smaller than x. If s is a square, then the
	 * conjecture holds true.
	 ******************************************************************/
	 for (int p_index=0; p_index<primes_len; p_index++) {
		int p = primes[p_index];
		
		if (p==0)
			continue;
		else if (p>=x)
			break;
		
		int s = x-p;
		s = s/2;
		
		if (is_square(s))
			return true;
	 }
	 
	 return false;
}
