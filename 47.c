/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 47
 **********************************************************************/
#include "euler.h"

int main() {
	/*******************************************************************
	 * 1. Prepare a list of numbers (500k is sufficient)
	 ******************************************************************/
	int limit = 500000;
	int* numbers = calloc(limit, sizeof(int));
	
	for (int n=0; n<limit; n++)
		numbers[n] = n+1;
	
	
	/*******************************************************************
	 * 2. Use the sieve of Eratosthenes to create two lists: primes
	 *    and nonprimes
	 ******************************************************************/
	int cross_out_index;
	
	for (int i=1; i<limit; i++) {
		if (numbers[i] > 0) {
			cross_out_index = i+numbers[i];
			while (cross_out_index < limit) {
				numbers[cross_out_index] = 0;
				cross_out_index += numbers[i];
			}
		}
	}
	numbers[0] = 0; //Cross 1 out
	
	
	
	int* primes			= NULL;
	int primes_len		= 0;
	int* nonprimes		= NULL;
	int nonprimes_len	= 0;
	
	for (int i=0; i<limit; i++) {
		if (numbers[i]==0)
			nonprimes = append(nonprimes, i+1, &nonprimes_len);
		else
			primes = append( primes, numbers[i], &primes_len);
	}
	

	

	/*******************************************************************
	 * 3. Create a list of nonprimes whose next consecutive values
	 *    are also nonprime (this consecutive sequence should be at
	 *    least 4 terms long)
	 ******************************************************************/
	int* consec_nonprimes = NULL;
	int consec_nonprimes_len = 0;
	int consecutive = 0;
	
	for (int i=1; i<nonprimes_len; i++) {
		int prev = nonprimes[i-1];
		int current = nonprimes[i];
		
		if (current == prev+1)
			consecutive++;
			
		else {
			if (consecutive >= 4) {
				for (int c=consecutive; c>0; c--)
					consec_nonprimes = append(consec_nonprimes,
												nonprimes[i-c],
												&consec_nonprimes_len);
			}
			consecutive = 0;
		}
	}
	
	
	/*******************************************************************
	 * 4. Search the list for 4 consecutive numbers which have 4
	 *    distinct prime factors (DPFs)
	 ******************************************************************/
	consecutive = 0;
	int goal = 4;
	int answer;
	
	for (int i=1; i<consec_nonprimes_len; i++) {
		/***************************************************************
		 * 4a. Get the next two terms on the list
		 **************************************************************/
		int n = consec_nonprimes[i];
		int last_n = consec_nonprimes[i-1];
		
		
		/***************************************************************
		 * 4b. If they aren't consecutive, skip them
		 **************************************************************/
		if (n != last_n+1) {
			consecutive = 0;
			continue;
		}
		
		
		/***************************************************************
		 * 4c. Count the DPFs; increment if it's 4
		 **************************************************************/
		int dpf_count = distinct_prime_factor_count(n,
													primes,
													primes_len);
													
		if (dpf_count==4) {
			consecutive++;
			//printf("%d has %d DPFs (consecutive: %d) \n", 
			//											n,
			//											dpf_count,
			//											consecutive);
		}
		
		else {
			consecutive = 0;
			continue;
		}
		
		
		/***************************************************************
		 * 4d. If the past 4 terms were consecutive and had 4 DPFs,
		 *     save the answer and break
		 **************************************************************/
		if (consecutive==goal) {
			answer = n-(goal-1);
			break;
		}
	}
	
	
	/*******************************************************************
	 * 5. Print, cleanup, and exit
	 ******************************************************************/
	printf("limit                  %d \n", limit);
	printf("primes                 %p \n", primes);
	printf("primes_len             %d \n", primes_len);
	printf("nonprimes              %p \n", nonprimes);
	printf("nonprimes_len          %d \n", nonprimes_len);
	printf("consec_nonprimes       %p \n", consec_nonprimes);
	printf("consec_nonprimes_len   %d \n\n", consec_nonprimes_len);
	
	if (consecutive==goal) {
		printf("answer                 %d \n", answer);
		printf("                       %d \n", answer+1);
		printf("                       %d \n", answer+2);
		printf("                       %d \n", answer+3);
	}
	else
		puts("Didn't find the answer. Try increasing the limit.");
	
	free(numbers);
	free(primes);
	free(nonprimes);
	free(consec_nonprimes);
	return 0;
}
