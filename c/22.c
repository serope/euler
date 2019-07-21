/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 22
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define ALPHABET_VALUE(c)	c-64

int name_to_score(char* name, int index);
int comparison(const void* a, const void* b);


int main() {
	/*******************************************************************
	 * 1. Open the file
	 ******************************************************************/
	const char* filename = "22_names.txt";
	FILE* txtfile = fopen(filename, "r");
	if (!txtfile) {
		printf("Unable to open %s \n", filename);
		exit(EXIT_FAILURE);
	}
	
	
	
	/*******************************************************************
	 * 2. Convert the file's contents into a list of strings
	 ******************************************************************/
	char** list = NULL;
	int list_len = 0;
	
	char* name = NULL;
	int name_len = 0;
	
	while (true) {
		//Get the next char in the file
		int seek = getc(txtfile);
		
		//Skip if it's a double quote
		if (seek=='\"')
			continue;
		
		//Append the name to the list if it's a comma or EOF
		else if (seek==',' || seek==EOF) {
			//Terminate the name
			name = (char*) realloc(name, sizeof(char)*(name_len+1));
			name[name_len] = '\0';
			name_len++;
			
			//Append it to the list
			list = (char**) realloc(list, sizeof(char*)*(list_len+1));
			list[list_len] = (char*) calloc(name_len+1, sizeof(char));
			list[list_len] = strcpy(list[list_len], name);
			list_len++;
			
			//Reset the name
			free(name);
			name = NULL;
			name_len = 0;
			
			//Break if it's the end
			if (seek==EOF)
				break;
		}
		
		//Otherwise, append the char to the name
		else {
			name = (char*) realloc(name, sizeof(char)*(name_len+1));
			name[name_len] = seek;
			name_len++;
		}
	}
	
	
	/*******************************************************************
	 * 3. Sort the list
	 ******************************************************************/
	qsort(list, list_len, sizeof(char*), comparison);
	
	
	/*******************************************************************
	 * 4. Sum the names' scores
	 ******************************************************************/
	int64_t sum = 0;
	
	for (int i=0; i<list_len; i++) {
		int score = name_to_score(list[i], i);
		//printf("%s (%d) (%d) \n", list[i], (int) strlen(list[i]), score);
		sum += score;
	}
	
		
		
	/*******************************************************************
	 * 5. Print, cleanup, and exit
	 ******************************************************************/
	for (int n=0; n<list_len; n++) {
		printf("list[%d] \t %s (len: %d) \n", n, list[n], (int) strlen(list[n]));
		free(list[n]);
	}
	free(list);
	free(name);
	
	printf("list_len \t %d \n", list_len);
	printf("sum      \t %lld \n", sum);

	exit(EXIT_SUCCESS);
}



int name_to_score(char* name, int index) {
	int len = (int) strlen(name);
	int sum = 0;
	int score;
	
	for (int c=0; c<len; c++) {
		char letter = name[c];
		sum += ALPHABET_VALUE(letter);
	}
	
	score = sum*(index+1);
	
	return score;
}



int comparison(const void* a, const void* b) {
    const char* str_a = *(const char**) a;
    const char* str_b = *(const char**) b;
    int result = strcmp(str_a , str_b);
    return result;
}
