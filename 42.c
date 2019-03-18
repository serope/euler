/***********************************************************************
 * Project Euler (https://serope.com/github/euler.html)
 * Problem 42
 **********************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_WORD_LEN        16
#define ALPHABET_VALUE(c)   c-64

int word_to_score(char* name);
int nth_triangular_number(int nth);


int main() {
	/*******************************************************************
	 * 1. Open the file
	 ******************************************************************/
	char* filename = "42_words.txt";
	FILE* textfile = fopen(filename, "r");
	if (!textfile) {
		printf("Unable to open (%s) \n", filename);
		exit(EXIT_FAILURE);
	}
	
	
	
	/*******************************************************************
	 * 2. Prepare the 'word_list' and the 'current_word' being read
	 *    from the file
	 ******************************************************************/
	char** word_list = NULL;
	int word_list_len = 0;
	
	char* current_word = (char*) calloc(MAX_WORD_LEN, sizeof(char));
	int current_word_len = 0;
	
	
	
	/*******************************************************************
	 * 3. Read every word from the textfile
	 *    Store the current word in the 'word_list'
	 ******************************************************************/
	int seek;
	bool recording = false;
	
	while((seek=getc(textfile)) != EOF) {
		if (seek=='"') {
			//When the first '"' appears, start recording the word
			if (recording==false)
				recording = true;
				
			//When the second '"' appears...
			else {
				//1. Store the current word in the array
				word_list = (char**) realloc(word_list, sizeof(char*) * (word_list_len+1) );
				word_list[word_list_len] = (char*) calloc(MAX_WORD_LEN, sizeof(char));
				strcpy(word_list[word_list_len], current_word);
				word_list_len += 1;
				
				//2. Reset the current word
				free(current_word);
				current_word = (char*) calloc(MAX_WORD_LEN, sizeof(char));
				current_word_len = 0;
				
				//3. Stop recording until the next '"' symbol appears
				recording = false;
			}
			continue;
		}
		
		//If recording, append the current char to the current word
		if (recording) {
			current_word[current_word_len] = seek;
			current_word_len += 1;
		}
	}
	fclose(textfile);
	
	
	
	
	/*******************************************************************
	 * 4. Create a list of each word's score
	 ******************************************************************/
	int score_list[word_list_len];
	int current_score;
	
	for (int n=0; n<word_list_len; n++) {
		current_score = word_to_score(word_list[n]);
		score_list[n] = current_score;
	}
	
	
	
	/*******************************************************************
	 * 5. Create a list of triangular numbers
	 *    (30 is sufficient for this problem)
	 ******************************************************************/
	int tri_list_len = 30;
	int tri_list[tri_list_len];
	
	for (int n=0; n<tri_list_len; n++)
		tri_list[n] = nth_triangular_number(n+1);
	
	
	
	/*******************************************************************
	 * 6. Compare each score with each triangular number
	 * 
	 *    If they match, increase the total
	 ******************************************************************/
	int triangle_words = 0;
	
	for (int s=0; s<word_list_len; s++)
		for (int t=0; t<tri_list_len; t++)
			if (score_list[s]==tri_list[t]) {
				triangle_words++;
				break;
			}
		
		
	/*******************************************************************
	 * 7. Print results
	 ******************************************************************/
	//for (int n=0; n<word_list_len; n++)
		//printf("word_list[%d] \t %s (len: %d, score: %d) \n", n, word_list[n], (int) strlen(word_list[n]), score_list[n]);
	
	printf("word_list_len   %d \n", word_list_len);
	printf("triangle_words  %d \n", triangle_words);
	
	
	
	/*******************************************************************
	 * 8. Free memory and exit
	 ******************************************************************/
	for (int n=0; n<word_list_len; n++)
		free(word_list[n]);
	
	free(word_list);
	free(current_word);
	
	exit(EXIT_SUCCESS);
}






int word_to_score(char* word) {
	int len = strlen(word);
	int sum = 0;
	
	for (int c=0; c<len; c++)
		sum += ALPHABET_VALUE(word[c]);
	
	return sum;
}





int nth_triangular_number(int nth) {
	int sum = 0;
	
	for (int x=1; x<=nth; x++)
		sum += x;
	
	return sum;
}
