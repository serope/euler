/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 8
 **********************************************************************/
#include "euler.h"

int main() {
	/*******************************************************************
	 * 1. Load the text file
	 ******************************************************************/
	const char* filename = "08_big_number.txt";
	FILE* txtfile = fopen(filename, "r");
	if (!txtfile) {
		printf("Unable to load %s \n", filename);
		return 1;
	}
	
	/*******************************************************************
	 * 2. Convert the contents of the file into an int array
	 *    Note: 'current_char' should be an int due to the nature
	 *          of getc() and EOF
	 ******************************************************************/
	int* digits = NULL;
	int digits_len = 0;
	int current_char;
	
	while ((current_char=getc(txtfile)) != EOF) {
		int current_digit = CHAR_TO_INT(current_char);
		digits = append(digits, current_digit, &digits_len);
	}
	fclose(txtfile);
	
	/*******************************************************************
	 * 3. Multiply every digit in every possible chunk of adjacent 
	 *    numbers and remember the largest product
	 ******************************************************************/
	int chunk_size = 13;
	int64_t largest = 0;
	
	for (int i=0; i<(digits_len-chunk_size)-1; i++) {
		/***************************************************************
		 * Get the product of the current chunk
		 **************************************************************/
		int64_t product = 1;
		for (int j=0; j<chunk_size; j++)
			product *= digits[i+j];
		
		
		/***************************************************************
		 * Compare it to the largest recorded product
		 **************************************************************/
		if (product > largest)
			largest = product;
	}
	
	/*******************************************************************
	 * 4. Print and exit
	 ******************************************************************/
	free(digits);
	printf("%lld \n", largest);
	return 0;
}
