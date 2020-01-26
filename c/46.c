/*
 * Project Euler
 * 46.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "array.h"
#include "euler.h"

bool is_square(int x);
bool has_problem46_property(int x, int* primes, int primes_len);
int cmp(const void* a_ptr, const void* b_ptr);

int main() {
	// prepare primes and odd composites
	int limit = 10000;
	int* primes	= calloc(limit, sizeof(int));
	for (int i=1; i<limit; i++)
		primes[i] = i+1;
	int* oddcs = NULL;
	int oddcs_len = 0;
	
	// sieve of Eratosthenes
	for (int i=1; i<limit; i++) {
		if (primes[i] > 0) {
			int cross_out_index = i+primes[i];
			while (cross_out_index < limit) {
				// append to odd composite list
				if (primes[cross_out_index]%2 != 0)
					oddcs = arr_append(oddcs, primes[cross_out_index],
															&oddcs_len);
				// clear from primes
				primes[cross_out_index] = 0;
				cross_out_index += primes[i];
			}
		}
	}
	
	// sort
	qsort(oddcs, oddcs_len, sizeof(int), cmp);
	
	// find first oddc which doesn't satisfy Goldbach's other conjecture
	int answer;
	bool solved = false;
	for (int i=0; i<oddcs_len; i++) {
		int oddc = oddcs[i];
		if (!has_problem46_property(oddc, primes, limit)) {
			answer = oddc;
			solved = true;
			break;
		}
	}
	
	// end
	if (solved)
		printf("%d \n", answer);
	else
		puts("The answer wasn't found (try increasing the limit)");
	free(primes);
	free(oddcs);
	return 0;
}


/**
 * Returns true if x is a perfect square.
 * 
 * @param	x	the term to check
 * @return		true or false
 */
bool is_square(int x) {
	float a		= sqrt(x);
	int b		= (int) a;
	float c		= (float) b;
	if (a>c)
		return false;
	return true;
}


/**
 * Compares two integers.
 * 
 * @param	a_ptr	a pointer to the first term
 * @param	b_ptr	a pointer to the second term
 * @return			positive if a>b
 * 					negative if a<b
 * 					zero if a==b
 */
int cmp(const void* a_ptr, const void* b_ptr) {
	int a = *((int*) a_ptr);
	int b = *((int*) b_ptr);
	return a-b;
}


/**
 * Returns true if x satisfies Goldbach's other conjecture.
 * By taking any of the problem's examples and solving for the squared
 * term, the result is s=(x-p)/2, where p is some prime number which is
 * smaller than x. If s is a square, then the conjecture holds true.
 * 
 * @param	x			the term to check
 * @param	primes		an array of primes
 * @param	primes_len	the array's length
 * @return				true or false
 */
bool has_problem46_property(int x, int* primes, int primes_len) {
	bool result = false;
	 for (int i=0; i<primes_len; i++) {
		int p = primes[i];
		if (p == 0)
			continue;
		else if (p >= x)
			break;
		int s = x-p;
		s = s/2;
		if (is_square(s)) {
			result = true;
			break;
		}
	 }
	 return result;
}
