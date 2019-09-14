/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 13
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "euler.h"
#include "euler_bignum.h"

int main() {
	/*******************************************************************
	 * 1. Open the file
	 ******************************************************************/
	const char* filename = "13_bignums.txt";
	FILE* txtfile = fopen(filename, "r");
	if (!txtfile) {
		printf("Unable to open %s \b", filename);
		exit(EXIT_FAILURE);
	}
	
	
	/*******************************************************************
	 * 2. Convert the file's contents into a list of bignums
	 ******************************************************************/
	big* list = NULL;
	int list_len = 0;
	
	char* string = NULL;
	int string_len = 0;
	int seek;
	
	while (true) {
		//Get the current digit
		seek=getc(txtfile);
		
		//Append the current bignum to the list
		if (seek=='\n' || seek==EOF) {
			//Terminate the string
			string = (char*) realloc(string, sizeof(char)*(string_len+1));
			string[string_len] = '\0';
			string_len++;
			
			//Append a new bignum to the list
			list = (big*) realloc(list, sizeof(big)*(list_len+1));
			list[list_len] = big_new(string);
			list_len++;
			
			//Reset the string
			free(string);
			string = NULL;
			string_len = 0;
			
			//Exit if it's the end of the file
			if (seek==EOF)
				break;
		}
		
		//Append the current character to the string
		else {
			string = (char*) realloc(string, sizeof(char)*(string_len+1));
			string[string_len] = seek;
			string_len++;
		}
	}
	fclose(txtfile);

	
	/*******************************************************************
	 * 3. Compute the sum
	 ******************************************************************/
	big sum = big_new("0");
	for (int i=0; i<list_len; i++)
		big_add(sum, list[i]);
	
	
	/*******************************************************************
	 * 4. Print, cleanup, and exit
	 ******************************************************************/
	big_print(sum);
	for (int i=0; i<list_len; i++) {
		BIG_FREE(list[i]);
	}
	BIG_FREE(sum);
	free(list);
	free(string);
	return 0;
}


