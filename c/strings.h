/*
 * Project Euler
 * strings.h
 * 
 * Functions for making C strings more convenient.
 */
#pragma once
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "vector.h"


/**
 * Reads a file into a string.
 * 
 * @param	filename	the name of the file to read
 * @param	len_ptr		a pointer to an integer which takes on the length
 * 						of the output array
 * @return				a heap-allocated string
 */
char* file_to_string(const char* filename, int* len_ptr);


/**
 * Reads a file into an array of strings separated by the given split
 * character. The array should be freed with free_string_split().
 * 
 * @param	filename	the name of the file to read
 * @param	len_ptr		a pointer to an integer which takes on the length
 * 						of the output array
 * @param	split		the character to split the string by
 * @return				a heap-allocated array of strings
 */
char**
file_to_string_split(const char* filename, int* len_ptr, char split);


/**
 * Splits a string by the given split character, returning an array of
 * strings.
 * 
 * @param	in			the input string
 * @param	in_len		the input string's length
 * @param	split		the character to split by
 * @param	len_ptr		a pointer to an integer which will take on the
 * 						length of the output array
 * @return				a heap-allocated array of strings
 */
char** string_split(char* in, int in_len, char split, int* len_ptr);


/**
 * Returns an uppercase letter's alphabetical value, e.g. A = 1, Z = 26.
 * 
 * @param	c	the char to evaluate
 * @return		an integer; 0 if c isn't an uppercase letter
 */
int alphabet_value(char c);


/**
 * Frees an array returned by string_split().
 * 
 * @param	arr			an array returned by string_split()
 * @param	arr_len		the array's length
 */
void free_string_split(char** arr, int arr_len);


/**
 * Splits a string by the given character, returning a vector.
 * 
 * @param	in			the input string
 * @param	in_len		the input string's length
 * @param	split		the character to split by
 * @return				a vector of strings
 */
vec_t* string_split_vec(char* in, int in_len, char split);


/**
 * Reads a file into an NxN matrix.
 * 
 * @param	filename	the file to read
 * @param	n			the amount of rows and columns
 * @return				a 2-dimensional int array
 */
int** file_to_matrix(const char* filename, int n);


/**
 * Appends a string to an array of strings.
 * 
 * @param	arr				the array to edit
 * @param	arr_len_ptr		a pointer to the array's length, which is
 * 							incremented accordingly
 * @param	str				the string to be appended
 * @param	str_len			the string's length
 * @return					the array, after the string has been appended
 * 							to it
 */
char** __append_to_strarr(char** arr, int* arr_len_ptr, char* str,
															int str_len);


/**
 * Returns the integer form of c.
 * 
 * @param	c	the character to convert
 * @return		c's ASCII integer value
 */
int char_to_int(char c);
