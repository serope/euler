/*
 * Project Euler
 * strings.c
 */
#include "strings.h"


char** string_split(char* in, int in_len, char split, int* len_ptr) {
	// list to return
	char** list = NULL;
	int list_len = 0;
	
	// current string
	char* str = NULL;
	int str_len = 0;
	
	for (int i=0; i<in_len; i++) {
		char c = in[i];
		
		if (c == split) {
			// terminate
			str = realloc(str, sizeof(char) * (str_len + 1) );
			str[str_len] = '\0';
			str_len += 1;
			
			// append
			list = __append_to_strarr(list, &list_len, str, str_len);
			
			// reset str
			str = realloc(str, 0);
			str_len = 0;
		}
		
		// append to str
		else {
			str = realloc(str, sizeof(char) * (str_len + 1) );
			str[str_len] = c;
			str_len += 1;
		}
	}
	
	// end
	list = __append_to_strarr(list, &list_len, str, str_len);
	*len_ptr = list_len;
	free(str);
	return list;
}


void free_string_split(char** arr, int arr_len) {
	for (int i=0; i<arr_len; i++)
		free(arr[i]);
	free(arr);
}


int char_to_int(char c) {
	return c-48;
}


vec_t* string_split_vec(char* in, int in_len, char split) {
	vec_t* v = vec_new();
	char* str = NULL;
	int str_len = 0;
	
	for (int i=0; i<in_len; i++) {
		char c = in[i];
		
		// append to vector and reset string
		if (c == split) {
			v = vec_append(v, str);
			str = realloc(str, 0);
			str_len = 0;
		}
		
		// append to str
		else {
			str = realloc(str, sizeof(char) * (str_len + 1) );
			str[str_len] = c;
			str_len += 1;
		}
	}
	
	// end
	v = vec_append(v, str);
	free(str);
	return v;
}


char* file_to_string(const char* filename, int* len_ptr) {
	// stat
	struct stat* st = malloc(sizeof(struct stat));
	stat(filename, st);
	if (!st) {
		printf("file_to_string() failed to stat \"%s\" \n", filename);
		return NULL;
	}
	
	// allocate
	int filesize = st->st_size;
	char* str = calloc(filesize, sizeof(char));
	
	// open
	FILE* txt = fopen(filename, "r");
	if (!txt) {
		printf("file_to_string() failed to open \"%s\" \n", filename);
		free(st);
		return NULL;
	}
	
	// read
	int i = 0;
	int c;
	while ((c = getc(txt)) != EOF) {
		str[i] = c;
		i++;
	}
	
	// end
	fclose(txt);
	free(st);
	*len_ptr = filesize;
	return str;
}


char**
file_to_string_split(const char* filename, int* len_ptr, char split) {
	// read
	int str_len;
	char* str = file_to_string(filename, &str_len);
	
	// split
	int arr_len;
	char** arr = string_split(str, str_len, split, &arr_len);
	
	// end
	free(str);
	*len_ptr = arr_len;
	return arr;
}


int** file_to_matrix(const char* filename, int n) {
	// read
	int str_len;
	char* str = file_to_string(filename, &str_len);
	
	// initialize NxN matrix
	int** m = calloc(n, sizeof(int*));
	for (int r=0; r<n; r++)
		m[r] = calloc(n, sizeof(int));
	
	// split string rows
	int str_rows_len = 0;
	char** str_rows = string_split(str, str_len, '\n', &str_rows_len);
	
	// populate m (ignore final element of str_rows; an empty newline)
	for (int r=0; r<str_rows_len-1; r++) {
		// get row elements (split row by spaces)
		char* str_row = str_rows[r];
		int elements_len;
		char** elements = string_split(str_row, strlen(str_row), ' ',
														&elements_len);
		
		// assign elements
		for (int c=0; c<elements_len; c++) {
			char* element = elements[c];
			int x = atoi(element);
			m[r][c] = x;
		}
		
		free_string_split(elements, elements_len);
	}
	
	// end
	free(str);
	free_string_split(str_rows, str_rows_len);
	return m;
}


int alphabet_value(char c) {
	if (c < 'A' || c > 'Z')
		return 0;
	return c-64;
}


char** __append_to_strarr(char** arr, int* arr_len_ptr, char* str,
														int str_len)
{
	arr = realloc(arr, sizeof(char*) * (*arr_len_ptr + 1));
	arr[*arr_len_ptr] = calloc(str_len, sizeof(char));
	size_t str_size = sizeof(char) * str_len;
	memcpy(arr[*arr_len_ptr], str, str_size);
	*arr_len_ptr += 1;
	return arr;
}
