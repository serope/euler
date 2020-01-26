/*
 * Project Euler
 * 50.c
 */
#include <stdlib.h>
#include <stdio.h>
#include "array.h"
#include "prime.h"

int main() {
	// sieve
	int limit = 1000000;
	int primes_len;
	int* primes = eratosthenes(limit, &primes_len);
	int max = primes[primes_len-1];
	
	// solve
	int longest = 21;
	int start = 0;
	while (start < (primes_len-longest)) {
		long int sum = 0;
		int seq_len = 0;
		for (int i=start; i<primes_len; i++) {
			sum += primes[i];
			seq_len++;
			if (sum > max)
				break;
			else if (arr_bsearch(primes, primes_len, sum)) {
				if (seq_len > longest) {
					printf("sum        %ld \n", sum);
					printf("seq_len    %d \n", seq_len);
					printf("first      %d (index %d) \n\n",
												primes[start], start);
					longest = seq_len;
				}
			}
		}
		start++;
	}
	
	// end
	free(primes);
	return 0;
}
