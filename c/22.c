/*
 * Project Euler
 * 22.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "strings.h"


int name_to_score(char* name, int index);
int cmp(const void* a, const void* b);


int main() {
	// read
	int len;
	char** arr = file_to_string_split("22_names", &len, ',');
	
	// sort
	qsort(arr, len, sizeof(char*), cmp);
	
	// score
	int64_t sum = 0;
	for (int i=0; i<len; i++)
		sum += name_to_score(arr[i], i);
	
	// end
	free_string_split(arr, len);
	printf("names      %d \n", len);
	printf("score sum  %" PRId64 "\n", sum);
	return 0;
}


/**
 * Computes a name's score as described in the problem text.
 * 
 * @param	name	the name to evaluate
 * @param	index	the name's position on the list
 * @return			the name's score
 */
int name_to_score(char* name, int index) {
	int len = (int) strlen(name);
	int sum = 0;
	for (int i=0; i<len; i++)
		sum += alphabet_value(name[i]);
	return sum * (index + 1);
}


/**
 * Compares two strings. This is a merely a wrapper around strcmp() so
 * that it can be passed to qsort() properly.
 * 
 * @param	a	the first string
 * @param	b	the second string
 * @return		the result of strcmp()
 */
int cmp(const void* a, const void* b) {
    const char* str_a = *(const char**) a;
    const char* str_b = *(const char**) b;
    int result = strcmp(str_a , str_b);
    return result;
}
