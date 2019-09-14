/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 35
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "euler.h"

#define TOTAL_ROTATIONS(x)	digit_count(x)

int main() {
	/*******************************************************************
	 * 1. Make a list of prime numbers from 1 to 1 million
	 ******************************************************************/
	int* primes = eratosthenes(1000000);
	int primes_len = eratosthenes_count(1000000);
	
	
	
	/*******************************************************************
	 * 2. With the exceptions of 2 and 5, remove all primes that
	 *    contain 2, 4, 5, 6, 8 or 0
	 *    
	 *    Note: If a rotation can be even or divisible by 5, it won't
	 *          satisfy the problem's requirement
	 ******************************************************************/
	for (int p=5; p<primes_len; p++) {
		//Get digits
		int* digits = digits_of(primes[p]);
		int len = digit_count(primes[p]);
		
		/*
		 * If it contains 2, 4, 5, 6, 8, or 0, remove it from
		 * the list
		 */
		for (int d=0; d<len; d++) {
			int digit = digits[d];
			
			if 	(digit==2 || digit==4 || digit==5 || digit==6 || digit==8 || digit==0) {
				primes[p] = 0;
				break;
			}
		}
		free(digits);
	}
	
	
	
	/*******************************************************************
	 * 3. Begin searching the list for circular primes
	 ******************************************************************/
	int total_circular_primes = 0;
	
	for (int p=0; p<primes_len; p++) {
		if (primes[p]>0) {
			//Count how many rotations this prime has
			int prime = primes[p];
			int total_rotations = TOTAL_ROTATIONS(prime);
			
			//Get rotations
			int* rotations = rotations_of(prime);
			
			//DEBUG: Print rotations
			//printf("%d: \t", prime);
			//for (int r=0; r<total_rotations; r++)
				//printf("%d ", rotations[r]);
			
			//f every rotation is prime, add 1 to the total
			bool every_rotation_is_prime = true;
			
			for (int r=0; r<total_rotations; r++)
				if (!is_prime(rotations[r])) {
					every_rotation_is_prime = false;
					break;
				}
				
			if (every_rotation_is_prime) {
				//Print
				printf("%d \t{", prime);
				for (int r=0; r<total_rotations; r++)
					printf("%d ", rotations[r]);
				printf("\b} \n");
				
				//Increment
				total_circular_primes += 1;
			}
			
			free(rotations);
		}
	}
	
	
	
	/*******************************************************************
	 * 4. End
	 ******************************************************************/
	printf("primes_len                  %d \n", primes_len);
	printf("total_circular_primes       %d \n", total_circular_primes);
	free(primes);
	return 0;
}
