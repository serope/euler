/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 36
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "euler.h"
#include "euler_binary.h"

int main() {
	int sum = 0;
	
	for (int x=1; x<=1000000; x++) {
		/**********************************************************
		 * 1. Check if 'x' is a palindrome
		 *********************************************************/
		if (!is_palindromic_int(x))
			continue;
			
		/**********************************************************
		 * 2. Check if the binary sequence of 'x' is a palindrome
		 *********************************************************/
		bool* bin = binary_sequence_of(x);
		int bin_len = binary_sequence_count(x);
		
		if (!binary_sequence_is_palindrome(bin, bin_len)) {
			free(bin);
			continue;
		}
		
		/**********************************************************
		 * 3. If both are palindromes, add 'x' to the sum
		 *********************************************************/
		printf("%d \t", x);
		binary_sequence_print(bin, bin_len);
		
		sum += x;

		free(bin);
	}
	
	printf("\nsum \t %d \n", sum);
}
