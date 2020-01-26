/*
 * Project Euler
 * 17.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "euler.h"


const char** new_p17_dictionary();
char* int_to_word(int n, const char** dict);


int main() {
	// dictionary of base words
	const char** dict = new_p17_dictionary();
	
	// count
	int total = 0;
	for (int x=1; x<=1000; x++) {
		char* word = int_to_word(x, dict);
		total += strlen(word);
		free(word);
	}
	
	// end
	printf("total \t %d \n", total);
	free(dict);
	return 0;
}


/**
 * Creates a new array wherein every value is its index's English word,
 * but only for base words, e.g. "hundred", but not "twohundred".
 * 
 * @return	an array of string constants
 */
const char** new_p17_dictionary() {
	const char** dict = calloc(1000, sizeof(char*));
	dict[1]		= "one";
	dict[2]		= "two";
	dict[3]		= "three";
	dict[4]		= "four";
	dict[5]		= "five";
	dict[6]		= "six";
	dict[7]		= "seven";
	dict[8]		= "eight";
	dict[9]		= "nine";
	dict[10]	= "ten";
	dict[11]	= "eleven";
	dict[12]	= "twelve";
	dict[13]	= "thirteen";
	dict[14]	= "fourteen";
	dict[15]	= "fifteen";
	dict[16]	= "sixteen";
	dict[17]	= "seventeen";
	dict[18]	= "eighteen";
	dict[19]	= "nineteen";
	dict[20]	= "twenty";
	dict[30]	= "thirty";
	dict[40]	= "forty";
	dict[50]	= "fifty";
	dict[60]	= "sixty";
	dict[70]	= "seventy";
	dict[80]	= "eighty";
	dict[90]	= "ninety";
	dict[100]	= "hundred";
	dict[1000]	= "onethousand";
	return dict;
}


/**
 * Converts the given integer (1-1000) into an English word.
 * 
 * @param	n		the integer to convert
 * @param	dict	a dictionary of numerical base words
 * @return			a dynamically-allocated string
 */
char* int_to_word(int n, const char** dict) {
	int max_word_len = 128;
	int total_digits = digit_count(n);
	char* result = calloc(max_word_len, sizeof(char));
	
	// 1 digit
	if (total_digits == 1)
		strcpy(result, dict[n]);
	
	// 2 total_digits
	else if (total_digits == 2) {
		const char* base = dict[n];
		if (base)
			strcpy(result, base);
		else {
			int* digits = digits_of(n);
			char* a = int_to_word(10*digits[0], dict);
			char* b = int_to_word(digits[1], dict);
			strcpy(result, a);
			strcat(result, b);
			free(digits);
			free(a);
			free(b);
		}
	}
	
	// 3 total_digits
	else if (total_digits == 3) {
		int first_digit = n/100;
		if (n%100==0) {
			char* a = int_to_word(first_digit, dict);
			char* b = "hundred";
			
			strcpy(result, a);
			strcat(result, b);
			
			free(a);
		}
		
		else {
			int second_part = 1;
			
			while ((n-second_part) % 100 != 0)
				second_part += 1;
			
			char* a = int_to_word(first_digit, dict);
			char* b = "hundredand";
			char* c = int_to_word(second_part, dict);
			
			strcpy(result, a);
			strcat(result, b);
			strcat(result, c);
			
			free(a);
			free(c);
		}
	}
	
	// 4 total_digits (1000)
	else
		strcpy(result, dict[n]);
	
	return result;
}
