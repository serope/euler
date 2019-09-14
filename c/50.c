/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 50
 **********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "euler.h"
#define IS_PRIME(x) contains(primes, x, primes_len)

int main() {
	/*******************************************************************
	 * 1. Create a list of primes from 1 to 1 million and get the
	 *    largest prime
	 ******************************************************************/
	int limit			= 1000000;
	int* primes			= eratosthenes(limit);
	int primes_len		= eratosthenes_count(limit);
	int largest_prime	= primes[primes_len-1];
	
	
	
	/*******************************************************************
	 * 2. Find the longest consecutive sequence which sums to a prime
	 *    which is below 1,000,000
	 * 
	 *    The 'start' value is the index at which the current
	 *    consecutive prime sequence starts
	 ******************************************************************/
	int longest_sequence = 21;
	int start = 0;
	
	while (start < (primes_len-longest_sequence)) {
		/***************************************************************
		 * Prepare the sum and sequence count for this starting point
		 **************************************************************/
		long int sum = 0;
		int sequence = 0;
		
		for (int p=start; p<primes_len; p++) {
			/***********************************************************
			 * Add the current term to the sum and increment the
			 * sequence count
			 **********************************************************/
			sum += primes[p];
			sequence++;
			
			/***********************************************************
			 * If the sum exceeds the largest prime, then the program
			 * has exhausted every sequence which begins at this
			 * starting point and forms a sum which is prime and less
			 * than 1,000,000
			 **********************************************************/
			if (sum > largest_prime)
				break;
			
			/***********************************************************
			 * Otherwise, if the sum is prime and it has the longest
			 * sequence count, print details and record the sequence
			 * count
			 **********************************************************/
			else if (IS_PRIME(sum)) {
				if (sequence > longest_sequence) {
					printf("sum               %ld \n", sum);
					printf("sequence length   %d \n", sequence);
					printf("first term        %d (index %d) \n\n",
												primes[start], start);
												
					longest_sequence = sequence;
				}
			}
		}
		
		/***************************************************************
		 * Increment the starting point for the next loop
		 **************************************************************/
		start++;
	}
	
	
	
	/*******************************************************************
	 * 3. Cleanup and exit
	 ******************************************************************/
	free(primes);
	return 0;
}
