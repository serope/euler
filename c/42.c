/*
 * Project Euler
 * 42.c
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "array.h"
#include "euler.h"
#include "strings.h"

bool has_problem42_property(char* word, int* arr, int arr_len);
int word_to_score(char* word);


int main() {
	// read
	int words_len;
	char** words = file_to_string_split("42_words", &words_len, ',');
	
	// triangles
	int tri_len = 1000;
	int* tris = triangle_numbers(tri_len);
	
	// solve
	int total = 0;
	for (int i=0; i<words_len; i++)
		if (has_problem42_property(words[i], tris, tri_len))
			total++;
	
	// end
	printf("total words       %d \n", words_len);
	printf("triangle words    %d \n", total);
	free_string_split(words, words_len);
	free(tris);
	return 0;
}


/**
 * Returns true if a word's score is a triangle number.
 * 
 * @param	word	the word to evaluate
 * @param	arr		an array of triangle numbers to search
 * @param	len		the array's length
 * @return			true or false
 */
bool has_problem42_property(char* word, int* arr, int arr_len) {
	int score = word_to_score(word);
	return arr_bsearch(arr, arr_len, score);
}


/**
 * Computes a word's score as described in the problem text.
 * 
 * @param	word	the word to evaluate
 * @return			the word's score
 */
int word_to_score(char* word) {
	int len = strlen(word);
	int score = 0;
	for (int i=0; i<len; i++)
		score += alphabet_value(word[i]);
	return score;
}
