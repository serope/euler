/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 21
 **********************************************************************/
#include "euler.h"
#define D(x) sum_of_proper_divisors_of(x)

int main() {
	/*******************************************************************
	 * 1. Find every amicable number between 1 and 10k
	 *    Put each one in the 'amicable_numbers' array, without repeats
	 ******************************************************************/
	int* amicable_numbers = NULL;
	int amicable_len = 0;
	int a;
	int b;
	
	for (int n=1; n<10000; n++) {
		a = D(n);
		b = D(a);
		
		if (b==n && a!=b) {
			if (!contains(amicable_numbers, a, amicable_len))
				amicable_numbers = append(amicable_numbers, a, &amicable_len);
			
			if (!contains(amicable_numbers, b, amicable_len))
				amicable_numbers = append(amicable_numbers, b, &amicable_len);
		}
	}
	
	
	
	/*******************************************************************
	 * 2. Sum them
	 ******************************************************************/
	int sum = 0;
	for (int i=0; i<amicable_len; i++)
		sum += amicable_numbers[i];
	
	
	
	/*******************************************************************
	 * 3. Print, cleanup, and exit
	 ******************************************************************/
	printf("amicable_len  %d \n", amicable_len);
	printf("sum           %d \n", sum);
	free(amicable_numbers);
	return 0;
}
