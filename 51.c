/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 51
 **********************************************************************/
#include "euler.h"
#include "euler_binary.h"

#define IS_PRIME(x)		contains(primes, x, primes_len)
#define PRINT_ALL		false //Set true for a detailed output

bool has_problem51_property(int x, bool* swap, int* primes, int primes_len);


int main() {
	/*******************************************************************
	 * 1. Create a list of primes from 1 to an upper limit
	 *    (1 million is sufficient for this problem)
	 ******************************************************************/
	int limit			= 1000000;
	int* primes			= eratosthenes(limit);
	int primes_len		= eratosthenes_count(limit);
	
	
	
	/*******************************************************************
	 * 2. For each 'x' on the list...
	 ******************************************************************/
	for (int p=0; p<primes_len; p++) {
		/***************************************************************
		 * 2a. Don't bother with 1-digit values
		 **************************************************************/
		int x = primes[p];
		if (x<=9)
			continue;
		
		/***************************************************************
		 * 2b. Get the digits of 'x'
		 **************************************************************/
		int* digits = digits_of(x);
		int digits_len = digit_count(x);
		
		
		
		/***************************************************************
		 * 2c. Generate every binary sequence starting from 1, then
		 *     test if 'x' satisfies the problem's requirements
		 *     (see the web page for a detailed explanation)
		 **************************************************************/
		int base = 1;
		while (true) {
			/***********************************************************
			 * Turn 'base' into a binary sequence
			 **********************************************************/
			bool* swap = binary_sequence_of(base);
			int bin_len = binary_sequence_count(base);
			
			
			/***********************************************************
			 * Break if it the current sequence is all ones
			 * e.g. {1 1 1 1 1 1}
			 **********************************************************/
			if (binary_sequence_count(base+1) > digits_len)
				break;
			
			/***********************************************************
			 * Prepend zeros to 'swap' until its length is equal to
			 * the amount of digits of 'x'
			 **********************************************************/
			while (bin_len < digits_len)
				swap = prepend_bool(swap, false, &bin_len);
			
			#if (PRINT_ALL)
			printf("base               %d \n", base);
			printf("swap               ");
			binary_sequence_print(swap, bin_len);
			#endif
			
			/***********************************************************
			 * Check if 'x' satisfies problem 51's requirements
			 **********************************************************/
			if (has_problem51_property(x, swap, primes, primes_len)) {
				free(swap);
				free(digits);
				goto nested_break;
			}
			
			free(swap);
			base += 1;
		}
		
		free(digits);
	}
	
	
	/*******************************************************************
	 * 3. Print, cleanup, and exit
	 ******************************************************************/
	nested_break:
	free(primes);
	return 0;
}





bool has_problem51_property(int x, bool* swap, int* primes, int primes_len) {
	/*******************************************************************
	 * Prepare the list of family members
	 ******************************************************************/
	int* family = NULL;
	int family_len = 0;
	
	
	/*******************************************************************
	 * For every digit from 0 to 9...
	 ******************************************************************/
	for (int digit=0; digit<=9; digit++) {
		int y = x;
		
		/***************************************************************
		 * For every bit in the 'swap' binary sequence...
		 **************************************************************/
		bool skip = false;
		for (int s=0; s<digit_count(x); s++) {
			if (swap[s]) {
				/*******************************************************
				 * Exceptions: Skip if the swap position is 0 and the
				 * digit is 0, or if the swap position is the last one
				 ******************************************************/
				if ((s==0 && digit==0) || (s==digit_count(x)-1)) {
					skip = true;
					break;
				}
				y = replace_digit(y, digit, s);
			}
		}
		
		if (skip)
			continue;
		else
			family = append(family, y, &family_len);
	}
	/*******************************************************************
	 * Check how many family members are prime
	 ******************************************************************/
	int total_primes = 0;
	
	for (int f=0; f<family_len; f++)
		if (IS_PRIME(family[f]))
			total_primes++;
	
	#if (PRINT_ALL)
	printf("x                  %d \n", x);
	printf("swap positions     ");
	for (int i=0; i<digit_count(x); i++) {
		if (swap[i]==true)
			printf("_");
		else
			printf("%d", digits_of(x)[i]);
	}
	printf("\n");
	
	printf("family             ");
	print_set(family, family_len);
	printf("total_primes       %d \n\n", total_primes);
	#endif
	
	
	if (total_primes>=8) {
		/***************************************************************
		 * Print details and return
		 **************************************************************/
		#if (!PRINT_ALL)
		printf("x                  %d \n", x);
		printf("swap positions     ");
		for (int i=0; i<digit_count(x); i++) {
			if (swap[i]==true)
				printf("_");
			else
				printf("%d", digits_of(x)[i]);
		}
		printf("\n");
		
		printf("family             ");
		print_set(family, family_len);
		printf("total_primes       %d \n", total_primes);
		printf("smallest member    %d \n\n", family[0]);
		#endif
		
		free(family);
		return true;
	}
	
	free(family);
	return false;
}
