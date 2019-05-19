/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 17
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LEN 128

char* int_to_word(int n);


int main() {
	int total_letters = 0;
	
	for (int x=1; x<=1000; x++) {
		//Convert the number to a word
		char* word = int_to_word(x);
		printf("%d. \t %s \n", x, word);
		
		//Add its length to the sum
		size_t len = strlen(word);
		total_letters += (int) len;
		
		//Free
		free(word);
	}
	
	printf("total_letters \t %d \n", total_letters);
	return 0;
}




char* int_to_word(int n) {
	/*******************************************************************
	 * Count n's digits
	 ******************************************************************/
	int digits;
	
	if (n <= 9)
		digits = 1;
	else if (n >= 10 && n <= 99)
		digits = 2;
	else if (n >= 100 && n <=999)
		digits = 3;
	else
		digits = 4;
	
	
	/*******************************************************************
	 * Allocate memory for the string to be returned
	 ******************************************************************/
	char* result = (char*) calloc(MAX_WORD_LEN, sizeof(char));
	
	
	/*******************************************************************
	 * Single digit
	 ******************************************************************/
	if (digits==1) {
		switch (n) {
			case 1:
				strcpy(result, "one");
				break;
			case 2:
				strcpy(result, "two");
				break;
			case 3:
				strcpy(result, "three");
				break;
			case 4:
				strcpy(result, "four");
				break;
			case 5:
				strcpy(result, "five");
				break;
			case 6:
				strcpy(result, "six");
				break;
			case 7:
				strcpy(result, "seven");
				break;
			case 8:
				strcpy(result, "eight");
				break;
			case 9:
				strcpy(result, "nine");
				break;
			}
		}
	
	
	/*******************************************************************
	 * Double digits
	 ******************************************************************/
	else if (digits==2) {
		switch (n) {
			case 10:
				strcpy(result, "ten");
				break;
			case 11:
				strcpy(result, "eleven");
				break;
			case 12:
				strcpy(result, "twelve");
				break;
			case 13:
				strcpy(result, "thirteen");
				break;
			case 14:
				strcpy(result, "fourteen");
				break;
			case 15:
				strcpy(result, "fifteen");
				break;
			case 16:
				strcpy(result, "sixteen");
				break;
			case 17:
				strcpy(result, "seventeen");
				break;
			case 18:
				strcpy(result, "eighteen");
				break;
			case 19:
				strcpy(result, "nineteen");
				break;
			case 20:
				strcpy(result, "twenty");
				break;
			case 30:
				strcpy(result, "thirty");
				break;
			case 40:
				strcpy(result, "forty");
				break;
			case 50:
				strcpy(result, "fifty");
				break;
			case 60:
				strcpy(result, "sixty");
				break;
			case 70:
				strcpy(result, "seventy");
				break;
			case 80:
				strcpy(result, "eighty");
				break;
			case 90:
				strcpy(result, "ninety");
				break;
			default: {
				int second_digit = 1;
				while ((n-second_digit) % 10 != 0)
					second_digit += 1;

				char* a = int_to_word(n-second_digit);	//Free this!
				char* b = int_to_word(second_digit);	//Free this!
				
				strcpy(result, a);
				strcat(result, b);
				
				free(a);
				free(b);
			}
		}
	}
	
	
	/*******************************************************************
	 * Triple digits
	 ******************************************************************/
	else if (digits==3) {
		int first_digit = n/100;
		if (n%100==0) {
			char* a = int_to_word(first_digit);		//Free this!
			char* b = "hundred";
			
			strcpy(result, a);
			strcat(result, b);
			
			free(a);
		}
		
		else {
			int second_part = 1;
			
			while ((n-second_part) % 100 != 0)
				second_part += 1;
			
			char* a = int_to_word(first_digit);		//Free this!
			char* b = "hundredand";
			char* c = int_to_word(second_part);		//Free this!
			
			strcpy(result, a);
			strcat(result, b);
			strcat(result, c);
			
			free(a);
			free(c);
		}
	}
	
	/*******************************************************************
	 * 1000
	 ******************************************************************/
	else
		strcpy(result, "onethousand");
	
	return result;
}
